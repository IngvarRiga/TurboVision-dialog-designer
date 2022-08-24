#include "textrainput.h"

#define Uses_TGroup
//#define Uses_TKeys
//#define Uses_TExtInputLine
//#define Uses_TDrawBuffer
#define Uses_TValidator
#define Uses_TText
#include <tvision/tv.h>

//#if !defined( __CTYPE_H )
//#include <ctype.h>
//#endif  // __CTYPE_H
//
//#if !defined( __STRING_H )
//#include <string.h>
//#endif  // __STRING_H
//
//#if !defined( __DOS_H )
//#include <dos.h>
//#endif  // __DOS_H

const int CONTROL_Y = 25;

//char hotKey(const char* s) noexcept
//{
//    char* p;
//
//    if ((p = strchr((char*)s, '~')) != 0)
//        return toupper(p[1]);
//    else
//        return 0;
//}

/// <summary>
/// ����������� ������� ����������� ����� � ������
/// </summary>
/// <param name="s">- ������ �� ������� ���������� �����������</param>
/// <param name="pos">- ������� ������� ������� � ������</param>
/// <returns></returns>
static int prevWord(const char* s, int pos) noexcept
{
    for (int i = pos - 1; i >= 1; --i)
    {
        if (s[i] != ' ' && s[i - 1] == ' ')
            return i;
    }
    return 0;
};

static int nextWord(TStringView s, int pos) noexcept
{
    for (int i = pos; i < int(s.size()) - 1; ++i)
    {
        if (s[i] == ' ' && s[i + 1] != ' ')
            return i + 1;
    }
    return int(s.size());
};

#define cpInputLine "\x13\x13\x14\x15"

TExtInputLine::TExtInputLine(const TRect& bounds, uint limit, TValidator* aValid, ushort limitMode) noexcept :
    TView(bounds),
    maxLen((limitMode == ilMaxBytes) ? min(max(limit - 1, 0), 255) : 255),
    maxWidth((limitMode == ilMaxWidth) ? limit : UINT_MAX),
    maxGraphemes((limitMode == ilMaxGraphemes) ? limit : UINT_MAX),
    curPos(0),
    firstPos(0),
    selStart(0),
    selEnd(0),
    validator(aValid)
{
    data = new char[maxLen + 1];
    oldData = new char[maxLen + 1];

    state |= sfCursorVis;
    options |= ofSelectable | ofFirstClick;
    *data = EOS;
}

TExtInputLine::~TExtInputLine()
{
    memset(data, 0x0, maxLen);
    memset(oldData, 0x0, maxLen);
    delete[] data;
    delete[] oldData;
    destroy(validator);
}

Boolean TExtInputLine::canScroll(int delta)
{
    if (delta < 0)
        return Boolean(firstPos > 0);
    else
        if (delta > 0)
            return Boolean(strwidth(data) - firstPos + 2 > size.x);
        else
            return False;
}

ushort TExtInputLine::dataSize()
{
    ushort dSize = 0;

    if (validator)
        dSize = validator->transfer(data, NULL, vtDataSize);
    if (dSize == 0)
        dSize = maxLen + 1;
    return dSize;
}

void TExtInputLine::draw()
{
    int l, r;
    TDrawBuffer b;

    TColorAttr color = getColor((state & sfFocused) ? 2 : 1);

    b.moveChar(0, ' ', color, size.x);
    if (size.x > 1)
    {
        b.moveStr(1, data, color, size.x - 1, firstPos);
    }
    if (canScroll(1))
        b.moveChar(size.x - 1, rightArrow, getColor(4), 1);
    if (canScroll(-1))
        b.moveChar(0, leftArrow, getColor(4), 1);
    if ((state & sfSelected) != 0)
    {
        l = displayedPos(selStart) - firstPos;
        r = displayedPos(selEnd) - firstPos;
        l = max(0, l);
        r = min(size.x - 2, r);
        if (l < r)
            b.moveChar(l + 1, 0, getColor(3), r - l);
    }
    writeLine(0, 0, size.x, size.y, b);
    setCursor(displayedPos(curPos) - firstPos + 1, 0);
}

void TExtInputLine::getData(void* rec)
{
    if ((validator == 0) || (validator->transfer(data, rec, vtGetData) == 0))
        memcpy(rec, data, dataSize());
}

TPalette& TExtInputLine::getPalette() const
{
    static TPalette palette(cpInputLine, sizeof(cpInputLine) - 1);
    return palette;
}

int TExtInputLine::mouseDelta(TEvent& event)
{
    TPoint mouse = makeLocal(event.mouse.where);

    if (mouse.x <= 0)
        return -1;
    else
        if (mouse.x >= size.x - 1)
            return 1;
        else
            return 0;
}

int TExtInputLine::mousePos(TEvent& event)
{
    TPoint mouse = makeLocal(event.mouse.where);
    mouse.x = max(mouse.x, 1);
    int pos = mouse.x + firstPos - 1;
    pos = max(pos, 0);
    TStringView text = data;
    return TText::scroll(text, pos, False);
}

int TExtInputLine::displayedPos(int pos)
{
    return strwidth(TStringView(data, pos));
}

void TExtInputLine::deleteSelect()
{
    if (selStart < selEnd)
    {
        int len = strlen(data);
        memmove(data + selStart, data + selEnd, len - selEnd);
        data[len - selEnd + selStart] = EOS;
        curPos = selStart;
    }
}

void TExtInputLine::deleteCurrent()
{
    TStringView text = data;
    if (curPos < (int)text.size())
    {
        selStart = curPos;
        selEnd = curPos + TText::next(text.substr(curPos));
        deleteSelect();
    }
}

void TExtInputLine::adjustSelectBlock()
{
    if (curPos < anchor)
    {
        selStart = curPos;
        selEnd = anchor;
    }
    else
    {
        selStart = anchor;
        selEnd = curPos;
    }
}

void TExtInputLine::saveState()
{
    if (validator)
    {
        strcpy(oldData, data);
        oldCurPos = curPos;
        oldFirstPos = firstPos;
        oldSelStart = selStart;
        oldSelEnd = selEnd;
    }
}

void TExtInputLine::restoreState()
{
    if (validator)
    {
        strcpy(data, oldData);
        curPos = oldCurPos;
        firstPos = oldFirstPos;
        selStart = oldSelStart;
        selEnd = oldSelEnd;
    }
}

Boolean TExtInputLine::checkValid(Boolean noAutoFill)
{
    int oldLen, newLen;
    char newData[256];

    if (validator)
    {
        oldLen = strlen(data);
        strcpy(newData, data);
        if (!validator->isValidInput(newData, noAutoFill))
        {
            restoreState();
            return False;
        }
        else
        {
            if (strlen(newData) > maxLen)
                newData[maxLen] = 0;
            strcpy(data, newData);
            newLen = strlen(data);
            if ((curPos >= oldLen) && (newLen > oldLen))
                curPos = newLen;
            return True;
        }
    }
    else
        return True;
}


void TExtInputLine::handleEvent(TEvent& event)
{
    Boolean extendBlock;
    /* Home, Left Arrow, Right Arrow, End, Ctrl-Left Arrow, Ctrl-Right Arrow */
    static const char padKeys[] = { 0x47,0x4b,0x4d,0x4f,0x73,0x74 };
    TView::handleEvent(event);

    char keyText[sizeof(event.keyDown.text) + 1];
    int delta, i, len, curWidth;
    if ((state & sfSelected) != 0)
        switch (event.what)
        {
            case evMouseDown:
                if (canScroll(delta = mouseDelta(event)))
                    do
                    {
                        if (canScroll(delta))
                        {
                            firstPos += delta;
                            drawView();
                        }
                    } while (mouseEvent(event, evMouseAuto));
                else if (event.mouse.eventFlags & meDoubleClick)
                    selectAll(True);
                else
                {
                    anchor = mousePos(event);
                    do
                    {
                        if (event.what == evMouseAuto)
                        {
                            delta = mouseDelta(event);
                            if (canScroll(delta))
                                firstPos += delta;
                        }
                        curPos = mousePos(event);
                        adjustSelectBlock();
                        drawView();
                    } while (mouseEvent(event, evMouseMove | evMouseAuto));
                }
                clearEvent(event);
                break;
            case evKeyDown:
                saveState();
                event.keyDown.keyCode = ctrlToArrow(event.keyDown.keyCode);
                if (memchr(padKeys, event.keyDown.charScan.scanCode, sizeof(padKeys)) != 0 &&
                    (event.keyDown.controlKeyState & kbShift) != 0
                    )
                {
                    event.keyDown.charScan.charCode = 0;
                    if (curPos == selEnd)
                        anchor = selStart;
                    else if (selStart == selEnd)
                        anchor = curPos;
                    else
                        anchor = selEnd;
                    extendBlock = True;
                }
                else
                    extendBlock = False;

                switch (event.keyDown.keyCode)
                {
                    case kbLeft:
                        curPos -= TText::prev(data, curPos);
                        break;
                    case kbRight:
                        curPos += TText::next(data + curPos);
                        break;
                    case kbCtrlLeft:
                        curPos = prevWord(data, curPos);
                        break;
                    case kbCtrlRight:
                        curPos = nextWord(data, curPos);
                        break;
                    case kbHome:
                        curPos = 0;
                        break;
                    case kbEnd:
                        curPos = strlen(data);
                        break;
                    case kbBack:
                        if (selStart == selEnd)
                        {
                            selStart = curPos - TText::prev(data, curPos);
                            selEnd = curPos;
                        }
                        deleteSelect();
                        checkValid(True);
                        break;
                    case kbCtrlBack:
                    case kbAltBack:
                        if (selStart == selEnd)
                        {
                            selStart = prevWord(data, curPos);
                            selEnd = curPos;
                        }
                        deleteSelect();
                        checkValid(True);
                        break;
                    case kbDel:
                        if (selStart == selEnd)
                            deleteCurrent();
                        else
                            deleteSelect();
                        checkValid(True);
                        break;
                    case kbCtrlDel:
                        if (selStart == selEnd)
                        {
                            selStart = curPos;
                            selEnd = nextWord(data, curPos);
                        }
                        deleteSelect();
                        checkValid(True);
                    case kbIns:
                        setState(sfCursorIns, Boolean(!(state & sfCursorIns)));
                        break;
                    default:
                        // The event text may contain null characters, but 'data' is null-terminated,
                        // so rely on strlen to measure the text length.
                        strnzcpy(keyText, event.keyDown.getText(), sizeof(keyText));
                        if ((len = strlen(keyText)) != 0)
                        {
                            deleteSelect();
                            if ((state & sfCursorIns) != 0)
                                deleteCurrent();

                            if (checkValid(True))
                            {
                                TTextMetrics dataMts = TText::measure(data);
                                TTextMetrics keyMts = TText::measure(keyText);
                                if (strlen(data) + len <= maxLen &&
                                    dataMts.width + keyMts.width <= maxWidth &&
                                    dataMts.graphemeCount + keyMts.graphemeCount <= maxGraphemes
                                    )
                                {
                                    if (firstPos > curPos)
                                        firstPos = curPos;
                                    memmove(data + curPos + len, data + curPos, strlen(data + curPos) + 1);
                                    memcpy(data + curPos, keyText, len);
                                    curPos += len;
                                }
                                checkValid(False);
                            }
                        }
                        else if (event.keyDown.charScan.charCode == CONTROL_Y)
                        {
                            *data = EOS;
                            curPos = 0;
                        }
                        else
                            return;
                }
                if (extendBlock)
                    adjustSelectBlock();
                else
                {
                    selStart = 0;
                    selEnd = 0;
                }
                curWidth = displayedPos(curPos);
                if (firstPos > curWidth)
                    firstPos = curWidth;
                i = curWidth - size.x + 2;
                if (firstPos < i)
                    firstPos = i;
                drawView();
                clearEvent(event);
                break;
        }
}

void TExtInputLine::selectAll(Boolean enable, Boolean scroll)
{
    selStart = 0;
    if (enable)
        curPos = selEnd = strlen(data);
    else
        curPos = selEnd = 0;
    if (scroll)
        firstPos = max(0, displayedPos(curPos) - size.x + 2);
    drawView();
}

void TExtInputLine::setData(void* rec)
{
    if ((validator == 0) || (validator->transfer(data, rec, vtSetData) == 0))
    {
        memcpy(data, rec, dataSize() - 1);
        data[dataSize() - 1] = EOS;
    }
    selectAll(True);
}

void TExtInputLine::setState(ushort aState, Boolean enable)
{
    TView::setState(aState, enable);
    if (aState == sfSelected ||
        (aState == sfActive && (state & sfSelected) != 0)
        )
        selectAll(enable, False);
}

void TExtInputLine::setValidator(TValidator* aValid)
{
    if (validator != 0)
        destroy(validator);

    validator = aValid;
}


Boolean TExtInputLine::valid(ushort cmd)
{
    if (validator)
    {
        if (cmd == cmValid)
            return Boolean(validator->status == vsOk);
        else if (cmd != cmCancel)
            if (!validator->validate(data))
            {
                select();
                return False;
            }
    }
    return True;
}



#include "winputline.h"

#define Uses_TGroup
#define Uses_TKeys
#define Uses_TInputLine
#define Uses_TDrawBuffer
#define Uses_TEvent
#define Uses_TValidator
#define Uses_opstream
#define Uses_ipstream
#define Uses_TText
#include <tvision/tv.h>

const char * const TWrapInputLine::name = "TWrapInputLine";
const char TWrapInputLine::rightArrow = '\x10';
const char TWrapInputLine::leftArrow = '\x11';

const int CONTROL_Y = 25;

//char hotKey(const char *s) noexcept
//{
//    char *p;
//
//    if ((p = strchr((char *) s, '~')) != 0)
//        return toupper(p[1]);
//    else
//        return 0;
//}

#define cpInputLine "\x13\x13\x14\x15"

TWrapInputLine::TWrapInputLine(const TRect& bounds, uint aMaxLen, TValidator *aValid) noexcept :
TView(bounds),
data(new char[aMaxLen]),
maxLen(aMaxLen - 1),
curPos(0),
firstPos(0),
selStart(0),
selEnd(0),
validator(aValid),
oldData(new char[aMaxLen])
{
    eventMask = 0xFF; //-- установлен флаг получения ВСЕХ сообщений от мыши
    state |= sfCursorVis;
    options |= ofSelectable | ofFirstClick;
    *data = EOS;
    eventClick = false;
    eventDragged = false;
}

TWrapInputLine::TWrapInputLine(const TRect& bounds, uint aMaxLen, TValidator *aValid, bool click) noexcept :
TView(bounds),
data(new char[aMaxLen]),
maxLen(aMaxLen - 1),
curPos(0),
firstPos(0),
selStart(0),
selEnd(0),
validator(aValid),
oldData(new char[aMaxLen])
{
    eventMask = 0xFF; //-- установлен флаг получения ВСЕХ сообщений от мыши
    state |= sfCursorVis;
    options |= ofSelectable | ofFirstClick;
    *data = EOS;
    eventClick = click;
    eventDragged = false;
}

TWrapInputLine::~TWrapInputLine()
{
    delete[] data;
    delete[] oldData;
    destroy(validator);
}

Boolean TWrapInputLine::canScroll(int delta)
{
    if (delta < 0)
        return Boolean(firstPos > 0);
    else
        if (delta > 0)
        return Boolean(strwidth(data) - firstPos + 2 > size.x);
    else
        return False;
}

ushort TWrapInputLine::dataSize()
{
    ushort dSize = 0;

    if (validator)
        dSize = validator->transfer(data, NULL, vtDataSize);
    if (dSize == 0)
        dSize = maxLen + 1;
    return dSize;
}

void TWrapInputLine::draw()
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

void TWrapInputLine::getData(void *rec)
{
    if ((validator == 0) || (validator->transfer(data, rec, vtGetData) == 0))
        memcpy(rec, data, dataSize());
}

TPalette& TWrapInputLine::getPalette() const
{
    static TPalette palette(cpInputLine, sizeof ( cpInputLine) - 1);
    return palette;
}

int TWrapInputLine::mouseDelta(TEvent& event)
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

int TWrapInputLine::mousePos(TEvent& event)
{
    TPoint mouse = makeLocal(event.mouse.where);
    mouse.x = max(mouse.x, 1);
    int pos = mouse.x + firstPos - 1;
    pos = max(pos, 0);
    TStringView text = data;
    return TText::scroll(text, pos, False);
}

int TWrapInputLine::displayedPos(int pos)
{
    return strwidth(TStringView(data, pos));
}

void TWrapInputLine::deleteSelect()
{
    if (selStart < selEnd)
    {
        int len = strlen(data);
        memmove(data + selStart, data + selEnd, len - selEnd);
        data[len - selEnd + selStart] = EOS;
        curPos = selStart;
    }
}

void TWrapInputLine::deleteCurrent()
{
    TStringView text = data;
    if (curPos < (int) text.size())
    {
        selStart = curPos;
        selEnd = curPos + TText::next(text.substr(curPos));
        deleteSelect();
    }
}

void TWrapInputLine::adjustSelectBlock()
{
    if (curPos < anchor)
    {
        selStart = curPos;
        selEnd = anchor;
    } else
    {
        selStart = anchor;
        selEnd = curPos;
    }
}

void TWrapInputLine::saveState()
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

void TWrapInputLine::restoreState()
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

Boolean TWrapInputLine::checkValid(Boolean noAutoFill)
{
    int oldLen, newLen;
    char *newData;

    if (validator)
    {
        oldLen = strlen(data);
        newData = new char[256];
        strcpy(newData, data);
        if (!validator->isValidInput(newData, noAutoFill))
        {
            restoreState();
            delete[] newData;
            return False;
        } else
        {
            if (strlen(newData) > maxLen)
                newData[maxLen] = 0;
            strcpy(data, newData);
            newLen = strlen(data);
            if ((curPos >= oldLen) && (newLen > oldLen))
                curPos = newLen;
            delete[] newData;
            return True;
        }
    } else
        return True;
}

void TWrapInputLine::handleEvent(TEvent& event)
{
    Boolean extendBlock;
    /* Home, Left Arrow, Right Arrow, End, Ctrl-Left Arrow, Ctrl-Right Arrow */
    static char padKeys[] = {0x47, 0x4b, 0x4d, 0x4f, 0x73, 0x74, 0};
    TView::handleEvent(event);

    char keyText[ sizeof ( event.keyDown.text) + 1 ];
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
                if (strchr(padKeys, event.keyDown.charScan.scanCode) &&
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
                } else
                    extendBlock = False;

                switch (event.keyDown.keyCode)
                {
                    case kbLeft:
                        curPos -= TText::prev(TStringView(data), curPos);
                        break;
                    case kbRight:
                        curPos += TText::next(TStringView(data + curPos));
                        break;
                    case kbHome:
                        curPos = 0;
                        break;
                    case kbEnd:
                        curPos = strlen(data);
                        break;
                    case kbBack:
                        if (selStart != selEnd)
                        {
                            deleteSelect();
                            checkValid(True);
                        } else if (curPos > 0)
                        {
                            TStringView text = data;
                            int len = TText::prev(text, curPos);
                            memmove(data + curPos - len, data + curPos, text.size() - curPos + 1);
                            curPos -= len;
                            checkValid(True);
                        }
                        break;
                    case kbDel:
                        if (selStart == selEnd)
                            deleteCurrent();
                        else
                            deleteSelect();
                        checkValid(True);
                        break;
                    case kbIns:
                        setState(sfCursorIns, Boolean(!(state & sfCursorIns)));
                        break;
                    default:
                        // The event text may contain null characters, but 'data' is null-terminated,
                        // so rely on strlen to measure the text length.
                        strnzcpy(keyText, event.keyDown.getText(), sizeof ( keyText));
                        if ((len = strlen(keyText)) != 0)
                        {
                            deleteSelect();
                            if ((state & sfCursorIns) != 0)
                                deleteCurrent();

                            if (checkValid(True))
                            {
                                if (strlen(data) + len <= maxLen)
                                {
                                    if (firstPos > curPos)
                                        firstPos = curPos;
                                    memmove(data + curPos + len, data + curPos, strlen(data + curPos) + 1);
                                    memcpy(data + curPos, keyText, len);
                                    curPos += len;
                                }
                                checkValid(False);
                            }
                        } else if (event.keyDown.charScan.charCode == CONTROL_Y)
                        {
                            *data = EOS;
                            curPos = 0;
                        } else
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

void TWrapInputLine::selectAll(Boolean enable, Boolean scroll)
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

void TWrapInputLine::setData(void *rec)
{
    if ((validator == 0) || (validator->transfer(data, rec, vtSetData) == 0))
    {
        memcpy(data, rec, dataSize() - 1);
        data[dataSize() - 1] = EOS;
    }
    selectAll(True);
}

void TWrapInputLine::setState(ushort aState, Boolean enable)
{
    TView::setState(aState, enable);
    if (aState == sfSelected ||
            (aState == sfActive && (state & sfSelected) != 0)
            )
        selectAll(enable, False);
}

void TWrapInputLine::setValidator(TValidator* aValid)
{
    if (validator != 0)
        destroy(validator);

    validator = aValid;
}

#if !defined(NO_STREAMABLE)

void TWrapInputLine::write(opstream& os)
{
    TView::write(os);
    os << maxLen << curPos << firstPos
            << selStart << selEnd;
    os.writeString(data);
    os << validator;
}

void *TWrapInputLine::read(ipstream& is)
{
    TView::read(is);
    is >> maxLen >> curPos >> firstPos
            >> selStart >> selEnd;
    data = new char[maxLen + 1];
    oldData = new char[maxLen + 1];
    is.readString(data, maxLen + 1);
    state |= sfCursorVis;
    is >> (void*&) validator;
    return this;
}

TStreamable *TWrapInputLine::build()
{
    return new TWrapInputLine(streamableInit);
}

TWrapInputLine::TWrapInputLine(StreamableInit) noexcept : TView(streamableInit)
{
}

#endif

Boolean TWrapInputLine::valid(ushort cmd)
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



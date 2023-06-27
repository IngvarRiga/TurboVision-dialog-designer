#include "common.h"
#include "wmemo.h"

#define cpMemo      "\x1A\x1B"

TWrapMemo::TWrapMemo(const TRect& bounds,
             TScrollBar* aHScrollBar,
             TScrollBar* aVScrollBar,
             TIndicator* aIndicator,
             ushort aBufSize,
             bool click) noexcept :
    TEditor(bounds, aHScrollBar, aVScrollBar, aIndicator, aBufSize)
{

    eventMask = 0xFF; //-- ���������� ���� ��������� ���� ��������� �� ����
    state |= sfCursorVis;
    options |= ofSelectable | ofFirstClick;
    eventClick = click;
    eventDragged = false;
    Selected = false;
}

TWrapMemo::~TWrapMemo()
{

}

ushort TWrapMemo::dataSize()
{
    return bufSize + sizeof(ushort);
}

void TWrapMemo::getData(void* rec)
{
    TMemoData* data = (TMemoData*)rec;

    data->length = bufLen;
    memcpy(data->buffer, buffer, curPtr);
    memcpy(&data->buffer[curPtr], buffer + (curPtr + gapLen), bufLen - curPtr);
    memset(&data->buffer[bufLen], 0, bufSize - bufLen);
}

void TWrapMemo::setData(void* rec)
{
    TMemoData* data = (TMemoData*)rec;
    if (setBufSize(data->length))
    {
        memcpy(&buffer[bufSize - data->length], data->buffer, data->length);
        setBufLen(data->length);
    }
}

TPalette& TWrapMemo::getPalette() const
{
    static TPalette palette(cpMemo, sizeof(cpMemo) - 1);
    return palette;
}

TAttrPair TWrapMemo::getColor(ushort color)
{
    if (Selected)
        return color_SelectedColor;
    if (eventDragged)
        return color_DraggedColor;
    return TEditor::getColor(color);
}

void TWrapMemo::draw()
{
    if (drawLine != delta.y)
    {
        drawPtr = lineMove(drawPtr, delta.y - drawLine);
        drawLine = delta.y;
    }
    drawLines(0, size.y, drawPtr);
}

void TWrapMemo::drawLines(int y, int count, uint linePtr)
{
    TAttrPair color = color = getColor(0x0201);
#ifndef __FLAT__
    TScreenCell b[maxLineLength];
#else
    TScreenCell* b = (TScreenCell*)alloca(sizeof(TScreenCell) * (delta.x + size.x));
#endif

    while (count-- > 0)
    {
        formatLine(b, linePtr, delta.x + size.x, color);
        writeBuf(0, y, size.x, 1, &b[delta.x]);
        linePtr = nextLine(linePtr);
        y++;
    }
}

bool TWrapMemo::isSelected()
{
    return Selected;
}

void TWrapMemo::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}

void TWrapMemo::handleEvent(TEvent& event)
{
    if (eventClick)
    {
        if (event.what | evMouse)
        {
            //-- ������� �� ���� - ��������� � �������� ���������������� �������
            if ((event.mouse.buttons == mbLeftButton) && (event.what == evMouseDown))
            {
                //-- ����� ���������� ����� ������ � ���������� �����������
                auto pt = event.mouse.where;
                //-- ����������� �������� ������ �� ������������� ���������
                message(owner, evBroadcast, (ushort)TDDCommand::cm_cmp_CreateMemo, &pt);
                clearEvent(event);
            }
        }
    }
    if (eventDragged)
    {
        if (event.what | evMouse)
        {
            if (event.what == evMouseDown)
            {
                auto rec = getBounds();
                event.mouse.where.x = rec.a.x;
                event.mouse.where.y = rec.a.y + 1;
                TPoint MinSz, MaxSz;
                //-- ������������� ����������� ������� ������� � ������ ������� �������
                //-- ���, ����� ��������� �������� � ����������� �� �������� ������
                //-- �� ������� ������ (���� � ����� ������)
                auto lims = owner->getExtent();
                lims.grow(-1, -1);
                sizeLimits(MinSz, MaxSz);
                //-- ������ ����� � ���, ��� �� ������� ����������� �� ������� ������ ����� ����, ��� ������������ �������� ����
                dragView(event, dragMode | dmDragMove, lims, MinSz, MaxSz);
                clearEvent(event);

                TEvent evDrop;
                evDrop.what = evBroadcast;
                evDrop.message.command = (ushort)TDDCommand::cm_drp_DropMemo;
                TPoint* pt = new TPoint();
                pt->x = event.mouse.where.x;
                pt->y = event.mouse.where.y;
                evDrop.message.infoPtr = pt;
                putEvent(evDrop);
                clearEvent(event);
                auto parent = this->owner;
                destroy(this);
                parent->drawView();
                return;
            }
        }
    }
    if (Selected)
    {
        //-- �������������� �������� ������ � ������ ����������
        if (event.what == evKeyDown)
        {
            //-- ��������� ������� ��������� ������
            if (event.keyDown.keyCode == kbCtrlDel)
            {
                clearEvent(event);
                destroy(this);
                return;
            }
        }
    }

    //-- ��������� ��������� ���� ������ ���������, ����� �� ������ �������
    //if (event.what != evKeyDown || event.keyDown.keyCode != kbTab)
      //  TEditor::handleEvent(event);
}




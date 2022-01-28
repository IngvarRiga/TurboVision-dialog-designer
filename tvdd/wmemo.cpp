/*
#include "wmemo.h"
#include "common.h"

#define cpMemo      "\x1A\x1B"
const char* const TWrapMemo::name = "TWrapMemo";

TWrapMemo::TWrapMemo(const TRect& bounds,
             TScrollBar* aHScrollBar,
             TScrollBar* aVScrollBar,
             TIndicator* aIndicator,
             ushort aBufSize,
             bool click) noexcept :
    TEditor(bounds, aHScrollBar, aVScrollBar, aIndicator, aBufSize)
{

    eventMask = 0xFF; //-- установлен флаг получения ВСЕХ сообщений от мыши
    eventClick = click;
    eventDragged = false;
    Selected = false;
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
            //-- Реакция на клик - сообщение о создании перетаскиваемого объекта
            if ((event.mouse.buttons == mbLeftButton) && (event.what == evMouseDown))
            {
                //-- берем координаты клика мышкой в глобальных координатах
                auto pt = event.mouse.where;
                //-- обязательно отсылаем ссылку на редактируемый компонент
                message(owner, evBroadcast, cm_cmp_CreateMemo, &pt);
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
                //-- устанавливаем минимальные границы размера в размер хозяина объекта
                //-- так, чтобы изменение размеров и перемещение не выводило объект
                //-- за границы предка (окна в общем случае)
                auto lims = owner->getExtent();
                lims.grow(-1, -1);
                sizeLimits(MinSz, MaxSz);
                //-- адский косяк в том, что из функции перемещения мы выходим только ПОСЛЕ того, как пользователь отпустил мышь
                dragView(event, dragMode | dmDragMove, lims, MinSz, MaxSz);
                clearEvent(event);

                TEvent evDrop;
                evDrop.what = evBroadcast;
                evDrop.message.command = cm_drp_DropMemo;
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
        //-- переопределяем действия клавиш в режиме разработки
        if (event.what == evKeyDown)
        {
            //-- обработка нажатий служебных клавиш
            if (event.keyDown.keyCode == kbCtrlDel)
            {
                clearEvent(event);
                destroy(this);
                return;
            }
        }
    }

    //-- блокируем обработку всех команд враппером, чтобы не мешать дизайну
    //if (event.what != evKeyDown || event.keyDown.keyCode != kbTab)
      //  TEditor::handleEvent(event);
}

#if !defined(NO_STREAMABLE)

void TWrapMemo::write(opstream& os)
{
    TEditor::write(os);
    os << bufLen;
    os.writeBytes(buffer, curPtr);
    os.writeBytes(buffer + gapLen, bufLen - curPtr);
}

void* TWrapMemo::read(ipstream& is)
{
    TEditor::read(is);
    uint length;
    is >> length;
    if (isValid)
    {
        is.readBytes(buffer + bufSize - length, length);
        setBufLen(length);
    }
    else
        is.seekg(is.tellg() + (streamoff)length);
    return this;
}

TStreamable* TWrapMemo::build()
{
    return new TWrapMemo(streamableInit);
}

TWrapMemo::TWrapMemo(StreamableInit) noexcept : TEditor(streamableInit)
{}

TStreamableClass RWrapMemo(TWrapMemo::name,
                       TWrapMemo::build,
                       __DELTA(TWrapMemo)
);

__link(RView)
__link(REditor)
__link(RWindow)
__link(RScrollBar)

#endif
*/


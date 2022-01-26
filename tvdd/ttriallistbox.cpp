#include "ttriallistbox.h"
#include "common.h"

const char * const TTrialListBox::name = "TTrialListBox";

TTrialListBox::TTrialListBox(const TRect& bounds, ushort aNumCols, TScrollBar *aScrollBar):
TListBox( bounds, aNumCols, aScrollBar)
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;

}

void TTrialListBox::draw()
{
    //-- полностью переопределяем процедуру отрисовки, поскольку в дизайнере нам нужны некоторые спецэффекты
    TListBox::draw();
}

void TTrialListBox::setState(ushort aState, Boolean enable)
{
    TView::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

void TTrialListBox::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_ListBox, nullptr);
            clearEvent(event);
        }
        if (event.what == evMouseDown)
        {
            owner->forEach(&unselected, 0);
            setState(sfSelected, true);
            select();
            DragObject(this, event);
            clearEvent(event);
        }
    }

    TListBox::handleEvent(event);
}

void TTrialListBox::sizeLimits(TPoint& min, TPoint& max)
{
    TListBox::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}

bool TTrialListBox::isSelected()
{
    return Selected;
}

void TTrialListBox::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}

void TTrialListBox::genCode(char *val)
{
    //-- генерируем код компонента
    //        auto t="\n insert(new TStaticText(TRect(";
    //        strcat(s,t,strlen(t));
    //        auto r = to->getBounds();
}

TStreamable *TTrialListBox::build()
{
    return new TTrialListBox(streamableInit);
}

void TTrialListBox::write(opstream& os)
{

    TListBox::write(os);
    os << eventMask << options << dragMode;
}

void *TTrialListBox::read(ipstream& is)
{
    TListBox::read(is);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialListBox(
        TTrialListBox::name,
        TTrialListBox::build,
        __DELTA(TTrialListBox)
        );

__link(RListBox)
__link(RTrialListBox)



#include "ttriallistbox.h"

const char * const TTrialListBox::name = "TTrialListBox";

TTrialListBox::TTrialListBox(const TRect& bounds, ushort aNumCols, TScrollBar *aScrollBar):
TListBox( bounds, aNumCols, aScrollBar)
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TListBox, strlen(txt_TListBox));

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
            DragObject(this, event);
            clearEvent(event);
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

void TTrialListBox::genCode(void *val)
{
    ofstream* res = (ofstream*)val;
    auto r = getBounds();

    //-- генерируем код компонента
    *res << "\n " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), 1, nullptr );";
    *res << "\n insert(" << var_name << ");";

}

TStreamable *TTrialListBox::build()
{
    return new TTrialListBox(streamableInit);
}

void TTrialListBox::write(opstream& os)
{

    TListBox::write(os);
    os.writeBytes((void*)var_name, StringMaxLen);
    os.writeBytes((void*)class_name, StringMaxLen);
    os << eventMask << options << dragMode;
}

void *TTrialListBox::read(ipstream& is)
{
    TListBox::read(is);
    is.readBytes((void*)var_name, StringMaxLen);
    is.readBytes((void*)class_name, StringMaxLen);
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



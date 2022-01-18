#include "ttrialbutton.h"
#include "common.h"

const char * const TTrialButton::name = "TTrialButton";

TTrialButton::TTrialButton(const TRect& bounds,
        TStringView aTitle,
        ushort aCommand,
        ushort aFlags) :
TButton(bounds, aTitle, aCommand, aFlags)
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;
}

void TTrialButton::draw()
{
    TButton::draw();
}

void TTrialButton::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_Button, nullptr);
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

    TButton::handleEvent(event);
}

void TTrialButton::sizeLimits(TPoint& min, TPoint& max)
{
    TButton::sizeLimits(min, max);
    min.x = 5; //-- минимальная ширина = 5 символов - для одного символа на самой кнопке
    min.y = 2; //-- высота ограничена константой
    max.x -= 2;
    //-- строка ввода занимает только одну строчку!
    max.y = 2;
}

bool TTrialButton::isSelected()
{
    return Selected;
}

void TTrialButton::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}
void TTrialButton::genCode(char *val)
{
    //-- генерируем код компонента
    char tmp[StringMaxLen];
    memset(tmp, 0x0, StringMaxLen);
    auto t = "\n insert(new TButton(TRect(";
    strncat(val, t, strlen(t));
    auto r = getBounds();
    itoa(r.a.x, tmp, 10);
    strncat(val, tmp, strlen(tmp));
    strncat(val, ",", 1);
    memset(tmp, 0x0, StringMaxLen);

    itoa(r.a.y, tmp, 10);
    strncat(val, tmp, strlen(tmp));
    strncat(val, ",", 1);
    memset(tmp, 0x0, StringMaxLen);

    itoa(r.b.x, tmp, 10);
    strncat(val, tmp, strlen(tmp));
    strncat(val, ",", 1);
    memset(tmp, 0x0, StringMaxLen);
    
    itoa(r.b.y, tmp, 10);
    strncat(val, tmp, strlen(tmp));
    memset(tmp, 0x0, StringMaxLen);

    strncat(val, "), \"", 4);
    strncat(val, title, strlen(title));
    memset(tmp, 0x0, StringMaxLen);
    strncat(val, "\", -1, -1));", 11);

}

TStreamable *TTrialButton::build()
{
    return new TTrialButton(streamableInit);
}

void TTrialButton::write(opstream& os)
{

    TButton::write(os);
    os << eventMask << options << dragMode;
}

void *TTrialButton::read(ipstream& is)
{
    TButton::read(is);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialButton(
        TTrialButton::name,
        TTrialButton::build,
        __DELTA(TTrialButton)
        );

__link(RButton)
__link(RTrialButton)


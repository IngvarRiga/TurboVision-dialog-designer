#include "ttrialradiobuttons.h"
#include "common.h"

const char * const TTrialRadioButtons::name = "TTrialRadioButtons";

TTrialRadioButtons::TTrialRadioButtons(const TRect& bounds, TSItem *aStrings) :
TWrapRadioButtons(bounds, aStrings)
{

    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
}


void TTrialRadioButtons::setState(ushort aState, Boolean enable)
{
    TWrapRadioButtons::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

void TTrialRadioButtons::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_RadioButtons, this);
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

    TWrapRadioButtons::handleEvent(event);
}

void TTrialRadioButtons::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapRadioButtons::sizeLimits(min, max);
    min.x = 5;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}


void TTrialRadioButtons::genCode(char *val)
{
    //-- генерируем код компонента
    //        auto t="\n insert(new TStaticText(TRect(";
    //        strcat(s,t,strlen(t));
    //        auto r = to->getBounds();
}

TStreamable *TTrialRadioButtons::build()
{
    return new TTrialRadioButtons(streamableInit);
}

void TTrialRadioButtons::write(opstream& os)
{

    TWrapRadioButtons::write(os);
    os << eventMask << options << dragMode;
}

void *TTrialRadioButtons::read(ipstream& is)
{
    TWrapRadioButtons::read(is);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialRadioButtons(
        TTrialRadioButtons::name,
        TTrialRadioButtons::build,
        __DELTA(TTrialRadioButtons)
        );

__link(RWrapRadioButtons)
__link(RTrialRadioButtons)
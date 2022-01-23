#include "ttrialcheckboxes.h"
#include "common.h"

const char * const TTrialCheckBoxes::name = "TTrialCheckBoxes";

TTrialCheckBoxes::TTrialCheckBoxes(const TRect& bounds, TSItem *aStrings) :
TCheckBoxes(bounds, aStrings)
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;
}

void TTrialCheckBoxes::draw()
{
    TCheckBoxes::draw();
}

void TTrialCheckBoxes::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_CheckBoxes, nullptr);
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

    TCheckBoxes::handleEvent(event);
}

void TTrialCheckBoxes::sizeLimits(TPoint& min, TPoint& max)
{
    TCheckBoxes::sizeLimits(min, max);
    min.x = 5;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}

bool TTrialCheckBoxes::isSelected()
{
    return Selected;
}

void TTrialCheckBoxes::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}
void TTrialCheckBoxes::genCode(char *val)
{
    //-- генерируем код компонента
    //        auto t="\n insert(new TStaticText(TRect(";
    //        strcat(s,t,strlen(t));
    //        auto r = to->getBounds();
}

TStreamable *TTrialCheckBoxes::build()
{
    return new TTrialCheckBoxes(streamableInit);
}

void TTrialCheckBoxes::write(opstream& os)
{

    TCheckBoxes::write(os);
    os << eventMask << options << dragMode;
}

void *TTrialCheckBoxes::read(ipstream& is)
{
    TCheckBoxes::read(is);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialCheckBoxes(
        TTrialCheckBoxes::name,
        TTrialCheckBoxes::build,
        __DELTA(TTrialCheckBoxes)
        );

__link(RCheckBoxes)
__link(RTrialCheckBoxes)
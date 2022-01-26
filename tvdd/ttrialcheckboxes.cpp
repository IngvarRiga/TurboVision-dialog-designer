#include "ttrialcheckboxes.h"
#include "common.h"

const char * const TTrialCheckBoxes::name = "TTrialCheckBoxes";

TTrialCheckBoxes::TTrialCheckBoxes(const TRect& bounds, TSItem *aStrings) :
TWrapCheckBoxes(bounds, aStrings)
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TCheckBoxes, strlen(txt_TCheckBoxes));

}

void TTrialCheckBoxes::setState(ushort aState, Boolean enable)
{
    TWrapCheckBoxes::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

void TTrialCheckBoxes::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_CheckBoxes, this);
            clearEvent(event);
        }
        if (event.what == evMouseDown)
        {
            owner->forEach(&unselected, 0);
            setSelected(true);
            DragObject(this, event);
            clearEvent(event);
        }
    }

    TWrapCheckBoxes::handleEvent(event);
}

void TTrialCheckBoxes::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapCheckBoxes::sizeLimits(min, max);
    min.x = 5;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}

void TTrialCheckBoxes::genCode(char *val)
{
    //-- генерируем код компонента
    //        auto t="\n insert(new TStaticText(TRect(";
    //        strcat(s,t,strlen(t));
    //        auto r = to->getBounds();
}

char* TTrialCheckBoxes::getVarName()
{
    return var_name;
}


void TTrialCheckBoxes::setClassName(char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialCheckBoxes::getClassName()
{
    return class_name;
}

void TTrialCheckBoxes::setVarName(char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}


TStreamable *TTrialCheckBoxes::build()
{
    return new TTrialCheckBoxes(streamableInit);
}

void TTrialCheckBoxes::write(opstream& os)
{

    TWrapCheckBoxes::write(os);
    os << eventMask << options << dragMode;
}

void *TTrialCheckBoxes::read(ipstream& is)
{
    TWrapCheckBoxes::read(is);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialCheckBoxes(
        TTrialCheckBoxes::name,
        TTrialCheckBoxes::build,
        __DELTA(TTrialCheckBoxes)
        );

__link(RWrapCheckBoxes)
__link(RTrialCheckBoxes)
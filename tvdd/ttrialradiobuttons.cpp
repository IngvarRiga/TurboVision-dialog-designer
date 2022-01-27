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

    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TRadioButtons, strlen(txt_TRadioButtons));
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


void TTrialRadioButtons::genCode(void *val)
{
    ofstream* res = (ofstream*)val;

    //-- генерируем код компонента
    auto r = getBounds();
    *res << "\n auto " << var_name << " = new TRadioButtons(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \n";
    auto itm = getItems();
    auto cnt = itm->getCount();
    for (int i = 0; i < (cnt - 1); i++)
    {
        *res << "   new TSItem(\"" << (char*)itm->at(i) << "\",\n";
    }
    *res << "   new TSItem(\"" << (char*)itm->at(cnt - 1) << "\", 0)";

    for (int i = 0; i < (cnt - 1); i++)
    {
        *res << ")";
    }
    *res << ");\n";
    *res << "\n insert(" << var_name << ");\n";
}
char* TTrialRadioButtons::getVarName()
{
    return var_name;
}


void TTrialRadioButtons::setClassName(char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialRadioButtons::getClassName()
{
    return class_name;
}

void TTrialRadioButtons::setVarName(char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}

TStreamable *TTrialRadioButtons::build()
{
    return new TTrialRadioButtons(streamableInit);
}

void TTrialRadioButtons::write(opstream& os)
{

    TWrapRadioButtons::write(os);
    os.writeBytes((void*)var_name, StringMaxLen);
    os.writeBytes((void*)class_name, StringMaxLen);
    os << eventMask << options << dragMode;
}

void *TTrialRadioButtons::read(ipstream& is)
{
    TWrapRadioButtons::read(is);
    is.readBytes((void*)var_name, StringMaxLen);
    is.readBytes((void*)class_name, StringMaxLen);
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
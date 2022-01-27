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

void TTrialCheckBoxes::genCode(void *val)
{
    ofstream* res = (ofstream*)val;

    //-- генерируем код компонента
    auto r = getBounds();
    *res << "\n auto " << var_name << " = new TCheckBoxes(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \n";
    auto itm = getItems();
    auto cnt = itm->getCount();
    for (int i = 0; i < (cnt-1); i++)
    {
        *res << "   new TSItem(\"" << (char*)itm->at(i) << "\",\n";
    }
    *res << "   new TSItem(\"" << (char*)itm->at(cnt-1) << "\", 0)";

    for (int i = 0; i < (cnt - 1); i++)
    {
        *res << ")";
    }
    *res << ");\n";
    *res << "\n insert(" << var_name << ");\n";
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
    os.writeBytes((void*)var_name, StringMaxLen);
    os.writeBytes((void*)class_name, StringMaxLen);
    os << eventMask << options << dragMode;
}

void *TTrialCheckBoxes::read(ipstream& is)
{
    TWrapCheckBoxes::read(is);
    is.readBytes((void*)var_name, StringMaxLen);
    is.readBytes((void*)class_name, StringMaxLen);
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
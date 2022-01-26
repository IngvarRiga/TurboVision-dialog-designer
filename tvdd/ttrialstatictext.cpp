#include "ttrialstatictext.h"
#include "common.h"


const char * const TTrialStaticText::name = "TTrialStaticText";

TTrialStaticText::TTrialStaticText(const TRect& bounds, TStringView aText) :
TWrapStaticText(bounds, aText)
{
    eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    //-- заданное имя переменной используется при генерации кода
    usedVarName = false; //-- по умолчанию -выключено!
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TStaticText, strlen(txt_TStaticText));
}

void TTrialStaticText::setState(ushort aState, Boolean enable)
{
    TView::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

void TTrialStaticText::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            //-- обязательно отсылаем ссылку на редактируемый компонент
            message(owner, evBroadcast, cmOption_StaticText, this);
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

    TWrapStaticText::handleEvent(event);
}

void TTrialStaticText::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapStaticText::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}

char* TTrialStaticText::getVarName()
{
    return var_name;
}

char* TTrialStaticText::getClassName()
{
    return class_name;
}

bool TTrialStaticText::getUsedVarName()
{
    return usedVarName;
}

void TTrialStaticText::setVarName(char *val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialStaticText::setClassName(char *val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialStaticText::setUsedVarName(bool val)
{
    usedVarName = val;
}

void TTrialStaticText::genCode(void *val)
{
    ofstream *res = (ofstream*)val;

    //-- генерируем код компонента
    auto r = getBounds();
    if (usedVarName)
    {
        *res << "\n auto " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << text << "\");";
        *res << "\n insert(" << var_name << ");\n";
    }
    else
    {
        *res << "\n insert(new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << text << "\"));\n";
    }
}

TStreamable *TTrialStaticText::build()
{
    return new TTrialStaticText(streamableInit);
}

void TTrialStaticText::write(opstream& os)
{

    TWrapStaticText::write(os);
    os.writeBytes(&usedVarName, sizeof (usedVarName));
    os.writeBytes((void *) var_name, StringMaxLen);
    os.writeBytes((void *) class_name, StringMaxLen);
    os << eventMask << options << dragMode;
}

void *TTrialStaticText::read(ipstream& is)
{
    TWrapStaticText::read(is);
    is.readBytes(&usedVarName, sizeof (usedVarName));
    is.readBytes((void *) var_name, StringMaxLen);
    is.readBytes((void *) class_name, StringMaxLen);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialStaticText(
        TTrialStaticText::name,
        TTrialStaticText::build,
        __DELTA(TTrialStaticText)
        );

__link(RWrapStaticText)
__link(RTrialStaticText)



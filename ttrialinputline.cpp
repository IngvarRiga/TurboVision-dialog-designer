#include "ttrialinputline.h"
#include "common.h"

const char * const TTrialInputLine::name = "TTrialInputLine";

TTrialInputLine::TTrialInputLine(const TRect& bounds, uint aMaxLen, TValidator *aValid) :
TWrapInputLine(bounds, aMaxLen, aValid)
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;
    memset(var_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
}

//void TTrialInputLine::draw()
//{
//    TWrapInputLine::draw();
//}

void TTrialInputLine::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {

        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_InputLine, this);
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

    TWrapInputLine::handleEvent(event);
}

void TTrialInputLine::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapInputLine::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    //-- строка ввода занимает только одну строчку!
    max.y = 1;
}

bool TTrialInputLine::isSelected()
{
    return Selected;
}

void TTrialInputLine::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}

void TTrialInputLine::genCode(char *val)
{
    //-- генерируем код компонента
    char tmp[StringMaxLen];
    memset(tmp, 0x0, StringMaxLen);
    auto t = "\n field = new TInputLine(TRect(";
    auto endl ="), 11));\n insert(field);";
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

    strncat(val, endl, strlen(endl));
    memset(tmp, 0x0, StringMaxLen);
}

TStreamable *TTrialInputLine::build()
{
    return new TTrialInputLine(streamableInit);
}

char* TTrialInputLine::getVarName()
{
    return var_name;
}

uint TTrialInputLine::getVarLen()
{
    return maxLen;
}

void TTrialInputLine::setVarName(char *val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}



void TTrialInputLine::setVarLen(uint val)
{
   maxLen = val;
}

void TTrialInputLine::write(opstream& os)
{

    TWrapInputLine::write(os);
    os << eventMask << options << dragMode;
    os.writeBytes((void *) var_name, StringMaxLen);
}

void *TTrialInputLine::read(ipstream& is)
{
    TWrapInputLine::read(is);
    is >> eventMask >> options >> dragMode;
    is.readBytes((void *) var_name, StringMaxLen);
    return this;
}


TStreamableClass RTrialInputLine(
        TTrialInputLine::name,
        TTrialInputLine::build,
        __DELTA(TTrialInputLine)
        );

__link(RWrapInputLine)
__link(RTrialInputLine)



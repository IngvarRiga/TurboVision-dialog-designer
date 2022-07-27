#include "textrainput.h"
//#include <strstream>
#include <string>
using namespace std;

TInputLong::TInputLong(const TRect& bounds, long MinValue, long MaxValue, long DefValue) :
    TInputLine(bounds, 12)
{
    //-- устанавливаем правильные значения
    if (MinValue < MaxValue)
    {
        minv = MinValue;
        maxv = MaxValue;
    }
    else
    {
        //-- если неправильно заданы, то устанавливаем значения по умолчанию
        minv = LONG_MIN;
        maxv = LONG_MAX;
        messageBox(mfError | mfOKButton, "MinValue >= MaxValue!");
    }
    if (CheckValue(DefValue))
        value = DefValue;
    else
    {
        std::string str = txt_Range_error3 + std::to_string(minv) + txt_Range_error2 + std::to_string(maxv);
        messageBox(str.c_str(), mfError | mfOKButton);
        if (CheckValue(0))
            value = DefValue;
        else
            //-- усредняем
            value = (maxv + minv) / 2L;
    }
    TInputLine::setData((void*)to_string(value).c_str());
}

bool TInputLong::CheckValue(long val)
{
    if ((val >= minv) && (val <= maxv))
        return true;
    else
        return false;
}

void TInputLong::setValue(long val)
{
    //-- если не равно уже установленному...
    if (val != value)
    {
        if (CheckValue(val))
            value = val;
        if (val > maxv)
            value = maxv;
        if (val < minv)
            value = minv;
        TInputLine::setData((void*)to_string(value).c_str());
    }
}

bool TInputLong::convertl(const char* tmp, long* out)
{
    if (strlen(tmp) == 0) return false;
    char* ptr;
    errno = 0;
    auto res = strtol(tmp, &ptr, 10);
    if (ptr == tmp) return false;
    if (errno == ERANGE) return false;
    *out = res;
    return true;
}

void  TInputLong::handleEvent(TEvent& event)
{
    long vl = 0;
    int ocp = 0;
    char tmp[100];
    char* pt;
    memset(tmp, 0x0, 100);

    if (event.what == evKeyDown)
    {
        switch (event.keyDown.keyCode)
        {
            //-- перемещение курсора
            case kbLeft:
            case kbRight:
            case kbCtrlRight:
            case kbCtrlLeft:
                TInputLine::handleEvent(event);
                clearEvent(event);
                break;
            case kbDel:
            case kbCtrlDel:
            case kbShiftDel:
            case kbCtrlBack:
            case kbAltDel:
            case kbAltBack:
            case kbBack:
                TInputLine::handleEvent(event);
                ocp = curPos;
                TInputLine::getData(tmp);
                vl = strtol(tmp, &pt, 10);
                if (*pt)
                    setValue(value);
                else
                    setValue(vl);
                selectAll(false);
                setCursor(ocp + 1, 0);
                curPos = ocp;
                clearEvent(event);
                break;
            default:
                break;
        }
        switch (event.keyDown.charScan.charCode)
        {
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
            case 56:
            case 57:
                ocp = curPos; //-- старая позиция курсора
                TInputLine::handleEvent(event);//-- обрабатываем событие ввода данных
                TInputLine::getData(tmp);
                if (convertl(tmp, &vl) && CheckValue(vl))
                {
                    value = vl;
                }
                else
                {
                    setValue(value);
                    selectAll(false);
                    setCursor(ocp + 1, 0);
                    curPos = ocp;
                    std::string str = txt_Range_error1 + std::to_string(minv) + txt_Range_error2 + std::to_string(maxv);
                    messageBox(str.c_str(), mfError | mfOKButton);
                }
                clearEvent(event);
                break;
            case 43:
                //-- "+" 
                if (value < 0)
                {
                    ocp = curPos;
                    long tm = fabsl(value);
                    if (CheckValue(tm))
                    {
                        setValue(tm);
                        selectAll(false);
                        setCursor(ocp, 0);
                        curPos = ocp - 1;
                    }
                    else
                    {
                        std::string str = txt_Range_error1 + std::to_string(minv) + txt_Range_error2 + std::to_string(maxv);
                        messageBox(str.c_str(), mfError | mfOKButton);
                    }
                }
                clearEvent(event);
                break;
            case 45:
                //-- "-"
                {
                    ocp = curPos;
                    long tm = -value;
                    if (CheckValue(tm))
                    {
                        setValue(tm);
                        selectAll(false);
                        if (value > 0)
                        {
                            setCursor(ocp, 0);
                            curPos = ocp - 1;
                        }
                        if (value < 0)
                        {
                            ocp += 1;
                            setCursor(ocp + 1, 0);
                            curPos = ocp;
                        }
                    }
                    else
                    {
                        std::string str = txt_Range_error1 + std::to_string(minv) + txt_Range_error2 + std::to_string(maxv);
                        messageBox(str.c_str(), mfError | mfOKButton);
                    }
                }
                clearEvent(event);
                break;
            default:
                break;
        }
        return;
    }
    TInputLine::handleEvent(event);
}


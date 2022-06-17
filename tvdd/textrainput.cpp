#include "textrainput.h"
#include <strstream>
#include <string>
using namespace std;
/*
 TInputInteger - ввод целого положительного или отрицательного числа с ограничением вода по диапазону

*/

TInputInteger::TInputInteger(const TRect& bounds, long vDef, long vMin, long vMax)
    :TInputLine(bounds, 12)
{
    if (vMin < vMax)
    {
        minValue = vMin;
        maxValue = vMax;
    }
    else
    {
        minValue = LONG_MIN;
        maxValue = LONG_MAX;
    }
    if (CheckValue(vDef))
        Value = vDef;
    else
        Value = (vMax + vMin) / 2L;
    TInputLine::setData((void*)to_string(Value).c_str());
}

bool TInputInteger::CheckValue(long val)
{
    if ((val >= minValue) && (val <= maxValue))
        return true;
    else
        return false;
}

long TInputInteger::getValue()
{
    return Value;
}

void TInputInteger::setValue(long val)
{
    if (CheckValue(val))
    {
        Value = val;
        TInputLine::setData((void*)to_string(Value).c_str());
    }
}

bool TInputInteger::convertl(const char* tmp, long* out)
{
    char* ptr;
    errno = 0;
    auto res = strtol(tmp, &ptr, 10);
    if (ptr == tmp)return false;
    if (strlen(tmp) == 0)return false;
    if (errno == ERANGE)  return false;
    *out = res;
    return true;
}

bool TInputInteger::valid(ushort command)
{
    /*   int value;
       Boolean ok;
       char msg[80];
       std::ostrstream os(msg, 80);

       ok = True;
       if ((command != cmCancel) && (command != cmValid))
       {
           if (strlen(data) == 0)
               strcpy(data, "0");

           value = (int)strtol(data, NULL, 0);
           if (value < userMin || value > userMax)
           {
               select();
               os << "Number outside range " << userMin
                   << ".." << userMax << std::ends;
               messageBox(os.str(), mfError + mfOKButton);
               selectAll(True);
               ok = False;
           }
       }
       if (ok)
           return TInputLine::valid(command);
       else
           return False;*/
    return true;
}

//void TInputInteger::handleEvent(TEvent& event)
//{
//    long vl = 0;
//    size_t len = 0;
//    long tst = 0;
//    int ocp = 0;
//    char tmp[100];
//    char tmp1[100];
//    char* pt;
//    memset(tmp, 0x0, 100);
//    memset(tmp1, 0x0, 100);
//
//    //-- берём текущее значение
//    TInputLine::getData(tmp);
//    ocp = curPos;
//    TInputLine::handleEvent(event);
//    //-- берём обновлённое значение
//    TInputLine::getData(tmp1);
//    if (convertl(tmp1, &tst))
//    {
//        if (CheckValue(tst))
//        {
//            //ocp = curPos;
//            //TInputLine::getData(tmp);
//            //vl = strtol(tmp, &pt, 10);
//            //if (*pt)
//            //    setValue(Value);
//            //else
//            //    setValue(vl);
//            //selectAll(false);
//            //setCursor(ocp + 1, 0);
//            //curPos = ocp;
//        }
//        else
//        {
//            TInputLine::setData(tmp);
//            selectAll(false);
//            setCursor(ocp, 0);
//            curPos = ocp;
//        }
//    }
//    else
//    {
//        TInputLine::setData(tmp);
//        selectAll(false);
//        setCursor(ocp, 0);
//        curPos = ocp;
//    }
//    clearEvent(event);
//}
void TInputInteger::handleEvent(TEvent& event)
{
    long vl = 0;
    size_t len = 0;
    long tst = 0;
    int ocp = 0;
    char tmp[100];
    char tmp_old[100];
    char* pt;
    memset(tmp, 0x0, 100);
    memset(tmp_old, 0x0, 100);

    if (event.what == evKeyDown)
    {
        switch (event.keyDown.keyCode)
        {
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
                    setValue(Value);
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
                //-- берём текущее значение
                TInputLine::getData(tmp_old);
                ocp = curPos;
                TInputLine::handleEvent(event);
                TInputLine::getData(tmp);
                if (convertl(tmp, &vl) && CheckValue(vl))
                {
                    ocp = curPos;
                    setValue(vl);
                    selectAll(false);
                    setCursor(ocp+1, 0);
                    curPos = ocp;
                }
                else
                {
                    setValue(Value);
                    selectAll(false);
                    setCursor(ocp + 1, 0);
                    curPos = ocp;
                }
                clearEvent(event);
                break;
            case 43:
                //-- нажатие знака "+"
                ocp = (Value < 0 ? 1 : 0) + curPos;
                setValue(fabsl(Value));
                TInputLine::getData(tmp);
                len = strlen(tmp);
                vl = strtol(tmp, &pt, 10);
                if (vl > 0 && vl < 10)
                    len = 1;
                selectAll(false);
                setCursor(len + 1, 0);
                curPos = len;
                clearEvent(event);
                break;
            case 45:
                //-- нажатие знака "-"
                ocp = curPos;
                TInputLine::getData(tmp);
                vl = strtol(tmp, &pt, 10);
                setValue(-Value);
                selectAll(false);
                if (Value < 0)
                {
                    ocp += 1;
                    setCursor(ocp + 1, 0);
                    curPos = ocp;
                }
                else
                {
                    ocp -= 1;
                    setCursor(ocp + 1, 0);
                    curPos = ocp;
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


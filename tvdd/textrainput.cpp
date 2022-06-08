#include "textrainput.h"
#include <strstream>
#include <string>
using namespace std;
/************************************************************************
** TInputInteger
**
**	Accepts signed integer inputs.  Also accepts hexadecimal numbers
** if expressed in the format "0x000..."
**
*************************************************************************/

TInputInteger::TInputInteger(const TRect& bounds, long vDef, long vMin, long vMax)
    :TInputLine(bounds, 11)
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
    return false;
}

void TInputInteger::handleEvent(TEvent& event)
{
    long vl = 0;
    int len = 0;
    int ocp = 0;
    char tmp[100];
    char* pt;
    memset(tmp, 0x0, 100);

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
                TInputLine::getData(tmp);
                len = strlen(tmp);
                len = len == 0 ? 1 : len;
                vl = strtol(tmp, &pt, 10);
                if (*pt)
                    setValue(Value);
                else
                {
                    setValue(vl);
                    selectAll(false);
                    setCursor(len + 1, 0);
                    curPos = len;
                }
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
                TInputLine::handleEvent(event);
                ocp = curPos;
                TInputLine::getData(tmp);
                len = strlen(tmp);
                vl = strtol(tmp, &pt, 10);
                if (vl > 0 && vl < 10)
                    len = 1;
                if (*pt)
                    setValue(Value);
                else
                {
                    setValue(vl);
                    selectAll(false);
                    setCursor(len + 1, 0);
                    curPos = len ;
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
                ocp = (Value < 0 ? 1 : 0) + curPos;
                TInputLine::getData(tmp);
                len = strlen(tmp);
                vl = strtol(tmp, &pt, 10);
                if (vl > 0 && vl < 10)
                    len = 1;
                setValue(-Value);
                selectAll(false);
                ocp = (Value < 0 ? 1 : 0) + ocp;
                setCursor(ocp + 1, 0);
                curPos = ocp;
                clearEvent(event);
                break;
            default:
                break;
        }
        return;
    }
    TInputLine::handleEvent(event);

}


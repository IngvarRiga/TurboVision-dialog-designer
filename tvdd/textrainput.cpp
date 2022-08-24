#include "textrainput.h"
#include <string>
using namespace std;

const int ev_FocusChanged = 1000001; //-- событие смены фокуса


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
        ShowError();
        if (CheckValue(0))
            value = DefValue;
        else
            //-- усредняем
            value = (maxv + minv) / 2L;
    }
    TInputLine::setData((void*)to_string(value).c_str());
}

void TInputLong::ShowError()
{
    std::string str = txt_Range_error3 + std::to_string(minv) + txt_Range_error2 + std::to_string(maxv);
    messageBox(str.c_str(), mfError | mfOKButton);
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
        drawView();
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
    std::string vals;
    long vl = 0;
    long vl_old = 0;
    int ocp = 0;
    char tmp[12]; //-- 12 символов максимальная длина  целого со знаком '-'
    char* pt;
    bool res = false;
    memset(tmp, 0x0, 12);
    if (event.what == evKeyDown)
    {
        switch (event.keyDown.keyCode)
        {
            //-- перемещение курсора
            case kbLeft:
            case kbRight:
            case kbCtrlRight:
            case kbCtrlLeft:
            case kbEnd:
            case kbHome:
            case kbTab:
            case kbShiftTab:
            case kbCtrlTab:
            case kbAltTab:
                TInputLine::handleEvent(event);
                clearEvent(event);
                break;
            case kbDel:
            case kbCtrlDel:
            case kbShiftDel:
            case kbAltDel:

            case kbCtrlBack:
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
                {
                    if (selStart == selEnd)
                    {
                        ocp = curPos; //-- старая позиция курсора
                        vl_old = value;

                        TInputLine::getData(tmp);
                        vals = tmp;
                        vals.insert(curPos, 1, char(event.keyDown.charScan.charCode));
                        res = convertl(vals.c_str(), &vl);
                        if (res && CheckValue(vl))
                        {
                            TInputLine::handleEvent(event);//-- обрабатываем событие ввода данных
                            value = vl;
                            ocp = curPos + 1;
                            setCursor(ocp, 0);
                        }
                        else
                            ShowError();
                    }
                    else
                    {
                        TInputLine::handleEvent(event);
                    }
                    clearEvent(event);
                    break;
                }
            case 43:
                //-- "+" 
                if (value < 0)
                {
                    //-- берём текстовые данные
                    memset(tmp, 0x0, 12); //-- очистка
                    TInputLine::getData(tmp);
                    vals = tmp;
                    //-- если предыдущее значение отрицательное - убираем '-'
                    vals = vals.substr(1, vals.length());
                    //-- пытаемся конвертировать получившийся результат в число
                    res = convertl(vals.c_str(), &vl);
                    //-- невозможность конвертации числа может быть обусловлена тем, что результат превышает максимальное / минимальное
                    //-- допустимое значение для данного типа LONG_MAX / LONG_MIN
                    if (res)
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
                            ShowError();
                    }
                }
                clearEvent(event);
                break;
            case 45:
                //-- "-"
                {
                    //-- берём текстовые данные
                    memset(tmp, 0x0, 12); //-- очистка
                    TInputLine::getData(tmp);
                    vals = tmp;
                    if (vals == "0")
                    {
                        //TInputLine::handleEvent(event);
                        return;
                    }
                    if (value > 0)
                        //-- если предыдущее значение положительно - добавляем '-'
                        vals.insert(0, 1, '-');
                    else
                        //-- если предыдущее значение отрицательное - убираем -
                        vals = vals.substr(1, vals.length());
                    //-- пытаемся конвертировать получившийся результат в число
                    res = convertl(vals.c_str(), &vl);
                    //-- невозможность конвертации числа может быть обусловлена тем, что результат превышает максимальное / минимальное
                    //-- допустимое значение для данного типа LONG_MAX / LONG_MIN
                    if (res)
                    {
                        ocp = curPos; //-- сохраняем позицию курсора
                        //-- если успешно....
                        long tm = -value; //-- проверяем на не превышение заданных пользователем ограничений
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
                                setCursor(ocp + 2, 0);
                                curPos = ocp + 1;
                            }
                        }
                        else
                            ShowError();
                    }
                    else
                        ShowError();
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

void TInputLong::setState(ushort aState, Boolean enable)
{
    char tmp[12]; //-- 12 символов максимальная длина  целого со знаком '-'
    memset(tmp, 0x0, 12);
    if (!enable)
    {
        //-- потеря фокуса ввода
        getData(tmp);
        int stop = 0;
    }
    TInputLine::setState(aState, enable);
}

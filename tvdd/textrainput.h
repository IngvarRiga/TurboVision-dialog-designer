
#ifndef TEXTRAINPUT				
#define TEXTRAINPUT

#define Uses_TEvent
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TRect
#define Uses_MsgBox
#include <tvision/tv.h>
#include <math.h>
#include "multilang.h"


//-- определение класса TInputLong

class TInputLong : public TInputLine
{
private:
    /// <summary>
    /// Редактируемое значение
    /// </summary>
    long value;
    /// <summary>
    /// Допустимый диапазон изменений значения
    /// </summary>
    long minv, maxv;
    /// <summary>
    /// 
    /// </summary>
    /// <param name="tmp"></param>
    /// <param name="out"></param>
    /// <returns></returns>
    bool convertl(const char* tmp, long* out);

public:

    TInputLong(const TRect& bounds, long MinValue = LONG_MIN, long MaxValue = LONG_MAX, long DefValue = 0);
    ~TInputLong() {};

    virtual void handleEvent(TEvent& event);
    /// <summary>
    /// Нормализованное получение данных 
    /// </summary>
    /// <returns></returns>
    long getValue() { return value; }
    /// <summary>
    /// Нормализованная установка данных
    /// </summary>
    /// <param name="val"></param>
    void setValue(long val);
    /// <summary>
    /// Проверка попадания в диапазон допустимых значений
    /// </summary>
    /// <param name="val"> - проверяемое значение</param>
    /// <returns></returns>
    bool CheckValue(long val);
};



#endif
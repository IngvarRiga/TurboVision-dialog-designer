#ifndef TTRIALBUTTON_H
#define TTRIALBUTTON_H
#define Uses_TButton
#define Uses_TEvent
#define Uses_TRect
#define Uses_TGroup

#include <tvision/tv.h>
#include "wbutton.h"

class TTrialButton : public TWrapButton
{
public:
    TTrialButton(const TRect& bounds,
                 TStringView aTitle,
                 ushort aCommand = 0,
                 ushort aFlags = 0);

    virtual ~TTrialButton()
    {}



    virtual void setState(ushort aState, Boolean enable);
    virtual void handleEvent(TEvent& event);
    virtual void sizeLimits(TPoint& min, TPoint& max);
    void genCode(void* val);

    //-- получение значений
    char* getVarName();
    char* getClassName();
    bool getUsedVarName();

    //-- установка значений
    void setVarName(const char* val);
    void setClassName(const char* val);
    void setUsedVarName(bool val);
    /// <summary>
    /// Генерирует JSON-код компонента
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    bool usedVarName; //-- при генерации исходного кода использовать отдельную переменную для объекта
    char class_name[StringMaxLen]; //-- имя базового класса
    char var_name[StringMaxLen]; //-- имя переменной для создания текста
};

#endif /* TTRIALBUTTON_H */


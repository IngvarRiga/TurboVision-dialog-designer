#ifndef TTRIALRADIOBUTTONS_H
#define TTRIALRADIOBUTTONS_H
#define Uses_TView
#define Uses_TSItem
#define Uses_TRadioButtons
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#define Uses_TEvent
#define Uses_TCluster
#define Uses_TStringCollection
#define Uses_TKeys
#include <tvision/tv.h>
#include "wradiobuttons.h"

class TTrialRadioButtons : public TWrapRadioButtons
{
public:

    TTrialRadioButtons(const TRect& bounds, TSItem* aStrings);

    virtual ~TTrialRadioButtons()
    {}

    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);

    //-- получение значений
    char* getVarName();
    char* getClassName();

    //-- установка значений
    void setVarName(const char* val);
    void setClassName(const char* val);

    virtual void setState(ushort aState, Boolean enable);
    void genCode(void* val);
    /// <summary>
    /// √енерирует JSON-код компонента
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    char var_name[StringMaxLen]; //-- им€ переменной дл€ создани€ строки ввода
    char class_name[StringMaxLen]; //-- им€ переменной дл€ создани€ текста


private:
    bool Selected;

};

#endif /* TTRIALRADIOBUTTONS_H */


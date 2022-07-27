#ifndef TTRIALCHECKBOXES_H
#define TTRIALCHECKBOXES_H

#define Uses_TView
#define Uses_TSItem
#define Uses_TCheckBoxes
#define Uses_TEvent
#define Uses_TCluster
#define Uses_TStringCollection
#define Uses_TKeys
#include <tvision/tv.h>
#include "wcheckboxes.h"
#include "common.h"

class TTrialCheckBoxes : public TWrapCheckBoxes
{
public:
    static const char* const name;

    TTrialCheckBoxes(const TRect& bounds, TSItem* aStrings);

    virtual ~TTrialCheckBoxes()
    {}

    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);

    virtual void setState(ushort aState, Boolean enable);
    void genCode(void* val);

    //-- получение значений
    char* getVarName();
    char* getClassName();

    //-- установка значений
    void setVarName(const char* val);
    void setClassName(const char* val);
    /// <summary>
    /// √енерирует JSON-код компонента
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    char var_name[StringMaxLen]; //-- им€ переменной дл€ создани€ строки ввода
    char class_name[StringMaxLen]; //-- им€ переменной дл€ создани€ текста

};

#endif /* TTRIALCHECKBOXES_H */


#ifndef TTRIALMEMO_H
#define TTRIALMEMO_H
#define Uses_TView
#define Uses_TKeys
#define Uses_TEditor
#define Uses_TMemo
#define Uses_TEvent
#define Uses_TDrawBuffer
#define Uses_TScrollBar
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TMenuBox
#include <tvision/tv.h>

#include "common.h"

class TTrialMemo : public TMemo
{
public:

    TTrialMemo(const TRect&, TScrollBar*, TScrollBar*, TIndicator*, ushort);


    virtual void setState(ushort aState, Boolean enable);

    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);
    void genCode(void* val);

    //-- получение значений
    char* getVarName();
    char* getClassName();

    //-- установка значений
    void setVarName(const char* val);
    void setClassName(const char* val);
    bool isSelected();
    void setSelected(bool val);
    /// <summary>
    /// √енерирует JSON-код компонента
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    bool Selected;

private:
    char var_name[StringMaxLen]; //-- им€ переменной дл€ создани€ строки ввода
    char class_name[StringMaxLen]; //-- им€ переменной дл€ создани€ текста

};

#endif /* TTRIALMEMO_H */


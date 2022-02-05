#ifndef TTRIALMEMO_H
#define TTRIALMEMO_H
#define Uses_TView
#define Uses_TKeys
#define Uses_TEditor
#define Uses_TMemo
#define Uses_TEvent
#define Uses_opstream
#define Uses_ipstream
#define Uses_ofpstream
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TDrawBuffer
#define Uses_TScrollBar
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TMenuBox
#include <tvision/tv.h>

#include "common.h"
//#include "wmemo.h"

class TTrialMemo : public TMemo
{
public:
    static const char* const name;

    TTrialMemo(const TRect&, TScrollBar*, TScrollBar*, TIndicator*, ushort);


    TTrialMemo(StreamableInit) :
        TMemo(streamableInit)
    {}

    static TStreamable* build();

    virtual const char* streamableName() const
    {
        return name;
    }
    virtual void setState(ushort aState, Boolean enable);

    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);
    void genCode(void* val);

    //-- получение значений
    char* getVarName();
    char* getClassName();

    //-- установка значений
    void setVarName(char* val);
    void setClassName(char* val);
    bool isSelected();
    void setSelected(bool val);

protected:
    bool Selected;
    virtual void write(opstream&);
    virtual void* read(ipstream&);

private:
    char var_name[StringMaxLen]; //-- имя переменной для создания строки ввода
    char class_name[StringMaxLen]; //-- имя переменной для создания текста

};

inline ipstream& operator>>(ipstream& is, TTrialMemo& cl)
{
    return is >> (TStreamable&)cl;
}

inline ipstream& operator>>(ipstream& is, TTrialMemo*& cl)
{
    return is >> (void*&)cl;
}

inline opstream& operator<<(opstream& os, TTrialMemo& cl)
{
    return os << (TStreamable&)cl;
}

inline opstream& operator<<(opstream& os, TTrialMemo* cl)
{
    return os << (TStreamable*)cl;
}


#endif /* TTRIALMEMO_H */


#ifndef TTRIALCHECKBOXES_H
#define TTRIALCHECKBOXES_H

#define Uses_TView
#define Uses_TSItem
#define Uses_TCheckBoxes
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
#include "wcheckboxes.h"

class TTrialCheckBoxes : public TWrapCheckBoxes
{
  public:
    static const char * const name;

    TTrialCheckBoxes(const TRect& bounds, TSItem *aStrings);

    virtual ~TTrialCheckBoxes()
    {
    }

    TTrialCheckBoxes(StreamableInit) :
    TWrapCheckBoxes(streamableInit)
    {
    }
    static TStreamable *build();

    virtual const char *streamableName() const
    {
        return name;
    }
    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);

    virtual void setState(ushort aState, Boolean enable);
    void genCode(void *val);

    //-- получение значений
    char* getVarName();
    char* getClassName();

    //-- установка значений
    void setVarName(const char* val);
    void setClassName(const char* val);

  protected:
    char var_name[StringMaxLen]; //-- имя переменной для создания строки ввода
    char class_name[StringMaxLen]; //-- имя переменной для создания текста

    virtual void write(opstream&);
    virtual void *read(ipstream&);

  private:
};

inline ipstream& operator>>(ipstream& is, TTrialCheckBoxes& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TTrialCheckBoxes*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TTrialCheckBoxes& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TTrialCheckBoxes* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TTRIALCHECKBOXES_H */


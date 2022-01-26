#ifndef TTRIALINPUTLINE_H
#define TTRIALINPUTLINE_H
#define Uses_TInputLine
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#define Uses_TRect
#define Uses_TGroup
#include <tvision/tv.h>
#include "winputline.h"
#include "common.h"

class TTrialInputLine : public TWrapInputLine
{
  public:
    static const char * const name;

    TTrialInputLine(const TRect& bounds, uint aMaxLen, TValidator *aValid = 0);

    virtual ~TTrialInputLine()
    {
    }

    TTrialInputLine(StreamableInit) :
    TWrapInputLine(streamableInit)
    {
    }

    static TStreamable *build();

    virtual const char *streamableName() const
    {
        return name;
    }
    virtual void setState(ushort aState, Boolean enable);

    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);
    bool isSelected();
    void setSelected(bool val);
    void genCode(void *val);

    //-- получение значений
    char* getVarName();
    char* getClassName();
    uint getVarLen();

    //-- установка значений
    void setVarName(char *val);
    void setClassName(char* val);
    void setVarLen(uint val);


  protected:
    virtual void write(opstream&);
    virtual void *read(ipstream&);

  private:
    char var_name[StringMaxLen]; //-- имя переменной для создания строки ввода
    char class_name[StringMaxLen]; //-- имя переменной для создания текста

 };

inline ipstream& operator>>(ipstream& is, TTrialInputLine& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TTrialInputLine*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TTrialInputLine& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TTrialInputLine* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TTRIALINPUTLINE_H */


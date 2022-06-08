
#ifndef TEXTRAINPUT				
#define TEXTRAINPUT

#define Uses_TEvent
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TRect
#define Uses_MsgBox
#include <tvision/tv.h>
//#include <conio.h>
//#include <dos.h>
#include <math.h>




/***********************************************************************
** TInputInteger
************************************************************************/

class TInputInteger : public TInputLine
{
private:
    long Value;		
    long minValue;
    long maxValue;

    bool CheckValue(long val);
public:

    TInputInteger(const TRect& bounds, long vDef = 0, long vMin = LONG_MIN, long vMax = LONG_MAX);
    ~TInputInteger() {};

    virtual void handleEvent(TEvent& event);	// перегрузка для блокирования не цифровых клавиш
    virtual Boolean valid(ushort command);
    virtual long getValue();
    virtual void setValue(long val);
};



#endif
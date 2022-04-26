
#ifndef TEXTRAINPUT				// { TINPEXTD_h
#define TEXTRAINPUT

#define Uses_TEvent
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TRect
#define Uses_MsgBox
#include <tvision/tv.h>
#include <conio.h>
#include <dos.h>
#include <math.h>

/***********************************************************************
** TExtended
**
**	This class is a minor extension of TInputLine designed to
** serve as a base class for numeric data types that we want to
** map.
**
**	It is an abstract base class, since two functions are pure
** virtual.
**
************************************************************************/

#define TINPUT_NO_EXTENDED	0
#define TINPUT_EXTENDED		1

class Range
{
public:
    double minimum;
    double maximum;
    Range(double min, double max) noexcept;
};

inline Range::Range(double min, double max) noexcept
{
    minimum = min;
    maximum = max;
}



class TExtended : public TInputLine
{

public:

    TExtended
    (
        const TRect& bounds,
        int aMaxLen,
        const Range& code,
        int mapped,
        const Range& user
    );

    //~TExtended();

    virtual void handleEvent(TEvent& event);	// override for mouse handling

    virtual void mapToUser();		// change to user units
    virtual void mapToCode();		// change to code units
    virtual double getValue() = 0;	// get current value (byte, long...)
    virtual void setValue(double) = 0;	// put current value back
    virtual void updateValue() = 0;	// redisplay current value

protected:

    //TExtended(StreamableInit) : TInputLine(streamableInit) {};

protected:			// code for remapping the displayed values

    int useMap;				// 1 if the mapping is to be used
    double codeValue;			// current value in internal scale
    double codeMin;			// minimum value in internal scale
    double codeMax;			// maximum value in internal scale
    double userValue;			// current value in user's scale
    double userMin;			// minimum value in user's scale
    double userMax;			// maximum value in user's scale

public:				// base class pointer

    static const char* const name;

private:			// functions not provided by base class

    void setupMouseMapping	// make equation for mouse<-->user conversions
    (
        double min,
        double max
    );
    void setupKeyMapping	// make equation for key<-->user conversions
    (
        double min,
        double max
    );
    double userMouseMapping	// convert mouse y-value to user range
    (
        int mousevalue		// current value of mouse y-mickey
    );
    double userKeyMapping	// convert key value to user range
    (
        int keyvalue		// current value of key counter
    );
    int mouseMapping		// convert user value to mouse range
    (
        double uservalue	// value of numeric field
    );
    int keyMapping		// convert user value to key range
    (
        double uservalue	// value of the numeric field
    );
    void handleKeyControl	// handle the keystroke properly
    (
        int key			// the keystroke (up or down arrow)
    );
    void handleMouseControl
    (
        void
    );
    int mouseCorrect
    (
        int ypos
    );

private:			// parameters of the mapping

    int mouseMin;		// minimum y-value of mouse [  0]
    int mouseMax;		// minimum y-value of mouse [  0]
    double muserMin;		// mouse's user-minimum
    double muserMax;		// mouse's user-maximum
    double mouseSlope;		// slope used in mapping equation

    int keyMin;			// minimum y-value of key [  0]
    int keyMax;			// minimum y-value of key [  0]
    double kuserMin;		// key's user-minimum
    double kuserMax;		// key's user-maximum
    double keySlope;		// slope used in mapping equation

private:			// values of our mapped variables

    int yMouse;			// current value of mouse cursor
    int yMouseOld;		// previous value of mouse cursor
    int yKey;			// current value of key count
    int yKeyOld;		// previous value of key count
    double oldValue;		// original value of user variable

private:

    int inControl;		// set to 1 if mouse/keys are in control

};


/***********************************************************************
** TInputInteger
************************************************************************/

class TInputInteger : public TExtended
{

public:

    TInputInteger(const TRect& bounds,int aMaxLen,const Range& code,char* formatstring,int mapped, const Range& user);
    ~TInputInteger() {};

    virtual ushort dataSize();
    virtual void getData(void* rec);
    virtual void setData(void* rec);
    virtual Boolean valid(ushort command);
    virtual double getValue();		// get current value (byte, long...)
    virtual void setValue(double value);	// put current value back
    virtual void updateValue();		// redisplay current value

    int Value;				// current value of the integer
    char* format;			// pointer to desired integer format

//protected:
//
//    TInputInteger(StreamableInit) : TExtended(streamableInit) {};
//    virtual void write(opstream&);
//    virtual void* read(ipstream&);
//
//private:
//
//    virtual const char* streamableName() const
//    {
//        return name;
//    }
//
//public:

    //static const char* const name;
    //static TStreamable* build();

};
#define intBufSize	18		// maximum number of characters allowed
#define intDatSize	 6		// default databox size

//inline ipstream& operator >> (ipstream& is, TInputInteger& cl)
//{
//    return is >> (TStreamable&)cl;
//}
//
//inline ipstream& operator >> (ipstream& is, TInputInteger*& cl)
//{
//    return is >> (void*&)cl;
//}
//
//inline opstream& operator << (opstream& os, TInputInteger& cl)
//{
//    return os << (TStreamable&)cl;
//}
//
//inline opstream& operator << (opstream& os, TInputInteger* cl)
//{
//    return os << (TStreamable*)cl;
//}


/***********************************************************************
** TInputFloat
************************************************************************/
/*
class TInputFloat : public TExtended
{

public:

    TInputFloat
    (
        const TRect& bounds,
        int aMaxLen,
        const Range& code,
        char* formatstring,
        int mapped,
        const Range& user
    );
    // ~TInputFloat();

    virtual ushort dataSize();
    virtual void getData(void* rec);
    virtual void setData(void* rec);
    virtual Boolean valid(ushort command);
    virtual double getValue();		// get current value (byte, long...)
    virtual void putValue(double);	// put current value back
    virtual void updateValue();		// redisplay current value

    double Value;			// current value of the float
    char* format;			// pointer to floating-point format

//protected:
//
//    TInputFloat(StreamableInit) : TExtended(streamableInit) {};
//    virtual void write(opstream&);
//    virtual void* read(ipstream&);
//
//private:
//
//    virtual const char* streamableName() const
//    {
//        return name;
//    }
//
//public:
//
//    static const char* const name;
//    static TStreamable* build();

};
#define floatBufSize	24		// maximum number of characters allowed
#define floatDatSize	 8		// default databox size

#ifdef DOUBLE_CRAP
//inline ipstream& operator >> (ipstream& is, TInputFloat& cl)
//{
//    return is >> (TStreamable&)cl;
//}
//
//inline ipstream& operator >> (ipstream& is, TInputFloat*& cl)
//{
//    return is >> (void*&)cl;
//}
//
//inline opstream& operator << (opstream& os, TInputFloat& cl)
//{
//    return os << (TStreamable&)cl;
//}
//
//inline opstream& operator << (opstream& os, TInputFloat* cl)
//{
//    return os << (TStreamable*)cl;
//}
#endif
*/

/***********************************************************************
** TInputLong
************************************************************************/
/*
class TInputLong : public TExtended
{

public:

    TInputLong
    (
        const TRect& bounds,
        int aMaxLen,
        const Range& code,
        char* formatstring,
        int mapped,
        const Range& user
    );
    virtual ushort dataSize();
    virtual void getData(void*);
    virtual void setData(void*);
    virtual Boolean valid(ushort);
    virtual double getValue();		// get current value (byte, long...)
    virtual void putValue(double);	// put current value back
    virtual void updateValue();		// redisplay current value

    long Value;				// current value of the integer
    char* format;			// pointer to desired integer format

//protected:
//
//    TInputLong(StreamableInit) : TExtended(streamableInit) {};
//    virtual void write(opstream&);
//    virtual void* read(ipstream&);
//
//private:
//
//    virtual const char* streamableName() const
//    {
//        return name;
//    }
//
//public:
//
//    static const char* const name;
//    static TStreamable* build();

};
#define longBufSize	24		// maximum number of characters allowed
#define longDatSize	10		// default databox size
//
//inline ipstream& operator >> (ipstream& is, TInputLong& cl)
//{
//    return is >> (TStreamable&)cl;
//}
//
//inline ipstream& operator >> (ipstream& is, TInputLong*& cl)
//{
//    return is >> (void*&)cl;
//}
//
//inline opstream& operator << (opstream& os, TInputLong& cl)
//{
//    return os << (TStreamable&)cl;
//}
//
//inline opstream& operator << (opstream& os, TInputLong* cl)
//{
//    return os << (TStreamable*)cl;
//}
*/
#endif
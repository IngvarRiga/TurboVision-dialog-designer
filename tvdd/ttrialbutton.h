#ifndef TTRIALBUTTON_H
#define TTRIALBUTTON_H
#define Uses_TButton
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#define Uses_TRect
#define Uses_TGroup

#include <tvision/tv.h>
#include "wbutton.h"

class TTrialButton : public TWrapButton
{
public:
    static const char* const name;

    TTrialButton(const TRect& bounds,
                 TStringView aTitle,
                 ushort aCommand = 0,
                 ushort aFlags = 0);

    virtual ~TTrialButton()
    {}

    TTrialButton(StreamableInit) :
        TWrapButton(streamableInit)
    {}

    static TStreamable* build();

    virtual const char* streamableName() const
    {
        return name;
    }

    virtual void setState(ushort aState, Boolean enable);
    virtual void handleEvent(TEvent& event);
    virtual void sizeLimits(TPoint& min, TPoint& max);
    void genCode(void* val);

    //-- ��������� ��������
    char* getVarName();
    char* getClassName();
    bool getUsedVarName();

    //-- ��������� ��������
    void setVarName(const char* val);
    void setClassName(const char* val);
    void setUsedVarName(bool val);
    /// <summary>
    /// ���������� JSON-��� ����������
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    bool usedVarName; //-- ��� ��������� ��������� ���� ������������ ��������� ���������� ��� �������
    char class_name[StringMaxLen]; //-- ��� �������� ������
    char var_name[StringMaxLen]; //-- ��� ���������� ��� �������� ������
    virtual void write(opstream&);
    virtual void* read(ipstream&);

};

inline ipstream& operator>>(ipstream& is, TTrialButton& cl)
{
    return is >> (TStreamable&)cl;
}

inline ipstream& operator>>(ipstream& is, TTrialButton*& cl)
{
    return is >> (void*&)cl;
}

inline opstream& operator<<(opstream& os, TTrialButton& cl)
{
    return os << (TStreamable&)cl;
}

inline opstream& operator<<(opstream& os, TTrialButton* cl)
{
    return os << (TStreamable*)cl;
}

#endif /* TTRIALBUTTON_H */


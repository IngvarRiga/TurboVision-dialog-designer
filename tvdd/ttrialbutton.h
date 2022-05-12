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
};

#endif /* TTRIALBUTTON_H */


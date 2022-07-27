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

    //-- ��������� ��������
    char* getVarName();
    char* getClassName();

    //-- ��������� ��������
    void setVarName(const char* val);
    void setClassName(const char* val);
    /// <summary>
    /// ���������� JSON-��� ����������
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    char var_name[StringMaxLen]; //-- ��� ���������� ��� �������� ������ �����
    char class_name[StringMaxLen]; //-- ��� ���������� ��� �������� ������

};

#endif /* TTRIALCHECKBOXES_H */


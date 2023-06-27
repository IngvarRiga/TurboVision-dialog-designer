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
#include "wmemo.h"
#include "common.h"

class TTrialMemo : public TWrapMemo
{
public:

    TTrialMemo(const TRect&, TScrollBar*, TScrollBar*, TIndicator*, ushort);


    virtual void setState(ushort aState, Boolean enable);

    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);
    void genCode(void* val);

    //-- ��������� ��������
    char* getVarName();
    bool getHScroll() { return h_scroll; };
    bool getVScroll() { return v_scroll; };
    long getMaxLength() { return max_length; };
    std::string getDefaultText() { return def_text; }
    //-- ��������� ��������
    void setVarName(const char* val);
    void setHScroll(bool val) { h_scroll = val; };
    void setVScroll(bool val) { v_scroll = val; };
    void setMaxLength(long val) { max_length = val; };
    void setDefaultText(std::string val) { def_text = val; }

    bool isSelected();
    //void setSelected(bool val);
    /// <summary>
    /// ���������� JSON-��� ����������
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    bool Selected;

private:
    char var_name[StringMaxLen]; //-- ��� ���������� ��� �������� ������ �����
    bool h_scroll; //-- ������� ������ �������������� ���������
    bool v_scroll; //-- ������� ������ ������������ ���������
    long max_length; //-- ����������� ���������� ����� ������
    std::string def_text; //-- ����� � ���������� �� ���������
};

#endif /* TTRIALMEMO_H */


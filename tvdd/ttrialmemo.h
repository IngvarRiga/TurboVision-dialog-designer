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

    //-- получение значений
    char* getVarName();
    bool getHScroll() { return h_scroll; };
    bool getVScroll() { return v_scroll; };
    long getMaxLength() { return max_length; };
    std::string getDefaultText() { return def_text; }
    //-- установка значений
    void setVarName(const char* val);
    void setHScroll(bool val) { h_scroll = val; };
    void setVScroll(bool val) { v_scroll = val; };
    void setMaxLength(long val) { max_length = val; };
    void setDefaultText(std::string val) { def_text = val; }

    bool isSelected();
    //void setSelected(bool val);
    /// <summary>
    /// Генерирует JSON-код компонента
    /// </summary>
    /// <returns></returns>
    nlohmann::json genJSON();

protected:
    bool Selected;

private:
    char var_name[StringMaxLen]; //-- имя переменной для создания строки ввода
    bool h_scroll; //-- Наличие строки горизонтальной прокрутки
    bool v_scroll; //-- Наличие строки вертикальной прокрутки
    long max_length; //-- Максимально допустимая длина текста
    std::string def_text; //-- Текст в компоненте по умолчанию
};

#endif /* TTRIALMEMO_H */


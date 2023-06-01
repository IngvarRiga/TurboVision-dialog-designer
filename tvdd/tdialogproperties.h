#ifndef TDIALOGPROPERTIES_H
#define TDIALOGPROPERTIES_H
#define Uses_TInputLine
#define Uses_TButton
#define Uses_TLabel
#define Uses_TCheckBoxes
#define Uses_TSItem

#include <tvision/tv.h>
#include "tcustomdialog.h"
#include "common.h"

class dataTDP
{
  public:
    dataTDP();
    char dlgClassName[StringMaxLen]; //-- имя класса создаваемого диалога
    char dlgBaseClass[StringMaxLen]; //-- имя класса - предка
    char dlgCaption[StringMaxLen]; //-- Заголовок окна
    bool dlgOpt_Centered; //-- Окно должно центрироваться на экране при вызове
    //-- окно может...
    bool wfDef;
    bool wfMove; //-- перемещаться
    bool wfGrow; //-- изменять размеры
    bool wfClose; //-- иметь кнопку закрытия
    bool wfZoom; //-- изменять размеры

    bool ofSelectable;
    bool ofTopSelect;
    bool ofFirstClick;
    bool ofFramed;
    bool ofPreProcess;
    bool ofPostProcess;
    bool ofBuffered;
    bool ofTileable;
    bool ofCenterX;
    bool ofCenterY;
    bool ofValidate;



    ////-- при генерации кода создавать: 
    //bool gcConstructor; //-- конструктор
    //bool ghHeader; //-- заголовочный файл
    //bool gcDataStruct; //-- структура данных окна
    //bool gcReadWriteFunc; //-- функции чтения и записи данных окна
};

/// <summary>
/// Окно редактирование свойств диалогового окна
/// </summary>
class TDialogProperties : public TCustomDialog
{
  public:
    TDialogProperties();
    virtual ~TDialogProperties() {}
    virtual void setData(dataTDP *val);
    virtual void getData(dataTDP *val);
  private:
    char dlgClassName[StringMaxLen]; //-- имя класса создаваемого диалога
    char dlgBaseClass[StringMaxLen]; //-- Имя класса - предка
    char dlgCaption[StringMaxLen]; //-- Заголовок окна
    
    TInputLine* class_name;
    TInputLine* base_name;
    TInputLine* caption;
    TCheckBoxes* add_prop;
    TCheckBoxes* dlg_WinFlags;
    TCheckBoxes* dlg_WinFlagDef;
    TCheckBoxes* gen_code;
};

#endif /* TDIALOGPROPERTIES_H */


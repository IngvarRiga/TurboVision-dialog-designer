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
};

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
    
    TInputLine *dcn;
    TInputLine *dbc;
    TInputLine *cpt;
    TCheckBoxes* add_prop;
};

#endif /* TDIALOGPROPERTIES_H */


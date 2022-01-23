#ifndef TDIALOGPROPERTIES_H
#define TDIALOGPROPERTIES_H
#define Uses_TInputLine
#define Uses_TButton
#define Uses_TLabel

#include <tvision/tv.h>
#include "tcustomdialog.h"
#include "common.h"

class dataTDP
{
  public:
    dataTDP();
    char dlgClassName[StringMaxLen]; //-- имя класса создаваемого диалога
    char dlgBaseClass[StringMaxLen]; //-- Иня класса - предка
    char dlgCaption[StringMaxLen]; //-- Заголовок окна
};

class TDialogProperties : public TCustomDialog
{
  public:
    TDialogProperties();
    virtual ~TDialogProperties();
    virtual void setData(dataTDP *val);
    virtual void getData(dataTDP *val);
  private:
    char dlgClassName[StringMaxLen]; //-- имя класса создаваемого диалога
    char dlgBaseClass[StringMaxLen]; //-- Иня класса - предка
    char dlgCaption[StringMaxLen]; //-- Заголовок окна
    
    TInputLine *dcn;
    TInputLine *dbc;
    TInputLine *cpt;
};

#endif /* TDIALOGPROPERTIES_H */


#ifndef TSTATICTEXTPROPERTIES_H
#define TSTATICTEXTPROPERTIES_H
#define Uses_TInputLine
#define Uses_TCheckBoxes
#define Uses_TSItem
#define Uses_TButton
#define Uses_TLabel
#define Uses_TMemo
#define Uses_TScrollBar
#define Uses_TLabel

#include <tvision/tv.h>
#include "tcustomdialog.h"
#include "common.h"

struct TDesc
{
    ushort length;
    char buffer[StringMaxLen];
};


class dataTSTP
{
  public:
    dataTSTP();
    char caption[StringMaxLen];
    char var_name[StringMaxLen];
    bool use_var_name;
};

class TStaticTextProperties : public TCustomDialog
{
  public:
    TStaticTextProperties();

    virtual ~TStaticTextProperties() {}

    virtual void setData(dataTSTP *val);
    virtual void getData(dataTSTP *val);
  private:
    TMemo *text;
    TScrollBar * sbv;
    TScrollBar * sbh;
    TInputLine * var_name;
    TCheckBoxes * var_name_use;
};
#endif /* TSTATICTEXTPROPERTIES_H */


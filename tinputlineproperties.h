#ifndef TINPUTLINEPROPERTIES_H
#define TINPUTLINEPROPERTIES_H

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

class dataTILP
{
  public:
    dataTILP();
    char var_name[StringMaxLen];
    uint var_len;    
};

class TInputLineProperties : public TCustomDialog
{
  public:
    TInputLineProperties();

    virtual ~TInputLineProperties();

    virtual void setData(dataTILP *val);
    virtual void getData(dataTILP *val);
  private:
    TInputLine * var_len;
    TInputLine * var_name;
};

#endif /* TINPUTLINEPROPERTIES_H */


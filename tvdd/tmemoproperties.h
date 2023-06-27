#ifndef TMEMOPROPERTIES_H
#define TMEMOPROPERTIES_H

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
#include "textrainput.h"
#include "common.h"


class dataTMEMOP
{
public:
	dataTMEMOP();
	long mem_len;
	bool h_scroll;
	bool v_scroll;
	std::string text;
	char var_name[StringMaxLen];
};

class TMemoProperties : public TCustomDialog
{
  public:
    TMemoProperties();
    virtual ~TMemoProperties() {}

    virtual void setData(dataTMEMOP* Data);
    virtual void getData(dataTMEMOP* Data);

    TInputLong* mem_len;
    TCheckBoxes* mem_scroll;
    TMemo* def_text;
    TInputLine* var_name;
};

#endif /* TMEMOPROPERTIES_H */


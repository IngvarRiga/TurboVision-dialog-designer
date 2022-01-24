#ifndef TBUTTONPROPERTIES_H
#define TBUTTONPROPERTIES_H

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


class dataTBTNP
{
public:
	dataTBTNP();

	char caption[StringMaxLen];
	char var_name[StringMaxLen];
	//char class_name[StringMaxLen];
	bool use_var_name;

};

class TButtonProperties : public TCustomDialog
{
public:
	TButtonProperties();

	virtual ~TButtonProperties() {}

	virtual void setData(dataTBTNP* val);
	virtual void getData(dataTBTNP* val);
private:
	TInputLine* capt;
	TInputLine* var_name;
	//TInputLine* class_name;
	TCheckBoxes* var_name_use;
};

#endif /* TBUTTONPROPERTIES_H */


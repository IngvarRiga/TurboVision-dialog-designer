#ifndef TINPUTDOUBLEPROPERTIES_H
#define TINPUTDOUBLEPROPERTIES_H

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


class dataTInputDouble
{
public:
	dataTInputDouble();

	char var_name[StringMaxLen];
	long double minv;
	long double maxv;
	long double defv;
	int prec;
	bool allow_undef;
};

class TInputDoubleProperties : public TCustomDialog
{
public:
	TInputDoubleProperties();

	virtual ~TInputDoubleProperties() {}

	virtual void setData(dataTInputDouble* val);
	virtual void getData(dataTInputDouble* val);
private:
	TInputLine* var_name;
	TInputDouble* minv;
	TInputDouble* maxv;
	TInputDouble* defv;
	TInputLong* prec;
	TCheckBoxes* allow_undef;

};

#endif 


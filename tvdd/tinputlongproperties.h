#ifndef TINPUTLONGPROPERTIES_H
#define TINPUTLONGPROPERTIES_H

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


class dataTInputLong
{
public:
	dataTInputLong();

	char var_name[StringMaxLen];
	long minv;
	long maxv;
	long defv;
	bool allow_undef;
};

class TInputLongProperties : public TCustomDialog
{
public:
	TInputLongProperties();

	virtual ~TInputLongProperties() {}

	virtual void setData(dataTInputLong* val);
	virtual void getData(dataTInputLong* val);
private:
	TInputLine* var_name;
	TInputLong* minv;
	TInputLong* maxv;
	TInputLong* defv;
	TCheckBoxes* allow_undef;
};

#endif /* TBUTTONPROPERTIES_H */


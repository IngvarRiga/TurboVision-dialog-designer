#ifndef TCHECKBOXESPROPERTIES_H
#define TCHECKBOXESPROPERTIES_H

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

class dataTCBP
{
public:
	dataTCBP();
	char var_name[StringMaxLen];
	char class_name[StringMaxLen];

	char v0[StringMaxLen];
	char v1[StringMaxLen];
	char v2[StringMaxLen];
	char v3[StringMaxLen];
	char v4[StringMaxLen];
	char v5[StringMaxLen];
	char v6[StringMaxLen];
	char v7[StringMaxLen];
	char v8[StringMaxLen];
	char v9[StringMaxLen];
	char v10[StringMaxLen];
	char v11[StringMaxLen];
	char v12[StringMaxLen];
	char v13[StringMaxLen];
	char v14[StringMaxLen];
	char v15[StringMaxLen];

};

class TCheckBoxesProperties : public TCustomDialog
{
public:
	TCheckBoxesProperties();

	virtual ~TCheckBoxesProperties() {}

	virtual void setData(dataTCBP* val);
	virtual void getData(dataTCBP* val);
private:
	TInputLine* class_name;
	TInputLine* var_name;
	TInputLine* v0;
	TInputLine* v1;
	TInputLine* v2;
	TInputLine* v3;
	TInputLine* v4;
	TInputLine* v5;
	TInputLine* v6;
	TInputLine* v7;
	TInputLine* v8;
	TInputLine* v9;
	TInputLine* v10;
	TInputLine* v11;
	TInputLine* v12;
	TInputLine* v13;
	TInputLine* v14;
	TInputLine* v15;
};

#endif /* TCHECKBOXESPROPERTIES_H */


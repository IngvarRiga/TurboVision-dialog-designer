#include "tinputlongproperties.h"
#include "multilang.h"

TInputLongProperties::TInputLongProperties() :
	TCustomDialog(TRect(39, 24, 81, 35), txt_PropertyInputLong),
	TWindowInit(&TDialog::initFrame)
{
	insert(new TStaticText(TRect(2, 2, 22, 3), txt_PropertyMinValue));
	insert(new TStaticText(TRect(2, 3, 23, 4), txt_PropertyMaxValue));
	insert(new TStaticText(TRect(2, 4, 23, 5), txt_PropertyDefValue));
	insert(new TStaticText(TRect(2, 6, 16, 7), txt_pd_VariableName));
	minv = new TInputLong(TRect(24, 2, 40, 3), -2147483648, 2147483647, 0);
	insert(minv);
	maxv = new TInputLong(TRect(24, 3, 40, 4), -2147483648, 2147483647, 0);
	insert(maxv);
	defv = new TInputLong(TRect(24, 4, 40, 5), -2147483648, 2147483647, 0);
	insert(defv);
	allow_undef = new TCheckBoxes(TRect(2, 5, 40, 6),
		new TSItem(txt_PropertyAllowUndefVal, 0));
	insert(allow_undef);
	var_name = new TInputLine(TRect(24, 6, 40, 7), 251);
	insert(var_name);
	insert(new TButton(TRect(20, 8, 30, 10), txt_btnCancel, cmCancel, bfDefault));
	insert(new TButton(TRect(30, 8, 40, 10), txt_btnOk, cmOK, bfDefault));
	selectNext(False);
}

void TInputLongProperties::setData(dataTInputLong* val)
{
	if (val != nullptr)
	{
		var_name->setData(val->var_name);
		var_name->setData((void*)val->var_name);
		minv->setValue(val->minv);
		maxv->setValue(val->maxv);
		defv->setValue(val->defv);
		if (val->allow_undef)
			allow_undef->press(0);
	}
}

void TInputLongProperties::getData(dataTInputLong* val)
{
	if (val != nullptr)
	{
		memset(val->var_name, 0x0, StringMaxLen);
		var_name->getData(val->var_name);
		val->minv= minv->getValue();
		val->maxv = maxv->getValue();
		val->defv = defv->getValue();
		val->allow_undef = allow_undef->mark(0);
	}
}

dataTInputLong::dataTInputLong()
{
	//-- очистка строковых массивов
	memset(var_name, 0x0, StringMaxLen);
	minv = LONG_MIN;
	maxv = LONG_MAX;
	defv = 0;
	allow_undef = false;
}


#include "tinputdoubleproperties.h"
#include "multilang.h"

TInputDoubleProperties::TInputDoubleProperties() :
	TCustomDialog(TRect(42, 9, 100, 20), txt_PropertyInputDouble),
	TWindowInit(&TDialog::initFrame)
{
	options |= ofCentered;
	insert(new TStaticText(TRect(2, 2, 22, 3), txt_PropertyMinValue));
	insert(new TStaticText(TRect(2, 3, 23, 4), txt_PropertyMaxValue));
	insert(new TStaticText(TRect(2, 5, 23, 6), txt_PropertyDefValue));
	insert(new TStaticText(TRect(2, 6, 16, 7), txt_pd_VariableName));
	insert(new TStaticText(TRect(2, 4, 24, 5), txt_PropertyPrecision));
	minv = new TInputDouble(TRect(25, 2, 56, 3), -FLT_MAX, FLT_MAX, 0, 20);
	insert(minv);
	maxv = new TInputDouble(TRect(25, 3, 56, 4), -FLT_MAX, FLT_MAX, 0, 20);
	insert(maxv);
	prec = new TInputLong(TRect(25, 4, 37, 5), 1, 50, 20);
	insert(prec);
	defv = new TInputDouble(TRect(25, 5, 56, 6), -FLT_MAX, FLT_MAX, 0, 20);
	insert(defv);
	var_name = new TInputLine(TRect(25, 6, 37, 7), 255);
	insert(var_name);
	insert(new TButton(TRect(1, 8, 11, 10), txt_btnCancel, cmCancel, bfDefault));
	insert(new TButton(TRect(11, 8, 21, 10), txt_btnOk, cmOK, bfDefault));
	selectNext(False);
}


void TInputDoubleProperties::setData(dataTInputDouble* val)
{
	if (val != nullptr)
	{
		var_name->setData(val->var_name);
		var_name->setData((void*)val->var_name);
		minv->setValue(val->minv);
		maxv->setValue(val->maxv);
		defv->setValue(val->defv);
		prec->setValue(val->prec);
	}
}

void TInputDoubleProperties::getData(dataTInputDouble* val)
{
	if (val != nullptr)
	{
		memset(val->var_name, 0x0, StringMaxLen);
		var_name->getData(val->var_name);
		val->minv= minv->getValue();
		val->maxv = maxv->getValue();
		val->defv = defv->getValue();
		val->prec = prec->getValue();
	}
}

dataTInputDouble::dataTInputDouble()
{
	//-- очистка строковых массивов
	memset(var_name, 0x0, StringMaxLen);
	minv = -FLT_MAX;
	maxv = FLT_MAX;
	defv = 0.0;
	prec = 8;
}


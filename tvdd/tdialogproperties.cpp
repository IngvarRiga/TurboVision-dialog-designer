#include "tdialogproperties.h"
#include "multilang.h"

TDialogProperties::TDialogProperties() :
	TCustomDialog(TRect(66, 11, 113, 25), txt_PropertyDialogCaption),
	TWindowInit(&TDialog::initFrame)
{
	cpt = new TInputLine(TRect(2, 3, 45, 4), StringMaxLen);
	insert(cpt);
	dcn = new TInputLine(TRect(2, 5, 45, 6), StringMaxLen);
	insert(dcn);
	dbc = new TInputLine(TRect(2, 7, 45, 8), StringMaxLen);
	insert(dbc);
	auto s1 = new TSItem(txt_pd_CenteredDialog, 0);
	add_prop = new TCheckBoxes(TRect(2, 9, 45, 10), s1);
	insert(add_prop);

	insert(new TLabel(TRect(2, 2, 45, 3), txt_pd_DialogCaption, cpt));
	insert(new TLabel(TRect(2, 4, 45, 5), txt_pd_ClassName, dcn));
	insert(new TLabel(TRect(2, 6, 45, 7), txt_pd_BaseClassName, dbc));
	insert(new TLabel(TRect(2, 8, 45, 9), txt_pd_AdditionalProp, add_prop));

	insert(new TButton(TRect(25, 11, 35, 13), txt_btnCancel, cmCancel, bfDefault));
	insert(new TButton(TRect(35, 11, 45, 13), txt_btnOk, cmOK, bfDefault));
	selectNext(false);

	//add_prop->buttonState(sfDisabled, true);
	//add_prop->setState(sfActive, false);
}


void TDialogProperties::setData(dataTDP* val)
{
	if (val != nullptr)
	{
		dbc->setData(val->dlgBaseClass);
		dcn->setData(val->dlgClassName);
		cpt->setData(val->dlgCaption);
		if (val->dlgOpt_Centered)
			add_prop->press(0);
	}
}

void TDialogProperties::getData(dataTDP* val)
{
	if (val != nullptr)
	{
		dbc->getData(val->dlgBaseClass);
		dcn->getData(val->dlgClassName);
		cpt->getData(val->dlgCaption);
		val->dlgOpt_Centered = add_prop->mark(0);
	}
}

dataTDP::dataTDP()
{
	//-- очистка строковых массивов
	memset(dlgBaseClass, 0x0, StringMaxLen);
	memset(dlgClassName, 0x0, StringMaxLen);
	memset(dlgCaption, 0x0, StringMaxLen);
	dlgOpt_Centered = true;
}

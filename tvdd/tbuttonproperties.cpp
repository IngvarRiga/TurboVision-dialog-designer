#include "tbuttonproperties.h"
#include "multilang.h"

TButtonProperties::TButtonProperties() :
	TCustomDialog(TRect(10, 2, 50, 10), txt_PropertyButton),
	TWindowInit(&TDialog::initFrame)
{
	insert(new TStaticText(TRect(2, 2, 22, 3), txt_pd_CaptionText));
	var_name_use = new TCheckBoxes(TRect(2, 3, 22, 4),
							  new TSItem(txt_pd_VariableName, 0));
	insert(var_name_use);

	capt = new TInputLine(TRect(22, 2, 38, 3), 256);
	insert(capt);
	var_name = new TInputLine(TRect(22, 3, 38, 4), 15);
	insert(var_name);

	insert(new TButton(TRect(28, 5, 38, 7), txt_btnOk, cmOK, bfDefault));
	insert(new TButton(TRect(18, 5, 28, 7), txt_btnCancel, cmCancel, bfDefault));

	selectNext(False);
}

void TButtonProperties::setData(dataTBTNP* val)
{
	if (val != nullptr)
	{
		capt->setData(val->caption);
		//class_name->setData((void*)val->class_name);
		var_name->setData((void*)val->var_name);
		if (val->use_var_name)
			var_name_use->press(0);
	}
}

void TButtonProperties::getData(dataTBTNP* val)
{
	if (val != nullptr)
	{
		capt->getData(val->caption);
		//memset(val->class_name, 0x0, StringMaxLen);
		//class_name->getData(val->class_name);
		memset(val->var_name, 0x0, StringMaxLen);
		var_name->getData(val->var_name);
		val->use_var_name = var_name_use->mark(0);
	}
}

dataTBTNP::dataTBTNP()
{
	//-- очистка строковых массивов
	memset(caption, 0x0, StringMaxLen);
	memset(var_name, 0x0, StringMaxLen);
	//memset(class_name, 0x0, StringMaxLen);
	use_var_name = false;

}


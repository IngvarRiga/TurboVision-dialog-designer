#include "tcheckboxesproperties.h"
#include "multilang.h"

TCheckBoxesProperties::TCheckBoxesProperties() :
	TCustomDialog(TRect(29, 10, 81, 31), txt_PropertyCheckBoxes),
	TWindowInit(&TDialog::initFrame)
{
	insert(new TStaticText(TRect(2, 2, 18, 3), txt_pd_ValuesList));
	insert(new TStaticText(TRect(24, 4, 50, 5), txt_pd_BaseClassName));
	insert(new TStaticText(TRect(24, 2, 50, 3), txt_pd_VariableName));

	v0 = new TInputLine(TRect(2, 3, 23, 4), 254);
	insert(v0);
	v1 = new TInputLine(TRect(2, 4, 23, 5), 254);
	insert(v1);
	v2 = new TInputLine(TRect(2, 5, 23, 6), 254);
	insert(v2);
	v3 = new TInputLine(TRect(2, 6, 23, 7), 254);
	insert(v3);
	v4 = new TInputLine(TRect(2, 7, 23, 8), 254);
	insert(v4);
	v5 = new TInputLine(TRect(2, 8, 23, 9), 254);
	insert(v5);
	v6 = new TInputLine(TRect(2, 9, 23, 10), 254);
	insert(v6);
	v7 = new TInputLine(TRect(2, 10, 23, 11), 254);
	insert(v7);
	v8 = new TInputLine(TRect(2, 11, 23, 12), 254);
	insert(v8);
	v9 = new TInputLine(TRect(2, 12, 23, 13), 254);
	insert(v9);
	v10 = new TInputLine(TRect(2, 13, 23, 14), 254);
	insert(v10);
	v11 = new TInputLine(TRect(2, 14, 23, 15), 254);
	insert(v11);
	v12 = new TInputLine(TRect(2, 15, 23, 16), 254);
	insert(v12);
	v13 = new TInputLine(TRect(2, 16, 23, 17), 254);
	insert(v13);
	v14 = new TInputLine(TRect(2, 17, 23, 18), 254);
	insert(v14);
	v15 = new TInputLine(TRect(2, 18, 23, 19), 254);
	insert(v15);
	var_name = new TInputLine(TRect(24, 3, 50, 4), 254);
	insert(var_name);
	class_name = new TInputLine(TRect(24, 5, 50, 6), 254);
	insert(class_name);

	insert(new TButton(TRect(31, 18, 41, 20), txt_btnCancel, cmCancel, bfDefault));
	insert(new TButton(TRect(41, 18, 51, 20), txt_btnOk, cmOK, bfDefault));
	selectNext(false);
}

void TCheckBoxesProperties::setData(dataTCBP* val)
{
	if (val != nullptr)
	{
		class_name->setData((void*)val->class_name);
		var_name->setData((void*)val->var_name);
		v0->setData((void*)val->v0);
		v1->setData((void*)val->v1);
		v2->setData((void*)val->v2);
		v3->setData((void*)val->v3);
		v4->setData((void*)val->v4);
		v5->setData((void*)val->v5);
		v6->setData((void*)val->v6);
		v7->setData((void*)val->v7);
		v8->setData((void*)val->v8);
		v9->setData((void*)val->v9);
		v10->setData((void*)val->v10);
		v11->setData((void*)val->v11);
		v12->setData((void*)val->v12);
		v13->setData((void*)val->v13);
		v14->setData((void*)val->v14);
		v15->setData((void*)val->v15);
	}
}

void TCheckBoxesProperties::getData(dataTCBP* val)
{
	if (val != nullptr)
	{
		memset(val->class_name, 0x0, StringMaxLen);
		class_name->getData(val->class_name);
		memset(val->var_name, 0x0, StringMaxLen);
		var_name->getData(val->var_name);

		memset(val->v0, 0x0, StringMaxLen);
		memset(val->v1, 0x0, StringMaxLen);
		memset(val->v2, 0x0, StringMaxLen);
		memset(val->v3, 0x0, StringMaxLen);
		memset(val->v4, 0x0, StringMaxLen);
		memset(val->v5, 0x0, StringMaxLen);
		memset(val->v6, 0x0, StringMaxLen);
		memset(val->v7, 0x0, StringMaxLen);
		memset(val->v8, 0x0, StringMaxLen);
		memset(val->v9, 0x0, StringMaxLen);
		memset(val->v10, 0x0, StringMaxLen);
		memset(val->v11, 0x0, StringMaxLen);
		memset(val->v12, 0x0, StringMaxLen);
		memset(val->v13, 0x0, StringMaxLen);
		memset(val->v14, 0x0, StringMaxLen);
		memset(val->v15, 0x0, StringMaxLen);
		v0->getData(val->v0);
		v1->getData(val->v1);
		v2->getData(val->v2);
		v3->getData(val->v3);
		v4->getData(val->v4);
		v5->getData(val->v5);
		v6->getData(val->v6);
		v7->getData(val->v7);
		v8->getData(val->v8);
		v9->getData(val->v9);
		v0->getData(val->v0);
		v11->getData(val->v11);
		v12->getData(val->v12);
		v13->getData(val->v13);
		v14->getData(val->v14);
		v15->getData(val->v15);
	}
}

dataTCBP::dataTCBP()
{
	//-- очистка строковых массивов
	memset(class_name, 0x0, StringMaxLen);
	memset(var_name, 0x0, StringMaxLen);
    memset(v0, 0x0, StringMaxLen);
	memset(v1, 0x0, StringMaxLen);
	memset(v2, 0x0, StringMaxLen);
	memset(v3, 0x0, StringMaxLen);
	memset(v4, 0x0, StringMaxLen);
	memset(v5, 0x0, StringMaxLen);
	memset(v6, 0x0, StringMaxLen);
	memset(v7, 0x0, StringMaxLen);
	memset(v8, 0x0, StringMaxLen);
	memset(v9, 0x0, StringMaxLen);
	memset(v10, 0x0, StringMaxLen);
	memset(v11, 0x0, StringMaxLen);
	memset(v12, 0x0, StringMaxLen);
	memset(v13, 0x0, StringMaxLen);
	memset(v14, 0x0, StringMaxLen);
	memset(v15, 0x0, StringMaxLen);
}


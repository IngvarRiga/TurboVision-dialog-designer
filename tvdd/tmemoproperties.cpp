#include "tmemoproperties.h"
#include "multilang.h"

TMemoProperties::TMemoProperties() :
	TCustomDialog(TRect(26, 19, 94, 39), "Свойства TMemo"),
	TWindowInit(&TDialog::initFrame)
{
	options |= ofCentered;
	insert(new TStaticText(TRect(2, 2, 27, 3), "Максимальная длина текста"));
	insert(new TStaticText(TRect(2, 3, 16, 4), "Полосы сдвига"));
	insert(new TStaticText(TRect(2, 4, 20, 5), "Текст по умолчанию"));
	insert(new TStaticText(TRect(2, 15, 19, 16), txt_pd_VariableName));
	mem_len = new TInputLong(TRect(28, 2, 66, 3), 1, 65535, 1024, 0);
	insert(mem_len);
	mem_scroll = new TCheckBoxes(TRect(28, 3, 66, 4),
		new TSItem("Вертикальная",
			new TSItem("Горизонтальная", 0)));
	insert(mem_scroll);
	def_text = new TMemo(TRect(2, 5, 65, 14), nullptr, nullptr, nullptr, 255);
	insert(def_text);
	var_name = new TInputLine(TRect(28, 15, 66, 16), 247);
	insert(var_name);
	insert(new TButton(TRect(46, 17, 56, 19), txt_btnCancel, cmCancel, bfDefault));
	insert(new TButton(TRect(56, 17, 66, 19), txt_btnOk, cmOK, bfDefault));

	selectNext(false);
}

void TMemoProperties::setData(dataTMEMOP* val)
{
	if (val != nullptr)
	{
		//capt->setData(val->caption);
		var_name->setData((void*)val->var_name);
	}
}

void TMemoProperties::getData(dataTMEMOP* val)
{
	if (val != nullptr)
	{
		memset(val->var_name, 0x0, StringMaxLen);
		var_name->getData(val->var_name);
//		val->use_var_name = var_name_use->mark(0);
	}
}

dataTMEMOP::dataTMEMOP()
{
	memset(var_name, 0x0, StringMaxLen);
	mem_len = 1024;
	h_scroll = false;
	v_scroll = true;
	text = "";

}

#include "common.h"
#include "multilang.h"
#include "ttrialstatictext.h"
#include "ttrialinputline.h"
#include "ttrialbutton.h"
#include "ttrialcheckboxes.h"
#include "ttrialradiobuttons.h"
#include "ttriallistbox.h"
#include "ttrialmemo.h"

void DragObject(TView* obj, TEvent event)
{
	//-- перетаскивание и изменение размеров исключительно левой кнопкой мыши!
	if (event.mouse.buttons == mbLeftButton)
	{
		TPoint MinSz, MaxSz;
		ushort d;
		//-- устанавливаем минимальные границы размера в размер хозяина объекта
		//-- так, чтобы изменение размеров и перемещение не выводило объект
		//-- за границы предка (окна в общем случае)
		auto lims = obj->owner->getExtent();
		lims.grow(-1, -1);
		obj->sizeLimits(MinSz, MaxSz);

		auto r = obj->getBounds();
		auto tx = r.b.x - r.a.x - 1;
		auto ty = r.b.y - r.a.y - 1;
		auto mp = obj->makeLocal(event.mouse.where);
		
		d = dmDragMove;
		if ((mp.x == tx) && (mp.y == ty))
			d = dmDragGrow;
		obj->dragView(event, obj->dragMode | d, lims, MinSz, MaxSz);
	}
}

void unselected(TView* obj, void*)
{
	obj->setState(sfSelected, false);
}

void generateCode(TView* obj, void* res)
{
	std::vector<std::string> *src = (std::vector<std::string> *) res;
	std::stringstream ss;

	if (dynamic_cast<TTrialStaticText*> (obj))
	{
		TTrialStaticText* to = dynamic_cast<TTrialStaticText*> (obj);
		to->genCode(&ss);
		//return;
	}
	if (dynamic_cast<TTrialButton*> (obj))
	{
		TTrialButton* to = dynamic_cast<TTrialButton*> (obj);
		to->genCode(&ss);
		//return;
	}
	if (dynamic_cast<TTrialInputLine*> (obj))
	{
		TTrialInputLine* to = dynamic_cast<TTrialInputLine*> (obj);
		to->genCode(&ss);
		//return;
	}
	if (dynamic_cast<TTrialCheckBoxes*> (obj))
	{
		TTrialCheckBoxes* to = dynamic_cast<TTrialCheckBoxes*> (obj);
		to->genCode(&ss);
		//return;
	}
	if (dynamic_cast<TTrialListBox*> (obj))
	{
		TTrialListBox* to = dynamic_cast<TTrialListBox*> (obj);
		to->genCode(&ss);
		//return;
	}
	if (dynamic_cast<TTrialRadioButtons*> (obj))
	{
		TTrialRadioButtons* to = dynamic_cast<TTrialRadioButtons*> (obj);
		to->genCode(&ss);
		//return;
	}
	if (dynamic_cast<TTrialMemo*> (obj))
	{
		TTrialMemo* to = dynamic_cast<TTrialMemo*> (obj);
	    to->genCode(&ss);
	    //return;
	}

	std::vector<std::string> elem;
	std::vector<std::string>::iterator iter;
	std::string it;
	while (std::getline(ss, it))
	{
		if (it.length()>0)
			elem.push_back(it);
	}

	for (int i = elem.size() - 1; i > -1; i--)
	{
		iter = src->begin();
		src->insert(iter, elem[i]);
	}
}

TMenuBox* dialogMenu()
{
	//-- создание контекстного меню диалога
	TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
										 new TMenu(
											 *new TMenuItem(txt_PropertyDialogCaption, cmOption_Dialog, kbCtrlEnter, hcNoContext, "Ctrl+Enter") +
											 newLine() +
											 *new TMenuItem(txt_mnu_StaticText, cm_ed_InsertStaticText, kbNoKey) +
											 *new TMenuItem(txt_mnu_Button, cm_ed_InsertButton, kbNoKey) +
											 *new TMenuItem(txt_mnu_InputLine, cm_ed_InsertInputLine, kbNoKey) +
											 *new TMenuItem(txt_mnu_RadioButtons, cm_ed_InsertRadioButtons, kbNoKey) +
											 *new TMenuItem(txt_mnu_CheckBoxes, cm_ed_InsertCheckBoxes, kbNoKey) +
											 *new TMenuItem(txt_mnu_ListBox, cm_ed_InsertListBox, kbNoKey) +
											 *new TMenuItem(txt_mnu_Memo, cm_ed_InsertMemo, kbNoKey)), nullptr);
	return contextMenu;
}


#include "tcomponentdialog.h"
#include "multilang.h"
#include "common.h"

#define memTxt "Memo"
struct memInfo
{
	ushort length;
	char buffer[StringMaxLen];
};


TComponentDialog::TComponentDialog() :
	TCustomDialog(TRect(2, 1, 17, 14), txt_dlg_GadgetsPanel, false, false),
	TWindowInit(&TCustomDialog::initFrame)
{
	//-- удаляем кнопку закрытия окна
	flags &= 0xfb;
	//-- StaticText
	insert(new TWrapStaticText(TRect(2, 2, 6, 3), txt_dlg_StaticText, true));

	//-- InputLine
	auto il = new TWrapInputLine(TRect(8, 2, 13, 3), 11, 0, TLineType::lt_InputLine, true);
	il->setData((void*)txt_dlg_InputLine);
	insert(il);

	//-- InputLong
	auto ilong = new TWrapInputLine(TRect(8, 4, 13, 5), 11, 0, TLineType::lt_InputLong, true);
	ilong->setData((void*)txt_dlg_InputLong);
	insert(ilong);

	//-- InputDouble
	auto idouble = new TWrapInputLine(TRect(8, 6, 13, 7), 11, 0, TLineType::lt_InputDouble, true);
	idouble->setData((void*)txt_dlg_InputDouble);
	insert(idouble);

	//--TButton
	insert(new TWrapButton(TRect(1, 4, 7, 6), txt_dlg_Buton, -1, bfDefault, true));

	//-- TCheckBoxes
	auto cb = new TWrapCheckBoxes(TRect(8, 8, 13, 9), new TSItem("", 0), true);
	cb->press(0);
	insert(cb);

	//-- TRadioButtons
	auto rb = new TWrapRadioButtons(TRect(8, 10, 13, 11), new TSItem("", 0), true);
	rb->press(0);
	insert(rb);


	//auto sb = new TScrollBar(TRect(5, 6, 6, 9));
	//insert(sb);

	//auto lst = new TListBox(TRect(2, 6, 6, 9), 1, sb);
	//insert(lst);

#pragma region TMemo
	//-- полосы склоллинга не делаем
	//auto sbv = new TScrollBar(TRect(18, 19, 19, 21));
	//insert(sbv);

	//auto sbh = new TScrollBar(TRect(2, 21, 18, 22));
	//insert(sbh);

	//auto text = new TMemo(TRect(2, 19, 18, 21), (TScrollBar*)sbh, (TScrollBar*)sbv, 0, 255);
	//auto text = new TWrapMemo(TRect(8, 8, 13, 9), nullptr, nullptr, nullptr, 255, true);
	//rb->setState(sfDisabled, true);

	//auto rec = new memInfo();
	//memset(rec->buffer, 0x0, StringMaxLen);
	//rec->length = strlen(memTxt);
	//strncpy(rec->buffer, memTxt, rec->length);
	//text->setData(rec);

	//insert(text);
	
#pragma endregion


	setState(sfModal, false); //-- окно становится не модальным

}

void TComponentDialog::handleEvent(TEvent& event)
{
	if (event.what == evBroadcast)
	{
		auto pt = ((TPoint*)event.message.infoPtr);
		switch (event.message.command)
		{
			case (ushort)TDDCommand::cm_cmp_CreateStaticText:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop  не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapStaticText(TRect(pt->x, pt->y - 1, pt->x + 10, pt->y), txt_btnStaticText);
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;

					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateInputLine:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop  не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapInputLine(TRect(pt->x, pt->y - 1, pt->x + 10, pt->y), 11, nullptr, TLineType::lt_InputLine, false);
					v->setData((void*)txt_dlg_InputLine);
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;
					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateInputLong:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapInputLine(TRect(pt->x, pt->y - 1, pt->x + 10, pt->y), 11, nullptr, TLineType::lt_InputLong, false);
					v->setData((void*)txt_dlg_InputLong);
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;
					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateInputDouble:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop не доходит до диалогового окна
					clearEvent(event);
					//messageBox(txt_error_Unreleased, mfInformation | mfOKButton);

					auto v = new TWrapInputLine(TRect(pt->x, pt->y - 1, pt->x + 10, pt->y), 11, nullptr, TLineType::lt_InputDouble, false);
					v->setData((void*)txt_dlg_InputDouble);
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;
					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateButton:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop  не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapButton(TRect(pt->x, pt->y - 2, pt->x + 10, pt->y), txt_btnButton, -1, bfDefault);
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;
					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateCheckBoxes:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop  не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapCheckBoxes(TRect(pt->x, pt->y - 2, pt->x + 12, pt->y), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr)));
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;
					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateRadioButtons:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop  не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapRadioButtons(TRect(pt->x, pt->y - 2, pt->x + 12, pt->y), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr)));
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;
					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateListBox:
				{
					break;
				}
			case (ushort)TDDCommand::cm_cmp_CreateMemo:
				{
					break;
				}

		};
	}
	TCustomDialog::handleEvent(event);
}

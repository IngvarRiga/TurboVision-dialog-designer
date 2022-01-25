#include "tcomponentdialog.h"
#include "multilang.h"


#define memTxt "Memo"
struct memInfo
{
	ushort length;
	char buffer[StringMaxLen];
};


TComponentDialog::TComponentDialog() :
	TCustomDialog(TRect(2, 1, 17, 12), txt_dlg_GadgetsPanel, false, false),
	TWindowInit(&TCustomDialog::initFrame)
{
	//-- удаляем кнопку закрытия окна
	flags &= 0xfb;
	//-- StaticText
	insert(new TWrapStaticText(TRect(2, 2, 6, 3), txt_dlg_StaticText, true));
	
	//-- InputLine
	auto il = new TWrapInputLine(TRect(8, 2, 13, 3), 11, 0, true);
	il->setData((void*)txt_dlg_InputLine);
	insert(il);
	
	//--TButton
	insert(new TWrapButton(TRect(1, 4, 7, 6), txt_dlg_Buton, -1, bfDefault, true));

	//-- TCheckBoxes
	auto cb = new TWrapCheckBoxes(TRect(8, 4, 13, 5), new TSItem("", 0), true);
	cb->press(0);
	insert(cb);

	//-- TRadioButtons
	auto rb = new TWrapRadioButtons(TRect(8, 6, 13, 7), new TSItem("",0), true);
	rb->press(0);
	insert(rb);


	//    TScrollBar *sb = new TScrollBar(TRect(19, 15, 20, 20));
	//    insert(sb);

	TSortedListBox* lst = new TSortedListBox(TRect(2, 6, 6, 9), 1, 0);
	insert(lst);

#pragma region TMemo
	//-- полосы склоллинга не делаем
	//auto sbv = new TScrollBar(TRect(18, 19, 19, 21));
	//insert(sbv);

	//auto sbh = new TScrollBar(TRect(2, 21, 18, 22));
	//insert(sbh);

	//auto text = new TMemo(TRect(2, 19, 18, 21), (TScrollBar*)sbh, (TScrollBar*)sbv, 0, 255);
	auto text = new TMemo(TRect(8, 8, 13, 9), 0, 0, 0, 255);
	rb->setState(sfDisabled, true);

	auto rec = new memInfo();
	memset(rec->buffer, 0x0, StringMaxLen);
	rec->length = strlen(memTxt);
	strncpy(rec->buffer, memTxt, rec->length);
	text->setData(rec);

	insert(text);

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
			case cm_cmp_CreateStaticText:
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
			case cm_cmp_CreateInputLine:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop  не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapInputLine(TRect(pt->x, pt->y - 1, pt->x + 10, pt->y), 11, nullptr, false);
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
			case cm_cmp_CreateButton:
				{
					//-- очистка события должна быть именно здесь иначе сообщение о Drop  не доходит до диалогового окна
					clearEvent(event);
					auto v = new TWrapButton(TRect(pt->x, pt->y - 2, pt->x + 11, pt->y), txt_btnButton, -1, bfDefault);
					v->setDragged();
					v->options |= ofPreProcess | ofPostProcess;
					//-- прикручиваем тень к объекту, чтобы он "парил"
					v->setState(sfShadow, true);
					v->drawView();
					owner->insert(v);
					message(v, evMouseDown, -1, 0);
					break;
				}
			case cm_cmp_CreateCheckBoxes:
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
			case cm_cmp_CreateRadioButtons:
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
			case cm_cmp_CreateListBox:
				{
					break;
				}
			case cm_cmp_CreateMemo:
				{
					break;
				}

		};
	}
	TCustomDialog::handleEvent(event);
}

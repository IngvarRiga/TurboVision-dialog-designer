#include "tcomponentdialog.h"
#include "multilang.h"

TComponentDialog::TComponentDialog() :
	TCustomDialog(TRect(2, 1, 22, 30), txt_dlg_GadgetsPanel, false, false),
	TWindowInit(&TCustomDialog::initFrame)
{
	insert(new TWrapStaticText(TRect(2, 1, 18, 2), "StaticText", true));
	insert(new TWrapInputLine(TRect(2, 3, 18, 4), 11, 0, true));

	insert(new TWrapButton(TRect(1, 5, 18, 7), txt_btnButton, -1, bfDefault, true));
	insert(new TCheckBoxes(TRect(2, 7, 18, 9), new TSItem(txt_btnCheck1,
														  new TSItem(txt_btnCheck2, 0))));
	insert(new TRadioButtons(TRect(2, 10, 18, 12), new TSItem(txt_btnCheck1,
															  new TSItem(txt_btnCheck2, 0))));


	//    TScrollBar *sb = new TScrollBar(TRect(19, 15, 20, 20));
	//    insert(sb);

	TSortedListBox* lst = new TSortedListBox(TRect(2, 13, 18, 18), 1, 0);
	insert(lst);

#pragma region TMemo
	auto sbv = new TScrollBar(TRect(18, 19, 19, 21));
	insert(sbv);

	auto sbh = new TScrollBar(TRect(2, 21, 18, 22));
	insert(sbh);

	auto text = new TMemo(TRect(2, 19, 18, 21), (TScrollBar*)sbh, (TScrollBar*)sbv, 0, 255);
	insert(text);

#pragma endregion


	setState(sfModal, false); //-- окно становится немодальным

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

		};
	}
	TCustomDialog::handleEvent(event);
}

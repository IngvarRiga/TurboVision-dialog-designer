#define Uses_TRect
#define Uses_TGroup
#define Uses_TEvent
#define Uses_TKeys
#define Uses_TMenu
#define Uses_TMenuItem
#define Uses_TMenuBox
#include <tvision/tv.h>

#include "twinextmenu.h"
#include "multilang.h"
#include "common.h"


TWinExtMenu::TWinExtMenu(const TRect& rect) :
	TView(rect)
{
	eventMask = 0xFF; //-- установлен флаг получения кликом мышкой
	options |= ofPreProcess;
}


void TWinExtMenu::draw()
{
	TColorAttr color;
	TDrawBuffer b;
	color = 0xAC;
	setBounds(TRect(0, 2, 1, 3));
	b.moveStr(0, "\360", color);
	writeBuf(0, 0, size.x, 1, b);
}

void TWinExtMenu::handleEvent(TEvent& event)
{
	if (event.what | evMouse)
	{
		if (event.what == evMouseUp)
		{
			clearEvent(event);
			auto r = getBounds();
			r.a.x += 10;
			r.b.x = r.a.x + 20;
			r.b.y = r.a.y + 20;
			TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
												 new TMenu(
													 *new TMenuItem(txt_PropertyDialogCaption, (ushort)TDDCommand::cmOption_Dialog, kbNoKey, hcNoContext) +
													 newLine() +
													 *new TMenuItem(txt_mnu_DlgPropShowPosition, (ushort)TDDCommand::cmDialogPosOnOff, kbNoKey, hcNoContext) +
													 *new TMenuItem(txt_mnu_DlgPropShowSize, (ushort)TDDCommand::cmDialogSizeOnOff, kbNoKey, hcNoContext) +
													 newLine() +
													 *new TMenuItem(txt_mnu_DlgPropShowSizePos, (ushort)TDDCommand::cmDialogPosSizeOnOff, kbNoKey, hcNoContext) +
													 newLine() +
													 *new TMenuItem(txt_mnu_SaveToJson, (ushort)TDDCommand::cmDialogSaveToJson, kbNoKey, hcNoContext) +
													 newLine() +
													 *new TMenuItem(txt_mnu_GenCode, (ushort)TDDCommand::cmDialogGenCode, kbNoKey, hcNoContext)
												 ), nullptr);
			contextMenu->options |= ofCentered;
			auto res = owner->owner->execView(contextMenu);
			destroy(contextMenu);
			//-- рассылаем команды
			message(owner, evBroadcast, res, nullptr);
		}
	}
	TView::handleEvent(event);
}


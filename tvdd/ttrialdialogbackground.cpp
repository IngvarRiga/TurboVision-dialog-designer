#include "ttrialdialogbackground.h"
#include "common.h"

#include <math.h>

const char* const TTrialDialogBackground::name = "TTrialDialogBackground";

TTrialDialogBackground::TTrialDialogBackground(TRect& Bounds) :
	TView(Bounds)
{
	eventMask |= 0xF; //-- установлен флаг получения ВСЕХ сообщений
	options |= ofPreProcess;

	growMode = gfGrowHiX + gfGrowHiY;
	Patterned = true;
	currPos.y = -1;
}

void TTrialDialogBackground::draw()
{
	//-- коды указаны для ASCII, символы в консоле - другие
	// 0xB0 = light hatch ░ 
	// 0xB1 = med.  hatch ▒
	// 0xB2 = havy  hatch ▓
	TDrawBuffer bf1;
	TDrawBuffer b;
	char ch1;
	if (Patterned)
		ch1 = 0xb0;
	else
		ch1 = 0x20;
	//-- заполняем буфер легкой штриховки
	bf1.moveChar(0, ch1, 0x8E, size.x); // 76
	b.moveChar(0, ch1, 0x8E, size.x); // 76
	b.moveChar(currPos.x, 0xB1, 0x8A, 1);
	for (int i = 0; i < size.y; i++)
	{
		if (i == currPos.y)
			writeLine(0, i, size.x, 1, b);
		else
			writeLine(0, i, size.x, 1, bf1);
	}
}

void TTrialDialogBackground::handleEvent(TEvent& event)
{
	if (event.what == evBroadcast)
	{
		if (event.message.command == cm_DisableCursorPaint)
		{
			clearEvent(event);
			currPos.y = -1;
			drawView();
			return;
		}
	}
	currPos = makeLocal(event.mouse.where);
	drawView();
	if (event.what | evMouse)
	{

		//-- вызов окна редактирования свойств объекта
		if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
		{
			message(owner, evBroadcast, cmOption_Dialog, nullptr);
			clearEvent(event);
		}

		if (event.what == evMouseUp)
		{
			//-- вызов контекстного меню для диалога
			if (event.mouse.buttons == mbRightButton)
			{
				message(owner, evBroadcast, cmPopupMenu_Dialog, &event.mouse.where);
			}
		}
	}

	//-- вызываем унаследованный метод обработки сообщений
	TView::handleEvent(event);
}

Boolean TTrialDialogBackground::valid(ushort command)
{
	bool rslt = TView::valid(command);
	if (rslt && (command == cmOK))
	{
	}
	return rslt;
}

void TTrialDialogBackground::write(opstream& os)
{
	TView::write(os);
	os.writeBytes(&Patterned, sizeof(Patterned));
}

void* TTrialDialogBackground::read(ipstream& is)
{
	TView::read(is);
	is.readBytes(&Patterned, sizeof(Patterned));
	return this;
}

TStreamable* TTrialDialogBackground::build()
{
	return new TTrialDialogBackground(streamableInit);
}

TStreamableClass RTrialDialogBackground(
	TTrialDialogBackground::name,
	TTrialDialogBackground::build,
	__DELTA(TTrialDialogBackground)
);

__link(RView)
__link(RTrialDialogBackground)

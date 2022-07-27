#include "wbutton.h"


const char* TWrapButton::shadows = "\xDC\xDB\xDF";
const char* TWrapButton::markers = "[]";

const int

cmGrabDefault = 61,
cmReleaseDefault = 62;

#define cpButton "\x0A\x0B\x0C\x0D\x0E\x0E\x0E\x0F"

TWrapButton::TWrapButton(const TRect& bounds,
						 TStringView aTitle,
						 ushort aCommand,
						 ushort aFlags,
						 bool click) noexcept :
	TView(bounds),
	command(aCommand),
	flags(aFlags),
	amDefault(Boolean((aFlags& bfDefault) != 0))
{
	memset(title, 0x0, StringMaxLen);
	strncpy(title, aTitle.data(), strlen(aTitle.data()));
	options |= ofSelectable | ofFirstClick | ofPreProcess | ofPostProcess;
	eventMask |= evBroadcast;
	if (!commandEnabled(aCommand))
		state |= sfDisabled;

	eventMask = 0xFF; //-- установлен флаг получения ВСЕХ сообщений от мыши
	eventClick = click;
	eventDragged = false;
	Selected = false;

}

void TWrapButton::draw()
{
	drawState(False);
}

TAttrPair TWrapButton::getColor(ushort color)
{
	if ((Selected) && ((color ==1281) || (color == 1538) || (color == 1795)))
		return color_SelectedColor;
	if (eventDragged) //&& ((color == 1538) || (color == 1795) || (color == 8)))
		return color_DraggedColor;
	return TView::getColor(color);
}

bool TWrapButton::isSelected()
{
	return Selected;
}

void TWrapButton::setSelected(bool val)
{
	if (Selected != val)
	{
		Selected = val;
		drawView();
	}
}

void TWrapButton::setCaption(char* val)
{
	memset(title, 0x0, StringMaxLen);
	strncpy(title, val, StringMaxLen);
	drawView();
}

char* TWrapButton::getCaption()
{
	return title;
}

void TWrapButton::drawTitle(TDrawBuffer& b,
							int s,
							int i,
							TAttrPair cButton,
							Boolean down
)
{
	int l, scOff;
	if ((flags & bfLeftJust) != 0)
		l = 1;
	else
	{
		l = (s - cstrlen(title) - 1) / 2;
		if (l < 1)
			l = 1;
	}
	b.moveCStr(i + l, title, cButton);

	if (showMarkers == True && !down)
	{
		if ((state & sfSelected) != 0)
			scOff = 0;
		else if (amDefault)
			scOff = 2;
		else
			scOff = 4;
		b.putChar(0, specialChars[scOff]);
		b.putChar(s, specialChars[scOff + 1]);
	}
}

void TWrapButton::drawState(Boolean down)
{
	TAttrPair cButton, cShadow;
	TDrawBuffer b;

	if ((state & sfDisabled) != 0)
		cButton = getColor(0x0404);
	else
	{
		cButton = getColor(0x0501);
		if ((state & sfActive) != 0)
		{
			if ((state & sfSelected) != 0)
				cButton = getColor(0x0703);
			else if (amDefault)
				cButton = getColor(0x0602);
		}
	}
	cShadow = getColor(8);
	int s = size.x - 1;
	int T = size.y / 2 - 1;
	char ch = ' ';
	for (int y = 0; y <= size.y - 2; y++)
	{
		int i;
		b.moveChar(0, ' ', cButton, size.x);
		b.putAttribute(0, cShadow);
		if (down)
		{
			b.putAttribute(1, cShadow);
			ch = ' ';
			i = 2;
		}
		else
		{
			b.putAttribute(s, cShadow);
			if (showMarkers == True)
				ch = ' ';
			else
			{
				if (y == 0)
					b.putChar(s, shadows[0]);
				else
					b.putChar(s, shadows[1]);
				ch = shadows[2];
			}
			i = 1;
		}

		if (y == T && title != 0)
			drawTitle(b, s, i, cButton, down);

		if (showMarkers && !down)
		{
			b.putChar(1, markers[0]);
			b.putChar(s - 1, markers[1]);
		}
		writeLine(0, y, size.x, 1, b);
	}
	b.moveChar(0, ' ', cShadow, 2);
	b.moveChar(2, ch, cShadow, s - 1);
	writeLine(0, size.y - 1, size.x, 1, b);
}

TPalette& TWrapButton::getPalette() const
{
	static TPalette palette(cpButton, sizeof(cpButton) - 1);
	return palette;
}

void TWrapButton::handleEvent(TEvent& event)
{
	if (eventClick)
	{
		if (event.what | evMouse)
		{
			//-- Реакция на клик - сообщение о создании перетаскиваемого объекта
			if ((event.mouse.buttons == mbLeftButton) && (event.what == evMouseDown))
			{
				//-- берем координаты клика мышкой в глобальных координатах
				auto pt = event.mouse.where;
				//-- обязательно отсылаем ссылку на редактируемый компонент
				message(owner, evBroadcast, cm_cmp_CreateButton, &pt);
				clearEvent(event);
			}
		}
	}
	if (eventDragged)
	{
		if (event.what | evMouse)
		{
			if (event.what == evMouseDown)
			{
				auto rec = getBounds();
				event.mouse.where.x = rec.a.x;
				event.mouse.where.y = rec.a.y + 1;
				TPoint MinSz, MaxSz;
				//-- устанавливаем минимальные границы размера в размер хозяина объекта
				//-- так, чтобы изменение размеров и перемещение не выводило объект
				//-- за границы предка (окна в общем случае)
				auto lims = owner->getExtent();
				lims.grow(-1, -1);
				sizeLimits(MinSz, MaxSz);
				//-- адский косяк в том, что из функции перемещения мы выходим только ПОСЛЕ того, как пользователь отпустил мышь
				dragView(event, dragMode | dmDragMove, lims, MinSz, MaxSz);
				clearEvent(event);

				TEvent evDrop;
				evDrop.what = evBroadcast;
				evDrop.message.command = cm_drp_DropButton;
				TPoint* pt = new TPoint();
				pt->x = event.mouse.where.x;
				pt->y = event.mouse.where.y;
				evDrop.message.infoPtr = pt;
				putEvent(evDrop);
				clearEvent(event);
				auto parent = this->owner;
				destroy(this);
				parent->drawView();
				return;
			}
		}
	}
	if (Selected)
	{
		//-- переопределяем действия клавиш в режиме разработки
		if (event.what == evKeyDown)
		{
			//-- обработка нажатий служебных клавиш
			if (event.keyDown.keyCode == kbCtrlDel)
			{
				clearEvent(event);
				destroy(this);
				return;
			}
		}
	}
	TPoint mouse;
	TRect clickRect;

	clickRect = getExtent();
	clickRect.a.x++;
	clickRect.b.x--;
	clickRect.b.y--;

	if (event.what == evMouseDown)
	{
		mouse = makeLocal(event.mouse.where);
		if (!clickRect.contains(mouse))
			clearEvent(event);
	}
	if (flags & bfGrabFocus)
		TView::handleEvent(event);

	char c = hotKey(title);
	switch (event.what)
	{
		case evMouseDown:
			if ((state & sfDisabled) == 0)
			{
				clickRect.b.x++;
				Boolean down = False;
				do
				{
					mouse = makeLocal(event.mouse.where);
					if (down != clickRect.contains(mouse))
					{
						down = Boolean(!down);
						drawState(down);
					}
				} while (mouseEvent(event, evMouseMove));
				if (down)
				{
					press();
					drawState(False);
				}
			}
			clearEvent(event);
			break;

		case evKeyDown:
			if (event.keyDown.keyCode != 0 &&
				(event.keyDown.keyCode == getAltCode(c) ||
				 (owner->phase == phPostProcess &&
				  c != 0 &&
				  toupper(event.keyDown.charScan.charCode) == c
				  ) ||
				 ((state & sfFocused) != 0 &&
				  event.keyDown.charScan.charCode == ' '
				  )
				 )
				)
			{
				press();
				clearEvent(event);
			}
			break;

		case evBroadcast:
			switch (event.message.command)
			{
				case cmDefault:
					if (amDefault && !(state & sfDisabled))
					{
						press();
						clearEvent(event);
					}
					break;

				case cmGrabDefault:
				case cmReleaseDefault:
					if ((flags & bfDefault) != 0)
					{
						amDefault = Boolean(event.message.command == cmReleaseDefault);
						drawView();
					}
					break;

				case cmCommandSetChanged:
					setState(sfDisabled, Boolean(!commandEnabled(command)));
					drawView();
					break;
			}
			break;
	}
}

void TWrapButton::makeDefault(Boolean enable)
{
	if ((flags & bfDefault) == 0)
	{
		message(owner,
				evBroadcast,
				(enable == True) ? cmGrabDefault : cmReleaseDefault,
				this
		);
		amDefault = enable;
		drawView();
	}
}

void TWrapButton::setState(ushort aState, Boolean enable)
{
	if (aState == sfSelected)
	{
		setSelected(enable);
	}

	TView::setState(aState, enable);
	if (aState & (sfSelected | sfActive))
		drawView();
	if ((aState & sfFocused) != 0)
		makeDefault(enable);
}

void TWrapButton::press()
{
	message(owner, evBroadcast, cmRecordHistory, 0);
	if ((flags & bfBroadcast) != 0)
		message(owner, evBroadcast, command, this);
	else
	{
		TEvent e;
		e.what = evCommand;
		e.message.command = command;
		e.message.infoPtr = this;
		putEvent(e);
	}
}


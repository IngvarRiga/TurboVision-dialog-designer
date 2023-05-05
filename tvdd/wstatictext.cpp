#define Uses_TKeys

#include "wstatictext.h"
#include <tvision/tkeys.h>
#define cpStaticText "\x06"

TWrapStaticText::TWrapStaticText(const TRect& bounds, TStringView aText, bool click) noexcept :
	TView(bounds)
{
	growMode |= gfFixed;
	eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений от мыши
	memset(text, 0x0, StringMaxLen);
	strncpy(text, aText.data(), StringMaxLen);
	eventClick = click;
	eventDragged = false;
	Selected = false;
}

TAttrPair TWrapStaticText::getColor(ushort color)
{
	if (Selected)
		return color_SelectedColor;
	if (eventDragged)
		return color_DraggedColor;
	return TView::getColor(color);
}

void TWrapStaticText::draw()
{
	TColorAttr color;
	Boolean center;
	size_t i, j, p, y;
	TDrawBuffer b;
	char s[256];

	color = getColor(1);
	getText(s);
	auto l = strlen(s);
	p = 0;
	y = 0;
	center = False;
	while (y < size.y)
	{
		b.moveChar(0, ' ', color, size.x);
		if (p < l)
		{
			if (s[p] == 3)
			{
				center = True;
				++p;
			}
			i = p;
			auto last = i + TText::scroll(TStringView(&s[i], l - i), size.x, False);
			do
			{
				j = p;
				while ((p < l) && (s[p] == ' '))
					++p;
				while ((p < l) && (s[p] != ' ') && (s[p] != '\n'))
					p += TText::next(TStringView(&s[p], l - p));
			} while ((p < l) && (p < last) && (s[p] != '\n'));
			if (p > last)
			{
				if (j > i)
					p = j;
				else
					p = last;
			}
			int width = strwidth(TStringView(&s[i], p - i));
			if (center == True)
				j = (size.x - width) / 2;
			else
				j = 0;
			b.moveStr(j, TStringView(&s[i], l - i), color, (ushort)width);
			while ((p < l) && (s[p] == ' '))
				p++;
			if ((p < l) && (s[p] == '\n'))
			{
				center = False;
				p++;
			}
		}
		writeLine(0, y++, size.x, 1, b);
	}
}

TPalette& TWrapStaticText::getPalette() const
{
	static TPalette palette(cpStaticText, sizeof(cpStaticText) - 1);
	return palette;
}

void TWrapStaticText::getText(char* s)
{
	if (text == 0)
		*s = EOS;
	else
	{
		strncpy(s, text, 255);
		s[255] = EOS;
	}
}

bool TWrapStaticText::isSelected()
{
	return Selected;
}

void TWrapStaticText::setSelected(bool val)
{
	if (Selected != val)
	{
		Selected = val;
		drawView();
	}
}

void TWrapStaticText::setCaption(const char* val)
{
	memset(text, 0x0, StringMaxLen);
	strncpy(text, val, StringMaxLen);
	drawView();
}

char* TWrapStaticText::getCaption()
{
	return text;
}

void TWrapStaticText::handleEvent(TEvent& event)
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
				message(owner, evBroadcast, cm_cmp_CreateStaticText, &pt);
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
				evDrop.message.command = cm_drp_DropStaticText;
				TPoint* pt = new TPoint();
				pt->x = event.mouse.where.x;
				pt->y = event.mouse.where.y;
				evDrop.message.infoPtr = pt;
				putEvent(evDrop);
				auto parent = this->owner;
				destroy(this);
				parent->drawView();
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

}

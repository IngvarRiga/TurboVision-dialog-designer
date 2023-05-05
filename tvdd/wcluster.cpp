#define Uses_TKeys

#include "wcluster.h"
#include "common.h"
#include <tvision/tkeys.h>

#define cpCluster "\x10\x11\x12\x12\x1f"


TWrapCluster::TWrapCluster(const TRect& bounds, TSItem* aStrings, bool click) noexcept :
	TView(bounds),
	value(0),
	sel(0)
{
	options |= ofSelectable | ofFirstClick | ofPreProcess | ofPostProcess;

	recreateItems(aStrings);
	
	setCursor(2, 0);
	showCursor();
	enableMask = 0xFFFFFFFFL;

	eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений от мыши

	eventClick = click;
	eventDragged = false;
	Selected = false;

}

void TWrapCluster::recreateItems(TSItem* aStrings)
{
	if (strings != nullptr)
		destroy(strings);

	short i = 0;
	TSItem* p;
	for (p = aStrings; p != 0; p = p->next)
		i++;

	strings = new TStringCollection(i, 0);

	while (aStrings != 0)
	{
		p = aStrings;
		strings->atInsert(strings->getCount(), newStr(aStrings->value));
		aStrings = aStrings->next;
		delete p;
	}
}


TWrapCluster::~TWrapCluster()
{
	destroy((TCollection*)strings);
}

TAttrPair TWrapCluster::getColor(ushort color)
{
	if (Selected)
		return color_SelectedColor;
	if (eventDragged)
		return color_DraggedColor;
	return TView::getColor(color);
}
void TWrapCluster::setSelected(bool val)
{
	if (Selected != val)
	{
		Selected = val;
		drawView();
	}
}
ushort  TWrapCluster::dataSize()
{
	// value is now a long, but for compatibility with earlier TV,
	// return size of short; TMultiCheckBoxes returns sizeof(long).

	return sizeof(short);
}

void TWrapCluster::drawBox(const char* icon, char marker)
{
	char s[3];
	s[0] = ' '; s[1] = marker; s[2] = 0;
	drawMultiBox(icon, s);
}

void TWrapCluster::drawMultiBox(const char* icon, const char* marker)
{
	TDrawBuffer b;
	TAttrPair color;
	int i, j, cur;

	TAttrPair cNorm = getColor(0x0301);
	TAttrPair cSel = getColor(0x0402);
	TAttrPair cDis = getColor(0x0505);
	for (i = 0; i <= size.y; i++)
	{
		b.moveChar(0, ' ', cNorm, size.x);
		for (j = 0; j <= (strings->getCount() - 1) / size.y + 1; j++)
		{
			cur = j * size.y + i;
			if (cur < strings->getCount())
			{
				int col = column(cur);

				if (((col + strlen((const char*)strings->at(cur)) + 5)
					 < b.length()) && (col < size.x))
				{
					if (!buttonState(cur))
						color = cDis;
					else if ((cur == sel) && (state & sfSelected) != 0)
						color = cSel;
					else
						color = cNorm;
					b.moveChar(col, ' ', color, size.x - col);
					b.moveCStr(col, icon, color);

					b.putChar(col + 2, marker[multiMark(cur)]);
					b.moveCStr(col + 5, (char*)(strings->at(cur)), color);
					if (showMarkers && ((state & sfSelected) != 0) && cur == sel)
					{
						b.putChar(col, specialChars[0]);
						b.putChar(column(cur + size.y) - 1, specialChars[1]);
					}

				}
			}
		}
		writeBuf(0, i, size.x, 1, b);
	}
	setCursor(column(sel) + 2, row(sel));
}

void TWrapCluster::getData(void* rec)
{
	*(ushort*)rec = value;
	drawView();
}

ushort TWrapCluster::getHelpCtx()
{
	if (helpCtx == hcNoContext)
		return hcNoContext;
	else
		return helpCtx + sel;
}

TPalette& TWrapCluster::getPalette() const
{
	static TPalette palette(cpCluster, sizeof(cpCluster) - 1);
	return palette;
}

void TWrapCluster::moveSel(int i, int s)
{
	if (i <= strings->getCount())
	{
		sel = s;
		movedTo(sel);
		drawView();
	}
}

void TWrapCluster::handleEvent(TEvent& event)
{

	TView::handleEvent(event);
	if (!(options & ofSelectable))
		return;
	if (event.what == evMouseDown)
	{
		TPoint mouse = makeLocal(event.mouse.where);
		int i = findSel(mouse);
		if ((i != -1) && buttonState(i))
			sel = i;
		drawView();
		do
		{
			mouse = makeLocal(event.mouse.where);
			if ((findSel(mouse) == sel) && buttonState(sel))
				showCursor();
			else
				hideCursor();
		} while (mouseEvent(event, evMouseMove));
		showCursor();
		mouse = makeLocal(event.mouse.where);
		if (findSel(mouse) == sel)
		{
			press(sel);
			drawView();
		}
		clearEvent(event);
	}
	else if (event.what == evKeyDown)
	{
		int s = sel;
		switch (ctrlToArrow(event.keyDown.keyCode))
		{
			case kbUp:
				if ((state & sfFocused) != 0)
				{
					int i = 0;
					do
					{
						i++; s--;
						if (s < 0)
							s = strings->getCount() - 1;
					} while (!(buttonState(s) || (i > strings->getCount())));
					moveSel(i, s);
					clearEvent(event);
				}
				break;
			case kbDown:
				if ((state & sfFocused) != 0)
				{
					int i = 0;
					do
					{
						i++; s++;
						if (s >= strings->getCount())
							s = 0;
					} while (!(buttonState(s) || (i > strings->getCount())));
					moveSel(i, s);
					clearEvent(event);
				}
				break;
			case kbRight:
				if ((state & sfFocused) != 0)
				{
					int i = 0;
					do
					{
						i++; s += size.y;
						if (s >= strings->getCount())
							s = 0;
					} while (!(buttonState(s) || (i > strings->getCount())));
					moveSel(i, s);
					clearEvent(event);
				}
				break;
			case kbLeft:
				if ((state & sfFocused) != 0)
				{
					int i = 0;
					do
					{
						i++;
						if (s > 0)
						{
							s -= size.y;
							if (s < 0)
							{
								s = ((strings->getCount() + size.y - 1) /
									 size.y) * size.y + s - 1;
								if (s >= strings->getCount())
									s = strings->getCount() - 1;
							}
						}
						else
							s = strings->getCount() - 1;
					} while (!(buttonState(s) || (i > strings->getCount())));
					moveSel(i, s);
					clearEvent(event);
				}
				break;
			default:
				for (int i = 0; i < strings->getCount(); i++)
				{
					char c = hotKey((char*)(strings->at(i)));
					if (event.keyDown.keyCode != 0 &&
						(getAltCode(c) == event.keyDown.keyCode ||
						 ((owner->phase == phPostProcess ||
						   (state & sfFocused) != 0
						   ) &&
						  c != 0 &&
						  toupper(event.keyDown.charScan.charCode) == c
						  )
						 )
						)
					{
						if (buttonState(i))
						{
							if (focus())
							{
								sel = i;
								movedTo(sel);
								press(sel);
								drawView();
							}
							clearEvent(event);
						}
						return;
					}
				}
				if (event.keyDown.charScan.charCode == ' ' &&
					(state & sfFocused) != 0
					)
				{
					press(sel);
					drawView();
					clearEvent(event);
				}
		}
	}
}


void TWrapCluster::setButtonState(uint32_t aMask, Boolean enable)
{
	if (!enable)
		enableMask &= ~aMask;
	else
		enableMask |= aMask;

	int n = strings->getCount();
	if (n < 32)
	{
		uint32_t testMask = (1 << n) - 1;
		if ((enableMask & testMask) != 0)
			options |= ofSelectable;
		else
			options &= ~ofSelectable;
	}
}


void TWrapCluster::setData(void* rec)
{
	value = *(ushort*)rec;
	drawView();
}

void TWrapCluster::setState(ushort aState, Boolean enable)
{
	TView::setState(aState, enable);
	if (aState == sfSelected)
		drawView();
}

Boolean TWrapCluster::mark(int)
{
	return False;
}

uchar TWrapCluster::multiMark(int item)
{
	return (uchar)(mark(item) == True);
}

void TWrapCluster::movedTo(int)
{}

void TWrapCluster::press(int)
{}

int TWrapCluster::column(int item)
{
	if (item < size.y)
		return 0;
	else
	{
		int width = 0;
		int col = -6;
		int l = 0;
		for (int i = 0; i <= item; i++)
		{
			if (i % size.y == 0)
			{
				col += width + 6;
				width = 0;
			}

			if (i < strings->getCount())
				l = cstrlen((char*)(strings->at(i)));
			if (l > width)
				width = l;
		}
		return col;
	}
}

int TWrapCluster::findSel(TPoint p)
{
	TRect r = getExtent();
	if (!r.contains(p))
		return -1;
	else
	{
		int i = 0;
		while (p.x >= column(i + size.y))
			i += size.y;
		int s = i + p.y;
		if (s >= strings->getCount())
			return -1;
		else
			return s;
	}
}

int TWrapCluster::row(int item)
{
	return item % size.y;
}

Boolean TWrapCluster::buttonState(int item)
{
#if !defined(__FLAT__)
	ushort maskLo = enableMask & 0xffff;
	ushort maskHi = enableMask >> 16;

	asm{
			XOR     AL,AL
			MOV     CX,item
			CMP     CX,31
			JA      __3
			MOV     AX,1
			XOR     DX,DX
			JCXZ    __2
	}
	__1:
	asm{
			SHL     AX,1
			RCL     DX,1
			LOOP    __1
	}
	__2:
	asm{
			AND     AX,maskLo
			AND     DX,maskHi
			OR      AX,DX
			JZ      __3
			MOV     AL,1
	}
	__3:
	return Boolean(_AL);
#else
	if (item < 32)
	{
		uint32_t mask = 1;

		while (item--)
			mask <<= 1;

		if (enableMask & mask)
			return True;
		else
			return False;
	}
	else
		return False;
#endif
}

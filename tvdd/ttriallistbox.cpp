#include "ttriallistbox.h"
#include "multilang.h"

TTrialListBox::TTrialListBox(const TRect& bounds, ushort aNumCols, TScrollBar* aScrollBar) :
	TListBox(bounds, aNumCols, aScrollBar)
{
	eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
	options |= ofPreProcess;
	//-- ограничиваем перемещение внутри окна его границами
	dragMode |= dmLimitAll;
	Selected = false;
	memset(var_name, 0x0, StringMaxLen);
	memset(class_name, 0x0, StringMaxLen);
	strncpy(var_name, txt_control, strlen(txt_control));
	strncpy(class_name, txt_TListBox, strlen(txt_TListBox));

}

void TTrialListBox::draw()
{
	//-- полностью переопределяем процедуру отрисовки, поскольку в дизайнере нам нужны некоторые спецэффекты
	TListBox::draw();
}

void TTrialListBox::setState(ushort aState, Boolean enable)
{
	TView::setState(aState, enable);
	if (aState == sfSelected)
	{
		setSelected(enable);
	}
}

void TTrialListBox::handleEvent(TEvent& event)
{
	if (event.what | evMouse)
	{
		message(owner, evBroadcast, cm_DisableCursorPaint, 0);

		//-- вызов окна редактирования свойств объекта
		if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
		{
			message(owner, evBroadcast, cmOption_ListBox, nullptr);
			clearEvent(event);
		}
		if (event.mouse.buttons == mbRightButton)
			if (event.what == evMouseUp)
			{
				//-- создание контекстного меню диалога
				TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
													 new TMenu(
													 *new TMenuItem(txt_PropertyListBox, cmOption_ListBox, -1, hcNoContext) +
													 newLine() +
													 *new TMenuItem(txt_mnu_cmDelete, cm_ed_DestroyListBox, kbCtrlDel, hcNoContext)), nullptr);

				TPoint tmp;
				tmp.x = event.mouse.where.x;
				tmp.y = event.mouse.where.y;
				clearEvent(event);

				//-- смещаем левую верхнюю точку меню в точку клика мышкой на экране
				auto b = contextMenu->getBounds();
				auto dx = b.b.x - b.a.x;
				auto dy = b.b.y - b.a.y;
				b.a.x = tmp.x;
				b.a.y = tmp.y - 1;
				b.b.x = b.a.x + dx;
				b.b.y = b.a.y + dy;
				contextMenu->setBounds(b);
				//---------------------------------------------------------------------
				auto res = this->owner->owner->execView(contextMenu);
				destroy(contextMenu);
				if (res == cm_ed_DestroyListBox)
				{
					destroy(this);
					return;
				}
				else
				{
					//-- рассылаем команды
					if (res != 0)
						message(owner, evBroadcast, res, this);
				}
			}

		if (event.what == evMouseDown)
		{
			owner->forEach(&unselected, 0);
			setState(sfSelected, true);
			DragObject(this, event);
			clearEvent(event);
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

	TListBox::handleEvent(event);
}

void TTrialListBox::sizeLimits(TPoint& min, TPoint& max)
{
	TListBox::sizeLimits(min, max);
	min.x = 1;
	min.y = 1;
	max.x -= 2;
	max.y -= 2;
}

bool TTrialListBox::isSelected()
{
	return Selected;
}

void TTrialListBox::setSelected(bool val)
{
	if (Selected != val)
	{
		Selected = val;
		drawView();
	}
}

void TTrialListBox::genCode(void* val)
{
	ofstream* res = (ofstream*)val;
	auto r = getBounds();

	//-- генерируем код компонента
	*res << "\n " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), 1, nullptr );";
	*res << "\n insert(" << var_name << ");";

}


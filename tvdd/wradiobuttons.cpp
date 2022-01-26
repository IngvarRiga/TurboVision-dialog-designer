#include "wradiobuttons.h"
#include <tvision/tkeys.h>

const char* const TWrapRadioButtons::name = "TWrapRadioButtons";
const char* TWrapRadioButtons::button = " ( ) ";

void TWrapRadioButtons::draw()
{
	drawMultiBox(button, " \x7");
}

Boolean TWrapRadioButtons::mark(int item)
{
	return Boolean(item == (int)value);
}

void TWrapRadioButtons::press(int item)
{
	value = item;
}

void TWrapRadioButtons::movedTo(int item)
{
	value = item;
}

void TWrapRadioButtons::setData(void* rec)
{
	TWrapCluster::setData(rec);
	sel = (int)value;
}

void TWrapRadioButtons::handleEvent(TEvent& event)
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
				message(owner, evBroadcast, cm_cmp_CreateRadioButtons, &pt);
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
				evDrop.message.command = cm_drp_DropRadioButtons;
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


	TWrapCluster::handleEvent(event);
}

#if !defined(NO_STREAMABLE)

TStreamable* TWrapRadioButtons::build()
{
	return new TWrapRadioButtons(streamableInit);
}

TWrapRadioButtons::TWrapRadioButtons(StreamableInit) noexcept : TWrapCluster(streamableInit)
{}

TStreamableClass RWrapRadioButtons(
	TWrapRadioButtons::name,
	TWrapRadioButtons::build,
	__DELTA(TWrapRadioButtons)
);

__link(RWrapCluster)
__link(RWrapRadioButtons)
#endif



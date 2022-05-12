#include "wcheckboxes.h"
#include <tvision/tkeys.h>

//const char* const TWrapCheckBoxes::name = "TWrapCheckBoxes";
const char* TWrapCheckBoxes::button = " [ ] ";

void TWrapCheckBoxes::draw()
{
	drawMultiBox(button, " X");
}

Boolean TWrapCheckBoxes::mark(int item)
{
	return Boolean((value & (1 << item)) != 0);
}

void TWrapCheckBoxes::press(int item)
{
	value = value ^ (1 << item);
}

void TWrapCheckBoxes::handleEvent(TEvent& event)
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
				message(owner, evBroadcast, cm_cmp_CreateCheckBoxes, &pt);
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
				evDrop.message.command = cm_drp_DropCheckBoxes;
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

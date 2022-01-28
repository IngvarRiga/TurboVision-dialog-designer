#include "ttrialmemo.h"
#include "common.h"

const char* const TTrialMemo::name = "TTrialMemo";

TTrialMemo::TTrialMemo(const TRect& bounds,
					   TScrollBar* aHScrollBar,
					   TScrollBar* aVScrollBar,
					   TIndicator* aIndicator,
					   ushort aBufSize) :
	TMemo(bounds,aHScrollBar,aVScrollBar,aIndicator,aBufSize)
{
	eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений
	options |= ofPreProcess;
	//-- ограничиваем перемещение внутри окна его границами
	dragMode |= dmLimitAll;
	//Selected = false;
	memset(var_name, 0x0, StringMaxLen);
	memset(class_name, 0x0, StringMaxLen);
	strncpy(var_name, txt_control, strlen(txt_control));
	strncpy(class_name, txt_TMemo, strlen(txt_TMemo));
	Selected = false;
}

void TTrialMemo::handleEvent(TEvent& event)
{
	if (event.what | evMouse)
	{
		//-- вызов окна редактирования свойств объекта
		if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
		{
			message(owner, evBroadcast, cmOption_Button, this);
			clearEvent(event);
		}
		//-- Реакция на клик - выбор текущего объекта
		if (event.what == evMouseDown)
		{
			owner->forEach(&unselected, 0);
			setSelected(true);
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

	TMemo::handleEvent(event);
}

void TTrialMemo::setState(ushort aState, Boolean enable)
{
	TMemo::setState(aState, enable);
	if (aState == sfSelected)
	{
		if (!enable)
			setSelected(enable);
	}
}

bool TTrialMemo::isSelected()
{
	return Selected;
}

void TTrialMemo::setSelected(bool val)
{
	if (Selected != val)
	{
		Selected = val;
		drawView();
	}
}

void TTrialMemo::sizeLimits(TPoint& min, TPoint& max)
{
	TMemo::sizeLimits(min, max);
	min.x = 1;
	min.y = 1;
	max.x -= 2;
	//-- строка ввода занимает только одну строчку!
	max.y -= 2;
}


void TTrialMemo::genCode(void* val)
{
	ofstream* res = (ofstream*)val;
	auto r = getBounds();

	//-- генерируем код компонента
	*res << "\n " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), nullptr, nullptr, nullptr, 255 );";
	*res << "\n insert(" << var_name << ");";

}

TStreamable* TTrialMemo::build()
{
	return new TTrialMemo(streamableInit);
}

char* TTrialMemo::getVarName()
{
	return var_name;
}

void TTrialMemo::setClassName(char* val)
{
	memset(class_name, 0x0, StringMaxLen);
	auto len = strlen(val);
	if (len > 0)
		memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialMemo::getClassName()
{
	return class_name;
}

void TTrialMemo::setVarName(char* val)
{
	memset(var_name, 0x0, StringMaxLen);
	auto len = strlen(val);
	if (len > 0)
		memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}


void TTrialMemo::write(opstream& os)
{

	TMemo::write(os);
	os.writeBytes((void*)var_name, StringMaxLen);
	os.writeBytes((void*)class_name, StringMaxLen);
	os << eventMask << options << dragMode;

}

void* TTrialMemo::read(ipstream& is)
{
	TMemo::read(is);
	is.readBytes((void*)var_name, StringMaxLen);
	is.readBytes((void*)class_name, StringMaxLen);
	is >> eventMask >> options >> dragMode;
	return this;
}


TStreamableClass RTrialMemo(
	TTrialMemo::name,
	TTrialMemo::build,
	__DELTA(TTrialMemo)
);

__link(RScrollBar)
__link(RMemo)
__link(RTrialMemo)


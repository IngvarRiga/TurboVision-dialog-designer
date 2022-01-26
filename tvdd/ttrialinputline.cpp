#include "ttrialinputline.h"
#include "common.h"

const char* const TTrialInputLine::name = "TTrialInputLine";

TTrialInputLine::TTrialInputLine(const TRect& bounds, uint aMaxLen, TValidator* aValid) :
	TWrapInputLine(bounds, aMaxLen, aValid)
{
	eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
	options |= ofPreProcess;
	//-- ограничиваем перемещение внутри окна его границами
	dragMode |= dmLimitAll;
	Selected = false;
	memset(var_name, 0x0, StringMaxLen);
	memset(class_name, 0x0, StringMaxLen);
	strncpy(var_name, txt_control, strlen(txt_control));
	strncpy(class_name, txt_TInputLine, strlen(txt_TInputLine));

}

void TTrialInputLine::handleEvent(TEvent& event)
{
	if (event.what | evMouse)
	{
		//-- вызов окна редактирования свойств объекта
		if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
		{
			message(owner, evBroadcast, cmOption_InputLine, this);
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

	TWrapInputLine::handleEvent(event);
}

void TTrialInputLine::setState(ushort aState, Boolean enable)
{
	TWrapInputLine::setState(aState, enable);
	if (aState == sfSelected)
	{
		if (!enable)
			setSelected(enable);
	}
}

void TTrialInputLine::sizeLimits(TPoint& min, TPoint& max)
{
	TWrapInputLine::sizeLimits(min, max);
	min.x = 1;
	min.y = 1;
	max.x -= 2;
	//-- строка ввода занимает только одну строчку!
	max.y = 1;
}

bool TTrialInputLine::isSelected()
{
	return Selected;
}

void TTrialInputLine::setSelected(bool val)
{
	if (Selected != val)
	{
		Selected = val;
		drawView();
	}
}

void TTrialInputLine::genCode(void* val)
{
	ofstream* res = (ofstream*)val;
	auto r = getBounds();

	//-- генерируем код компонента
	*res << "\n auto " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), " << maxLen << ");";
	*res << "\n insert(" << var_name << ");\n";
	
}

TStreamable* TTrialInputLine::build()
{
	return new TTrialInputLine(streamableInit);
}

char* TTrialInputLine::getVarName()
{
	return var_name;
}

uint TTrialInputLine::getVarLen()
{
	return maxLen;
}
void TTrialInputLine::setClassName(char* val)
{
	memset(class_name, 0x0, StringMaxLen);
	auto len = strlen(val);
	if (len > 0)
		memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialInputLine::getClassName()
{
	return class_name;
}

void TTrialInputLine::setVarName(char* val)
{
	memset(var_name, 0x0, StringMaxLen);
	auto len = strlen(val);
	if (len > 0)
		memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}



void TTrialInputLine::setVarLen(uint val)
{
	maxLen = val;
}

void TTrialInputLine::write(opstream& os)
{

	TWrapInputLine::write(os);
	os.writeBytes((void*)var_name, StringMaxLen);
	os.writeBytes((void*)class_name, StringMaxLen);
	os << eventMask << options << dragMode;

}

void* TTrialInputLine::read(ipstream& is)
{
	TWrapInputLine::read(is);
	is.readBytes((void*)var_name, StringMaxLen);
	is.readBytes((void*)class_name, StringMaxLen);
	is >> eventMask >> options >> dragMode;
	return this;
}


TStreamableClass RTrialInputLine(
	TTrialInputLine::name,
	TTrialInputLine::build,
	__DELTA(TTrialInputLine)
);

__link(RWrapInputLine)
__link(RTrialInputLine)



#include "ttrialbutton.h"
#include "common.h"

const char* const TTrialButton::name = "TTrialButton";

TTrialButton::TTrialButton(const TRect& bounds,
						   TStringView aTitle,
						   ushort aCommand,
						   ushort aFlags) :
	TWrapButton(bounds, aTitle, aCommand, aFlags)
{
	eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений
	options |= ofPreProcess;
	//-- ограничиваем перемещение внутри окна его границами
	dragMode |= dmLimitAll;
	//-- заданное имя переменной используется при генерации кода
	usedVarName = false; //-- по умолчанию -выключено!
	memset(var_name, 0x0, StringMaxLen);
	memset(class_name, 0x0, StringMaxLen);
	strncpy(var_name, txt_control, strlen(txt_control));
	strncpy(class_name, txt_TButton, strlen(txt_TButton));

}

void TTrialButton::setState(ushort aState, Boolean enable)
{
	TWrapButton::setState(aState, enable);
	if (aState == sfSelected)
	{
		setSelected(enable);
	}
}

void TTrialButton::handleEvent(TEvent& event)
{
	if (event.what | evMouse)
	{
		//-- вызов окна редактирования свойств объекта
		if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
		{
			message(owner, evBroadcast, cmOption_Button, this);
			clearEvent(event);
		}
		if (event.what == evMouseDown)
		{
			owner->forEach(&unselected, 0);
			setState(sfSelected, true);
			//select();
			DragObject(this, event);
			clearEvent(event);
		}
	}

	TWrapButton::handleEvent(event);
}

void TTrialButton::sizeLimits(TPoint& min, TPoint& max)
{
	TWrapButton::sizeLimits(min, max);
	min.x = 5; //-- минимальная ширина = 5 символов - для одного символа на самой кнопке
	min.y = 2; //-- высота ограничена константой
	max.x -= 2;
	//-- строка ввода занимает только одну строчку!
	max.y = 2;
}

char* TTrialButton::getVarName()
{
	return var_name;
}

char* TTrialButton::getClassName()
{
	return class_name;
}

bool TTrialButton::getUsedVarName()
{
	return usedVarName;
}

void TTrialButton::setVarName(char* val)
{
	memset(var_name, 0x0, StringMaxLen);
	auto len = strlen(val);
	if (len > 0)
		memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialButton::setClassName(char* val)
{
	memset(class_name, 0x0, StringMaxLen);
	auto len = strlen(val);
	if (len > 0)
		memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialButton::setUsedVarName(bool val)
{
	usedVarName = val;
}

void TTrialButton::genCode(char* val)
{
	//-- генерируем код компонента
	char tmp[StringMaxLen];
	memset(tmp, 0x0, StringMaxLen);
	auto t = "\n insert(new TButton(TRect(";
	strncat(val, t, strlen(t));
	auto r = getBounds();
	_itoa(r.a.x, tmp, 10);
	strncat(val, tmp, strlen(tmp));
	strncat(val, ",", 1);
	memset(tmp, 0x0, StringMaxLen);

	_itoa(r.a.y, tmp, 10);
	strncat(val, tmp, strlen(tmp));
	strncat(val, ",", 1);
	memset(tmp, 0x0, StringMaxLen);

	_itoa(r.b.x, tmp, 10);
	strncat(val, tmp, strlen(tmp));
	strncat(val, ",", 1);
	memset(tmp, 0x0, StringMaxLen);

	_itoa(r.b.y, tmp, 10);
	strncat(val, tmp, strlen(tmp));
	memset(tmp, 0x0, StringMaxLen);

	strncat(val, "), \"", 4);
	strncat(val, title, strlen(title));
	memset(tmp, 0x0, StringMaxLen);
	strncat(val, "\", -1, -1));", 11);

}

TStreamable* TTrialButton::build()
{
	return new TTrialButton(streamableInit);
}

void TTrialButton::write(opstream& os)
{

	TWrapButton::write(os);
	os.writeBytes(&usedVarName, sizeof(usedVarName));
	os.writeBytes((void*)var_name, StringMaxLen);
	os.writeBytes((void*)class_name, StringMaxLen);
	os << eventMask << options << dragMode;
}

void* TTrialButton::read(ipstream& is)
{
	TWrapButton::read(is);
	is.readBytes(&usedVarName, sizeof(usedVarName));
	is.readBytes((void*)var_name, StringMaxLen);
	is.readBytes((void*)class_name, StringMaxLen);
	is >> eventMask >> options >> dragMode;
	return this;
}


TStreamableClass RTrialButton(
	TTrialButton::name,
	TTrialButton::build,
	__DELTA(TTrialButton)
);

__link(RWrapButton)
__link(RTrialButton)


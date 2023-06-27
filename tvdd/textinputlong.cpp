#include "textrainput.h"
#include <string>
using namespace std;

TInputLong::TInputLong(const TRect& bounds, long MinValue, long MaxValue, long DefValue, bool allow_not_def) :
	TInputLine(bounds, 12)
{
	AllowNotDefined = allow_not_def;
	//-- устанавливаем правильные значения
	if (MinValue < MaxValue)
	{
		minv = MinValue;
		maxv = MaxValue;
	}
	else
	{
		//-- если неправильно заданы, то меняем их местами
		maxv = MinValue;
		minv = MaxValue;
	}
	if (CheckValue(DefValue))
		value = def_value = DefValue;
	else
	{
		ShowError();
		if (CheckValue(0))
			value = 0;
		else
			//-- усредняем
			value = (maxv + minv) / 2L;
	}
	TInputLine::setData((void*)to_string(value).c_str());
}

void TInputLong::handleEvent(TEvent& event)
{
	if (event.what | evMouse)
	{
		if (event.mouse.buttons == mbRightButton)
			if (event.what == evMouseDown)
			{
				//-- создание контекстного меню диалога
				TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
					new TMenu(
						*new TMenuItem(txt_set_Minimum + std::to_string(minv), (ushort)TNumericInputCommand::cmSetMinimum, kbNoKey) +
						newLine() +
						*new TMenuItem(txt_set_Default + std::to_string(def_value), (ushort)TNumericInputCommand::cmSetDefault, kbNoKey) +
						newLine() +
						*new TMenuItem(txt_set_Maximum + std::to_string(maxv), (ushort)TNumericInputCommand::cmSetMaximum, kbNoKey)
					), nullptr);

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
				switch (res)
				{
				case (ushort)TNumericInputCommand::cmSetMinimum:
					setValue(minv);
					return;
					break;
				case (ushort)TNumericInputCommand::cmSetDefault:
					setValue(def_value);
					return;
					break;
				case (ushort)TNumericInputCommand::cmSetMaximum:
					setValue(maxv);
					return;
					break;
				}
			}
	}
	TInputLine::handleEvent(event);
}

void TInputLong::ShowError()
{
	messageBox(getDiap().c_str(), mfError | mfOKButton);
}

std::string TInputLong::getDiap()
{
	std::string str = std::to_string(minv) + ' ' + (char)0x1D + ' ' + std::to_string(maxv);
	return str;
}

bool TInputLong::CheckValue(long val)
{
	if ((val >= minv) && (val <= maxv))
		return true;
	else
		return false;
}

bool TInputLong::isNotDefined()
{
	if (AllowNotDefined)
		return notDefined;
	else
		return false;
}

void TInputLong::setUndefined()
{
	if (AllowNotDefined)
		notDefined = true;
	else
		notDefined = false;
	drawView();
}
void TInputLong::setMaxValue(long val)
{
	maxv = val;
	CheckValue(value);
	drawView();
}
void TInputLong::setMinValue(long val)
{
	minv = val;
	CheckValue(value);
	drawView();
}
void TInputLong::setDefValue(long val)
{
	def_value = val;
	CheckValue(value);
	drawView();
}
void TInputLong::setAllowNotDefined(bool val)
{
	AllowNotDefined = val;
	drawView();
}

long TInputLong::getMaxValue()
{
	return maxv;
}
long TInputLong::getMinValue()
{
	return minv;
}
long TInputLong::getDefValue()
{
	return def_value;
}
bool TInputLong::getAllowNotDefined()
{
	return AllowNotDefined;
}

void TInputLong::setValue(long val)
{
	//-- если не равно уже установленному...
	if (val != value)
	{
		if (CheckValue(val))
			value = val;
		if (val > maxv)
			value = maxv;
		if (val < minv)
			value = minv;
		TInputLine::setData((void*)to_string(value).c_str());
		drawView();
	}
}

bool TInputLong::convert(const char* tmp, long* out)
{
	if (strlen(tmp) == 0) return false;
	char* ptr;
	errno = 0;
	//-- преобразование в тип long
	*out = strtol(tmp, &ptr, 10);
	//*out = (long)strtold(tmp, &ptr);
	//-- если мусор в строке есть, то ошибка
	if (strlen(ptr) > 0) return false;
	//-- если вне диапазона, то ошибка
	if (errno == ERANGE) return false;
	return true;
}

void TInputLong::draw()
{
	int l, r;
	TDrawBuffer b;

	auto str = getDiap();

	char buff_diap[512];
	memset(buff_diap, 0x0, 512);
	str.copy(buff_diap, str.length());
	TColorAttr color = getColor((state & sfFocused) ? 2 : 1);

	long res = 0;
	auto cr = convert(data, &res);

	//-- проверяем, что заданное число лежит в допустимых пределах
	if (cr)
		cr = CheckValue(res);

	if (cr)
	{
		//-- нормальная отрисовка
		b.moveChar(0, ' ', color, size.x);
		value = res;
	}
	else
	{
		value = LONG_MIN;
		if (AllowNotDefined && (strlen(data) == 0))
			b.moveChar(0, ' ', color_Undefined, size.x);
		else
		{
			b.moveChar(0, ' ', color_Error, size.x);
		}
	}

	if (size.x > 1)
	{
		if (cr)
			b.moveStr(1, data, color, size.x - 1, firstPos);
		else
			if (strlen(data) == 0)
			{
				if (AllowNotDefined)
					b.moveStr(1, buff_diap, color_Undefined, size.x - 1, firstPos);
				else
					b.moveStr(1, buff_diap, color_Info, size.x - 1, firstPos);
			}
			else
				b.moveStr(1, data, color_Info, size.x - 1, firstPos);
	}
	if (canScroll(1))
		b.moveChar(size.x - 1, rightArrow, getColor(4), 1);
	if (canScroll(-1))
		b.moveChar(0, leftArrow, getColor(4), 1);
	if ((state & sfSelected) != 0)
	{
		l = displayedPos(selStart) - firstPos;
		r = displayedPos(selEnd) - firstPos;
		l = max(0, l);
		r = min(size.x - 2, r);
		if (l < r)
			b.moveChar(l + 1, 0, getColor(3), r - l);
	}
	writeLine(0, 0, size.x, size.y, b);
	setCursor(displayedPos(curPos) - firstPos + 1, 0);
}

Boolean TInputLong::canScroll(int delta)
{
	if (delta < 0)
		return Boolean(firstPos > 0);
	else
		if (delta > 0)
			return Boolean(strwidth(data) - firstPos + 2 > size.x);
		else
			return False;
}

int TInputLong::displayedPos(int pos)
{
	return strwidth(TStringView(data, pos));
}

long TInputLong::getValue()
{
	if (isNotDefined())
		return LONG_MIN;
	else
		return value;
}
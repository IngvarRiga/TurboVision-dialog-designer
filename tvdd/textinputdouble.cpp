#include "textrainput.h"
#include <string>
using namespace std;

TInputDouble::TInputDouble(const TRect& bounds, long double MinValue, long double MaxValue, long double DefValue, uint precision) :
	TInputLine(bounds, 255)
{
	prec = precision;
	if (prec <= 0) prec = 1;
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
			value = DefValue;
		else
			//-- усредняем
			value = (maxv + minv) / 2.0L;
	}
	setValue(value);
}


void TInputDouble::handleEvent(TEvent& event)
{
	if (event.what | evMouse)
	{
		if (event.mouse.buttons == mbRightButton)
			if (event.what == evMouseDown)
			{
				std::string fmin = convert_to_exp(minv);
				std::string fdef = convert_to_exp(def_value);
				std::string fmax = convert_to_exp(maxv);
				//-- создание контекстного меню диалога
				TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
					new TMenu(
						*new TMenuItem(txt_set_Minimum + fmin, (ushort)TNumericInputCommand::cmSetMinimum, kbNoKey) +
						newLine() +
						*new TMenuItem(txt_set_Default + fdef, (ushort)TNumericInputCommand::cmSetDefault, kbNoKey) +
						newLine() +
						*new TMenuItem(txt_set_Maximum + fmax, (ushort)TNumericInputCommand::cmSetMaximum, kbNoKey)
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

void TInputDouble::ShowError()
{
	messageBox(getDiap().c_str(), mfError | mfOKButton);
}

bool TInputDouble::CheckValue(long double val)
{
	if ((val >= minv) && (val <= maxv))
		return true;
	else
		return false;
}

void TInputDouble::setValue(long double val)
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
	}
	std::string valt = convert_to_exp(value);
	TInputLine::setData((void*)valt.c_str());
	drawView();
}

bool TInputDouble::convert(const char* tmp, long double* out)
{
	if (strlen(tmp) == 0) return false;
	char* ptr;
	errno = 0;
	//-- преобразование в тип long double
	*out = (long double)strtold(tmp, &ptr);
	//-- если мусор в строке есть, то ошибка
	if (strlen(ptr) > 0) return false;
	//-- если вне диапазона, то ошибка
	if (errno == ERANGE) return false;
	return true;
}

std::string TInputDouble::convert_to_exp(long double val)
{
	char buffer[255];
	memset(buffer, 0, sizeof(buffer));
	//-- вне указанных пределов все в экспоненте
	if (val == 0.0)
	{
		snprintf(buffer, sizeof(buffer), "%1.1f", 0.0);
	}
	else
	{
		if ((val < 0.0001L) || (val > 9000.0L))
		{
			std::string _prec = "%1." + to_string(prec) + "e";
			snprintf(buffer, sizeof(buffer), _prec.c_str(), val);
		}
		else
		{
			//-- внутри пределов - значение с пплавающей точкой
			std::string _prec = "%###1." + to_string(prec) + "f";
			snprintf(buffer, sizeof(buffer), _prec.c_str(), val);
		}
	}
	std::string result = buffer;
	return result;
}

std::string TInputDouble::getDiap()
{
	std::string fmin(convert_to_exp(minv));
	std::string fmax(convert_to_exp(maxv));

	std::string str = fmin + ' ' + (char)0x1D + ' ' + fmax;
	return str;
}

void TInputDouble::draw()
{
	int l, r;
	TDrawBuffer b;

	auto diap = getDiap();

	char buff_diap[512];
	memset(buff_diap, 0x0, 512);
	diap.copy(buff_diap, diap.length());
	TColorAttr color = getColor((state & sfFocused) ? 2 : 1);

	long double res = 0.0;
	auto cr = convert(data, &res);
	if (cr)
		cr = CheckValue(res);

	if (cr)
	{
		b.moveChar(0, ' ', color, size.x);
		value = res;
	}
	else
	{
		b.moveChar(0, ' ', 0x4f/*color*/, size.x);
		value = LONG_MIN;
	}

	if (size.x > 1)
	{
		if (cr)
			b.moveStr(1, data, color, size.x - 1, firstPos);
		else
			if (strlen(data) == 0)
				b.moveStr(1, buff_diap, 0x47, size.x - 1, firstPos);
			else
				b.moveStr(1, data, 0x4f, size.x - 1, firstPos);
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

Boolean TInputDouble::canScroll(int delta)
{
	if (delta < 0)
		return Boolean(firstPos > 0);
	else
		if (delta > 0)
			return Boolean(strwidth(data) - firstPos + 2 > size.x);
		else
			return False;
}

int TInputDouble::displayedPos(int pos)
{
	return strwidth(TStringView(data, pos));
}

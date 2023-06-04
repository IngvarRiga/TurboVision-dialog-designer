#include "textrainput.h"
#include <string>
using namespace std;

TInputDouble::TInputDouble(const TRect& bounds, long double MinValue, long double MaxValue, long double DefValue) :
	TInputLine(bounds, 12)
{
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
		value = DefValue;
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

void TInputDouble::ShowError()
{
	std::string str = std::to_string(minv) + ' ' + (char)0x1D + ' ' + std::to_string(maxv);
	messageBox(str.c_str(), mfError | mfOKButton);
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
		TInputLine::setData((void*)to_string(value).c_str());
		drawView();
	}
}

bool TInputDouble::convert(const char* tmp, long double* out)
{
	if (strlen(tmp) == 0) return false;
	char* ptr;
	errno = 0;
	//-- преобразование в тип long double
	*out = (long)strtold(tmp, &ptr);
	//-- если мусор в строке есть, то ошибка
	if (strlen(ptr) > 0) return false;
	//-- если вне диапазона, то ошибка
	if (errno == ERANGE) return false;
	return true;
}

void TInputDouble::draw()
{
	int l, r;
	TDrawBuffer b;

	std::string str = std::to_string(minv) + ' ' + (char)0x1D + ' ' + std::to_string(maxv);
	char buff_diap[512];
	memset(buff_diap, 0x0, 512);
	str.copy(buff_diap, str.length());
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

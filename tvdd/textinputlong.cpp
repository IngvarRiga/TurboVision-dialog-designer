#include "textrainput.h"
#include <string>
using namespace std;

TInputLong::TInputLong(const TRect& bounds, long MinValue, long MaxValue, long DefValue) :
	TInputLine(bounds, 12)
{
	//-- ������������� ���������� ��������
	if (MinValue < MaxValue)
	{
		minv = MinValue;
		maxv = MaxValue;
	}
	else
	{
		//-- ���� ����������� ������, �� ������ �� �������
		maxv = MinValue;
		minv = MaxValue;
	}
	if (CheckValue(DefValue))
		value = DefValue;
	else
	{
		ShowError();
		if (CheckValue(0))
			value = 0;
		else
			//-- ���������
			value = (maxv + minv) / 2L;
	}
	TInputLine::setData((void*)to_string(value).c_str());
}

void TInputLong::ShowError()
{
	std::string str = std::to_string(minv) + ' ' + (char)0x1D + ' ' + std::to_string(maxv);
	messageBox(str.c_str(), mfError | mfOKButton);
}

bool TInputLong::CheckValue(long val)
{
	if ((val >= minv) && (val <= maxv))
		return true;
	else
		return false;
}

void TInputLong::setValue(long val)
{
	//-- ���� �� ����� ��� ��������������...
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
	//-- �������������� � ��� long
	*out = strtol(tmp, &ptr, 10);
	//*out = (long)strtold(tmp, &ptr);
	//-- ���� ����� � ������ ����, �� ������
	if (strlen(ptr) > 0) return false;
	//-- ���� ��� ���������, �� ������
	if (errno == ERANGE) return false;
	return true;
}

void TInputLong::draw()
{
	int l, r;
	TDrawBuffer b;

	std::string str = std::to_string(minv) + ' ' + (char)0x1D + ' ' + std::to_string(maxv);
	char buff_diap[512];
	memset(buff_diap, 0x0, 512);
	str.copy(buff_diap, str.length());
	TColorAttr color = getColor((state & sfFocused) ? 2 : 1);

	long res = 0;
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

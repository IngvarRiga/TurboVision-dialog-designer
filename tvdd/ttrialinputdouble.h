#ifndef TTRIALINPUTDOUBLE_H
#define TTRIALINPUTDOUBLE_H
#define Uses_TInputLine
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#define Uses_TRect
#define Uses_TGroup
#include <tvision/tv.h>
#include "winputline.h"
#include "common.h"

class TTrialInputDouble : public TWrapInputLine
{
public:

	TTrialInputDouble(const TRect& bounds, uint aMaxLen, TValidator* aValid = 0);

	virtual ~TTrialInputDouble() {}


	virtual void setState(ushort aState, Boolean enable);
	virtual void sizeLimits(TPoint& min, TPoint& max);
	virtual void handleEvent(TEvent& event);

	void genCode(void* val);

	//-- получение значений
	char* getVarName();
	uint getVarLen();
	long double getMaxValue();
	long double getMinValue();
	long double getDefValue();
	int getPrecision();
	bool getAllowNotDefined();

	//-- установка значений
	void setVarName(const char* val);
	void setVarLen(uint val);
	void setMaxValue(long double val);
	void setMinValue(long double val);
	void setDefValue(long double val);
	void setPrecision(int val);
	void setAllowNotDefined(bool val);

	nlohmann::json genJSON();


private:
	char var_name[StringMaxLen]; //-- имя переменной для создания строки ввода
	long double minvalue; //-- минимально допустимое значение
	long double maxvalue; //-- максимально допустимое значение
	long double defvalue; //-- значение задаваемое по умолчанию
	int precision; //-- значение задаваемое по умолчанию
	bool AllowNotDefined; //-- допустимо незаданное значение (пустое)
};

#endif /* TTRIALINPUTLINE_H */


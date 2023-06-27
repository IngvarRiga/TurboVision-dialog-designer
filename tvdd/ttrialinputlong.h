#ifndef TTRIALINPUTLONG_H
#define TTRIALINPUTLONG_H
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

class TTrialInputLong : public TWrapInputLine
{
public:

	TTrialInputLong(const TRect& bounds, uint aMaxLen, TValidator* aValid = 0);

	virtual ~TTrialInputLong() {}

	virtual void setState(ushort aState, Boolean enable);
	virtual void sizeLimits(TPoint& min, TPoint& max);
	virtual void handleEvent(TEvent& event);

	void genCode(void* val);

	//-- получение значений
	char* getVarName();
	uint getVarLen();
	long getMaxValue();
	long getMinValue();
	long getDefValue();
	bool getAllowNotDefined();

	//-- установка значений
	void setVarName(const char* val);
	void setVarLen(uint val);
	void setMaxValue(long val);
	void setMinValue(long val);
	void setDefValue(long val);
	void setAllowNotDefined(bool val);

	nlohmann::json genJSON();

private:
	char var_name[StringMaxLen]; //-- имя переменной для создания строки ввода
	long minvalue; //-- минимально допустимое значение
	long maxvalue; //-- максимально допустимое значение
	long defvalue; //-- значение задаваемое по умолчанию
	bool AllowNotDefined; //-- допустимо незаданное значение (пустое)
};

#endif /* TTRIALINPUTLINE_H */


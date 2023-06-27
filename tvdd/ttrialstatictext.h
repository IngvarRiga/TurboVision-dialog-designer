#ifndef TTRIALSTATICTEXT_H
#define TTRIALSTATICTEXT_H

#define Uses_TStaticText
#define Uses_TEvent
#define Uses_TRect
#define Uses_TGroup
#define Uses_TText
#define Uses_TKeys
#include <tvision/tv.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "common.h"

#include "wstatictext.h"

class TTrialStaticText : public TWrapStaticText
{
public:
	TTrialStaticText(const TRect& bounds, TStringView aText);

	virtual ~TTrialStaticText()
	{}


	virtual void setState(ushort aState, Boolean enable);
	virtual void handleEvent(TEvent& event);
	virtual void sizeLimits(TPoint& min, TPoint& max);
	void genCode(void* val);

	//-- получение значений
	char* getVarName();
	bool getUsedVarName();

	//-- установка значений
	void setVarName(const char* val);
	void setUsedVarName(bool val);

	/// <summary>
	/// Генерирует JSON-код компонента
	/// </summary>
	/// <returns></returns>
	nlohmann::json genJSON();

protected:
	bool usedVarName; //-- при генерации исходного кода использовать отдельную переменную для объекта
	char var_name[StringMaxLen]; //-- имя переменной для создания текста

	std::vector<std::string> split(const std::string& s, char delim);

};


#endif /* TTRIALSTATICTEXT_H */


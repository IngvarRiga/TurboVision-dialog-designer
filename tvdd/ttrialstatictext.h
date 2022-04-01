#ifndef TTRIALSTATICTEXT_H
#define TTRIALSTATICTEXT_H

#define Uses_TStaticText
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#define Uses_TRect
#define Uses_TGroup
#define Uses_TText
#define Uses_TKeys
#include <tvision/tv.h>
#include <vector>
#include <sstream>
#include <iostream>

#include "wstatictext.h"

class TTrialStaticText : public TWrapStaticText
{
public:
	static const char* const name;
	TTrialStaticText(const TRect& bounds, TStringView aText);

	virtual ~TTrialStaticText()
	{}

	TTrialStaticText(StreamableInit) :
		TWrapStaticText(streamableInit)
	{}

	static TStreamable* build();

	virtual void setState(ushort aState, Boolean enable);
	virtual void handleEvent(TEvent& event);
	virtual void sizeLimits(TPoint& min, TPoint& max);
	void genCode(void* val);

	//-- получение значений
	char* getVarName();
	char* getClassName();
	bool getUsedVarName();

	//-- установка значений
	void setVarName(const char* val);
	void setClassName(const char* val);
	void setUsedVarName(bool val);

protected:
	bool usedVarName; //-- при генерации исходного кода использовать отдельную переменную для объекта
	char class_name[StringMaxLen]; //-- имя класса для создания текста
	char var_name[StringMaxLen]; //-- имя переменной для создания текста
	virtual void write(opstream&);
	virtual void* read(ipstream&);

	std::vector<std::string> split(const std::string& s, char delim);
private:
	virtual const char* streamableName() const
	{
		return name;
	}

};

inline ipstream& operator>>(ipstream& is, TTrialStaticText& cl)
{
	return is >> (TStreamable&)cl;
}

inline ipstream& operator>>(ipstream& is, TTrialStaticText*& cl)
{
	return is >> (void*&)cl;
}

inline opstream& operator<<(opstream& os, TTrialStaticText& cl)
{
	return os << (TStreamable&)cl;
}

inline opstream& operator<<(opstream& os, TTrialStaticText* cl)
{
	return os << (TStreamable*)cl;
}
#endif /* TTRIALSTATICTEXT_H */


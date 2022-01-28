#ifndef TTRIALLISTBOX_H
#define TTRIALLISTBOX_H

#define Uses_TView
#define Uses_TListBox
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_opstream
#define Uses_ipstream
#define Uses_ofpstream
#define Uses_TEvent
#define Uses_TKeys
#include <tvision/tv.h>


#include "common.h"
class TTrialListBox : public TListBox
{
public:
	static const char* const name;

	TTrialListBox(const TRect& bounds, ushort aNumCols, TScrollBar* aScrollBar);

	virtual ~TTrialListBox()
	{}

	TTrialListBox(StreamableInit) :
		TListBox(streamableInit)
	{}

	static TStreamable* build();

	virtual const char* streamableName() const
	{
		return name;
	}
	virtual void draw();
	virtual void setState(ushort aState, Boolean enable);
	virtual void handleEvent(TEvent& event);
	virtual void sizeLimits(TPoint& min, TPoint& max);
	bool isSelected();
	void setSelected(bool val);
	void genCode(void* val);

protected:
	char var_name[StringMaxLen]; //-- имя переменной для создания строки ввода
	char class_name[StringMaxLen]; //-- имя переменной для создания текста

	virtual void write(opstream&);
	virtual void* read(ipstream&);

private:
	bool Selected;

};

inline ipstream& operator>>(ipstream& is, TTrialListBox& cl)
{
	return is >> (TStreamable&)cl;
}

inline ipstream& operator>>(ipstream& is, TTrialListBox*& cl)
{
	return is >> (void*&)cl;
}

inline opstream& operator<<(opstream& os, TTrialListBox& cl)
{
	return os << (TStreamable&)cl;
}

inline opstream& operator<<(opstream& os, TTrialListBox* cl)
{
	return os << (TStreamable*)cl;
}

#endif /* TTRIALLISTBOX_H */


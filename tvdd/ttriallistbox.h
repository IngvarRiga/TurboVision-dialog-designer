#ifndef TTRIALLISTBOX_H
#define TTRIALLISTBOX_H

#define Uses_TView
#define Uses_TListBox
#define Uses_TEvent
#define Uses_TKeys
#include <tvision/tv.h>
#include "common.h"

class TTrialListBox : public TListBox
{
public:

	TTrialListBox(const TRect& bounds, ushort aNumCols, TScrollBar* aScrollBar);

	virtual ~TTrialListBox()
	{}

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

private:
	bool Selected;

};


#endif /* TTRIALLISTBOX_H */


#ifndef TTRIALDIALOGBACKGROUND_H
#define TTRIALDIALOGBACKGROUND_H

#define Uses_TView
#define Uses_TEvent

#include <tvision/tv.h>

class TTrialDialogBackground : public TView
{
public:
	TTrialDialogBackground(TRect& Bounds);

	virtual ~TTrialDialogBackground()
	{}

	virtual Boolean valid(ushort);

	virtual void draw();
	virtual void handleEvent(TEvent& event);

protected:
	TPoint currPos;

private:
	bool Patterned;
};


#endif /* TTRIALDIALOGBACKGROUND_H */


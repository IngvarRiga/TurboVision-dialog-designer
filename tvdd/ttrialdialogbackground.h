#ifndef TTRIALDIALOGBACKGROUND_H
#define TTRIALDIALOGBACKGROUND_H

#define Uses_TView
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream

#include <tvision/tv.h>

class TTrialDialogBackground : public TView
{
public:
	static const char* const name;

	TTrialDialogBackground(TRect& Bounds);

	virtual ~TTrialDialogBackground()
	{}

	TTrialDialogBackground(StreamableInit) :
		TView(streamableInit)
	{};
	virtual Boolean valid(ushort);
	static TStreamable* build();

	virtual const char* streamableName() const
	{
		return name;
	}
	virtual void draw();
	virtual void handleEvent(TEvent& event);

protected:
	TPoint currPos;
	virtual void write(opstream&);
	virtual void* read(ipstream&);

private:
	bool Patterned;
};

inline ipstream& operator>>(ipstream& is, TTrialDialogBackground& cl)
{
	return is >> (TStreamable&)cl;
}

inline ipstream& operator>>(ipstream& is, TTrialDialogBackground*& cl)
{
	return is >> (void*&)cl;
}

inline opstream& operator<<(opstream& os, TTrialDialogBackground& cl)
{
	return os << (TStreamable&)cl;
}

inline opstream& operator<<(opstream& os, TTrialDialogBackground* cl)
{
	return os << (TStreamable*)cl;
}

#endif /* TTRIALDIALOGBACKGROUND_H */


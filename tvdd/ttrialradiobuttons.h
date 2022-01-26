#ifndef TTRIALRADIOBUTTONS_H
#define TTRIALRADIOBUTTONS_H
#define Uses_TView
#define Uses_TSItem
#define Uses_TRadioButtons
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TEvent
#define Uses_TCluster
#define Uses_TStringCollection
#include <tvision/tv.h>
#include "wradiobuttons.h"

class TTrialRadioButtons : public TWrapRadioButtons
{
  public:
    static const char * const name;

    TTrialRadioButtons(const TRect& bounds, TSItem *aStrings);

    virtual ~TTrialRadioButtons()
    {
    }

    TTrialRadioButtons(StreamableInit) :
    TWrapRadioButtons(streamableInit)
    {
    }
    static TStreamable *build();

    virtual const char *streamableName() const
    {
        return name;
    }
    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void handleEvent(TEvent& event);

    virtual void setState(ushort aState, Boolean enable);
    void genCode(char *val);

  protected:

    virtual void write(opstream&);
    virtual void *read(ipstream&);

  private:
    bool Selected;

};

inline ipstream& operator>>(ipstream& is, TTrialRadioButtons& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TTrialRadioButtons*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TTrialRadioButtons& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TTrialRadioButtons* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TTRIALRADIOBUTTONS_H */

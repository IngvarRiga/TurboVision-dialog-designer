#ifndef TTRIALCHECKBOXES_H
#define TTRIALCHECKBOXES_H

#define Uses_TView
#define Uses_TSItem
#define Uses_TCheckBoxes
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TEvent
#include <tvision/tv.h>

class TTrialCheckBoxes : public TCheckBoxes
{
  public:
    static const char * const name;

    TTrialCheckBoxes(const TRect& bounds, TSItem *aStrings);

    virtual ~TTrialCheckBoxes()
    {
    }

    TTrialCheckBoxes(StreamableInit) :
    TCheckBoxes(streamableInit)
    {
    }
    static TStreamable *build();

    virtual const char *streamableName() const
    {
        return name;
    }
    virtual void sizeLimits(TPoint& min, TPoint& max);
    virtual void draw();
    virtual void handleEvent(TEvent& event);
    bool isSelected();
    void setSelected(bool val);
    void genCode(char *val);

  protected:

    virtual void write(opstream&);
    virtual void *read(ipstream&);

  private:
    bool Selected;
};

inline ipstream& operator>>(ipstream& is, TTrialCheckBoxes& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TTrialCheckBoxes*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TTrialCheckBoxes& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TTrialCheckBoxes* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TTRIALCHECKBOXES_H */


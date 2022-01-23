#ifndef TTRIALBUTTON_H
#define TTRIALBUTTON_H
#define Uses_TButton
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#define Uses_TRect
#define Uses_TGroup

#include <tvision/tv.h>

class TTrialButton : public TButton
{
  public:
    static const char * const name;

    TTrialButton(const TRect& bounds,
                 TStringView aTitle,
                 ushort aCommand = 0,
                 ushort aFlags = 0);

    virtual ~TTrialButton()
    {
    }

    TTrialButton(StreamableInit) :
    TButton(streamableInit)
    {
    }

    static TStreamable *build();

    virtual const char *streamableName() const
    {
        return name;
    }

    virtual void draw();
    virtual void handleEvent(TEvent& event);
    virtual void sizeLimits(TPoint& min, TPoint& max);
    bool isSelected();
    void setSelected(bool val);
    void genCode(char *val);

  protected:

    virtual void write(opstream&);
    virtual void *read(ipstream&);

  private:
    bool Selected;
};

inline ipstream& operator>>(ipstream& is, TTrialButton& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TTrialButton*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TTrialButton& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TTrialButton* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TTRIALBUTTON_H */


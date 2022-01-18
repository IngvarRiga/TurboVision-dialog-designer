#ifndef TTRIALLISTBOX_H
#define TTRIALLISTBOX_H

#define Uses_TView
#define Uses_TListBox
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TEvent
#include <tvision/tv.h>

class TTrialListBox : public TListBox
{
  public:
    static const char * const name;

    TTrialListBox(const TRect& bounds, ushort aNumCols, TScrollBar *aScrollBar);

    virtual ~TTrialListBox()
    {
    }

    TTrialListBox(StreamableInit) :
    TListBox(streamableInit)
    {
    }

    static TStreamable *build();

    virtual const char *streamableName() const
    {
        return name;
    }
    virtual void draw();
    virtual void setState(ushort aState, Boolean enable);
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

inline ipstream& operator>>(ipstream& is, TTrialListBox& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TTrialListBox*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TTrialListBox& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TTrialListBox* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TTRIALLISTBOX_H */


#ifndef TWINEXTMENU_H
#define TWINEXTMENU_H

#define Uses_TView
#define Uses_TMenuView
#define Uses_TSubMenu
#define Uses_TMenuBox
#define Uses_TMenu
#define Uses_TStreamable
#define Uses_TStreamableClass
#include <tvision/tv.h>


class TWinExtMenu : public TView
{
  public:
    static const char * const name;

    TWinExtMenu(const TRect& rect);
    virtual ~TWinExtMenu() {}

    TWinExtMenu(StreamableInit) :
    TView(streamableInit)
    {
    }

    virtual void handleEvent(TEvent& event);
    static TStreamable *build();
    virtual void draw();

  private:
    virtual const char *streamableName() const
    {
        return name;
    }

  protected:
    virtual void write(opstream&);
    virtual void *read(ipstream&);

};

inline ipstream& operator>>(ipstream& is, TWinExtMenu& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TWinExtMenu*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TWinExtMenu& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TWinExtMenu* cl)
{
    return os << (TStreamable *) cl;
}


#endif /* TWINEXTMENU_H */


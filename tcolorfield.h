#ifndef TCOLORFIELD_H
#define TCOLORFIELD_H
#define Uses_TView
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#define Uses_TRect
#define Uses_TGroup
#include <tvision/tv.h>


class TColorField : public TView
{
  public:
    TColorField(int delta = 0, int deltay = 0);

    virtual ~TColorField()
    {
    }

    TColorField(StreamableInit) :
    TView(streamableInit)
    {
    }

    static TStreamable *build();

    virtual const char *streamableName() const
    {
        return "TColorField";
    }

    virtual void draw();
    virtual void handleEvent(TEvent& event);
    
    void setDrawChar(const char val);
    char getDrawChar() {return DrawChar;}
    ushort getColor() {return selectedColor;}
  protected:
    char DrawChar; //-- отображаемый символ
    ushort selectedColor; //-- выбранный цвет
    virtual void write(opstream&);
    virtual void *read(ipstream&);

};

inline ipstream& operator>>(ipstream& is, TColorField& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TColorField*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TColorField& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TColorField* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TCOLORFIELD_H */


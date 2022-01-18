#ifndef TWINSIZEINDICATOR_H
#define TWINSIZEINDICATOR_H

#define Uses_TIndicator
#define Uses_TStreamable
#define Uses_TStreamableClass
#include <tvision/tv.h>
#include "common.h"
/// Компонент отображает истинный размер окна (без тени)

class TWinSizeIndicator : public TIndicator
{
  public:
    static const char * const name;

    TWinSizeIndicator(const TRect& rect);
    virtual ~TWinSizeIndicator();

    TWinSizeIndicator(StreamableInit) :
    TIndicator(streamableInit)
    {
    };
    static TStreamable *build();

    //-- отображать позицию левого верхнего угла
    void setPosInfo(bool val = true);
    //-- отображать размеры
    void setSizeInfo(bool val = true);
    virtual void handleEvent(TEvent& event);
    virtual void draw();
    bool getPosInfo();
    bool getSizeInfo();
    virtual const char *streamableName() const
    {
        return name;
    }
  private:
    bool posInfo;
    bool sizeInfo;
    char drawtext[StringMaxLen];
    char sh[StringMaxLen];
    char sw[StringMaxLen];
    char px[StringMaxLen];
    char py[StringMaxLen];
  protected:

    virtual void write(opstream&);
    virtual void *read(ipstream&);
};
inline ipstream& operator>>(ipstream& is, TWinSizeIndicator& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TWinSizeIndicator*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TWinSizeIndicator& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TWinSizeIndicator* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TCUSTOMINDICATOR_H */


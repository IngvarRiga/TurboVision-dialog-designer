#ifndef TWINSIZEINDICATOR_H
#define TWINSIZEINDICATOR_H

#define Uses_TIndicator
#include <tvision/tv.h>
#include "common.h"
/// Компонент отображает истинный размер окна (без тени)

class TWinSizeIndicator : public TIndicator
{
  public:

    TWinSizeIndicator(const TRect& rect);
    virtual ~TWinSizeIndicator();

    //-- отображать позицию левого верхнего угла
    void setPosInfo(bool val = true);
    //-- отображать размеры
    void setSizeInfo(bool val = true);
    virtual void handleEvent(TEvent& event);
    virtual void draw();
    bool getPosInfo();
    bool getSizeInfo();

private:
    bool posInfo;
    bool sizeInfo;
    char drawtext[StringMaxLen];
    char sh[StringMaxLen];
    char sw[StringMaxLen];
    char px[StringMaxLen];
    char py[StringMaxLen];

};

#endif /* TCUSTOMINDICATOR_H */


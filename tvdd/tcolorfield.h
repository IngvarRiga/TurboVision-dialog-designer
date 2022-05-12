#ifndef TCOLORFIELD_H
#define TCOLORFIELD_H
#define Uses_TView
#define Uses_TEvent
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

    virtual void draw();
    virtual void handleEvent(TEvent& event);
    
    void setDrawChar(const char val);
    char getDrawChar() {return DrawChar;}
    ushort getColor() {return selectedColor;}
  protected:
    char DrawChar; //-- отображаемый символ
    ushort selectedColor; //-- выбранный цвет
};

#endif /* TCOLORFIELD_H */


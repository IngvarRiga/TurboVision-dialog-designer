#ifndef TCUSTOMWINDOW_H
#define TCUSTOMWINDOW_H

#define Uses_TDialog
#define Uses_TEvent
#define Uses_TWindow
#define Uses_TView
#define Uses_TScrollBar
#define Uses_TScroller

#include <tvision/tv.h>
#include <cstdlib>
#include <string>
#include <vector>

class TInterior;


class TCustomWindow : public TWindow
{
private:
    TInterior *intr;

public:
    TCustomWindow(const int width, const int height, const char* aTitle, short aNumber=-1);

};

/// <summary>
///  ласс определ€ющий внутреннее содержимое окна
/// </summary>
class TInterior : public TScroller
{
private:
    std::vector<std::string> text;
    int maxLineLength;
public:
    TInterior(const TRect& bounds, TScrollBar* aHScrollBar, TScrollBar* aVScrollBar);
    virtual void draw();             
};

#endif
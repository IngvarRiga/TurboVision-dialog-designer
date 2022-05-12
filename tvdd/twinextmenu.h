#ifndef TWINEXTMENU_H
#define TWINEXTMENU_H

#define Uses_TView
#define Uses_TMenuView
#define Uses_TSubMenu
#define Uses_TMenuBox
#define Uses_TMenu
#include <tvision/tv.h>


class TWinExtMenu : public TView
{
  public:
    TWinExtMenu(const TRect& rect);
    virtual ~TWinExtMenu() {}
    virtual void handleEvent(TEvent& event);
    virtual void draw();
};

#endif /* TWINEXTMENU_H */


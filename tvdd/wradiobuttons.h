#ifndef WRADIOBUTTONS_H
#define WRADIOBUTTONS_H

#define Uses_TView
#define Uses_TEvent
#define Uses_TPalette
#define Uses_TDrawBuffer
#define Uses_TText
#define Uses_TSItem
#define Uses_TRect
#include "include/tvision/tv.h"
#include "wcluster.h"
#include <concepts>
 /* ---------------------------------------------------------------------- */
 /*      class TRadioButtons                                               */
 /*                                                                        */
 /*      Palette layout                                                    */
 /*        1 = Normal text                                                 */
 /*        2 = Selected text                                               */
 /*        3 = Normal shortcut                                             */
 /*        4 = Selected shortcut                                           */
 /* ---------------------------------------------------------------------- */



class TWrapRadioButtons : public TWrapCluster
{

public:

    TWrapRadioButtons(const TRect& bounds, TSItem* aStrings, bool click = false) noexcept;

    virtual void draw();
    virtual Boolean mark(int item);
    virtual void movedTo(int item);
    virtual void press(int item);
    virtual void setData(void* rec);

    //----------------------------------------------------------------
    virtual void handleEvent(TEvent& event);

private:

    static const char* _NEAR button;

};

inline TWrapRadioButtons::TWrapRadioButtons(const TRect& bounds, TSItem* aStrings, bool click) noexcept :
    TWrapCluster(bounds, aStrings, click)
{
}


#endif /* WRADIOBUTTONS_H */


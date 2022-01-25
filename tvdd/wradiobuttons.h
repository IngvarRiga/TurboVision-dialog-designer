#ifndef WRADIOBUTTONS_H
#define WRADIOBUTTONS_H

#define Uses_TView
#define Uses_TEvent
#define Uses_TPalette
#define Uses_TDrawBuffer
#define Uses_opstream
#define Uses_ipstream
#define Uses_TText
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TSItem
#include <tvision/tv.h>
#include "wcluster.h"
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
    virtual const char* streamableName() const
    {
        return name;
    }

protected:

    TWrapRadioButtons(StreamableInit) noexcept;

public:

    static const char* const _NEAR name;
    static TStreamable* build();

};

inline ipstream& operator >> (ipstream& is, TWrapRadioButtons& cl)
{
    return is >> (TStreamable&)cl;
}
inline ipstream& operator >> (ipstream& is, TWrapRadioButtons*& cl)
{
    return is >> (void*&)cl;
}

inline opstream& operator << (opstream& os, TWrapRadioButtons& cl)
{
    return os << (TStreamable&)cl;
}
inline opstream& operator << (opstream& os, TWrapRadioButtons* cl)
{
    return os << (TStreamable*)cl;
}

inline TWrapRadioButtons::TWrapRadioButtons(const TRect& bounds, TSItem* aStrings, bool click) noexcept :
    TWrapCluster(bounds, aStrings, click)
{
    int h = 0;
}


#endif /* WRADIOBUTTONS_H */


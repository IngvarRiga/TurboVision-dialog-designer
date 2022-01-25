#ifndef WCHECKBOXES_H
#define WCHECKBOXES_H

/* ---------------------------------------------------------------------- */
/*      TCheckBoxes                                                       */
/*                                                                        */
/*      Palette layout                                                    */
/*        1 = Normal text                                                 */
/*        2 = Selected text                                               */
/*        3 = Normal shortcut                                             */
/*        4 = Selected shortcut                                           */
/* ---------------------------------------------------------------------- */
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

class TWrapCheckBoxes : public TWrapCluster
{

public:

    TWrapCheckBoxes(const TRect& bounds, TSItem* aStrings, bool click=false) noexcept;

    virtual void draw();

    virtual Boolean mark(int item);
    virtual void press(int item);
    //----------------------------------------------------------------
    virtual void handleEvent(TEvent& event);

private:

    static const char* _NEAR button;

    virtual const char* streamableName() const
    {
        return name;
    }

protected:

    TWrapCheckBoxes(StreamableInit) noexcept;

public:

    static const char* const _NEAR name;
    static TStreamable* build();

};

inline ipstream& operator >> (ipstream& is, TWrapCheckBoxes& cl)
{
    return is >> (TStreamable&)cl;
}
inline ipstream& operator >> (ipstream& is, TWrapCheckBoxes*& cl)
{
    return is >> (void*&)cl;
}

inline opstream& operator << (opstream& os, TWrapCheckBoxes& cl)
{
    return os << (TStreamable&)cl;
}
inline opstream& operator << (opstream& os, TWrapCheckBoxes* cl)
{
    return os << (TStreamable*)cl;
}

inline TWrapCheckBoxes::TWrapCheckBoxes(const TRect& bounds, TSItem* aStrings, bool click) noexcept :
    TWrapCluster(bounds, aStrings, click)
{}

#endif /* WCHECKBOXES_H */


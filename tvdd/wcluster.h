#ifndef TWRAPCLUSTER_H
#define TWRAPCLUSTER_H

//      class Wrapped StaticText
//      Palette layout 1 = Text 
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
#define Uses_TStringCollection

#include <tvision/tv.h>
#include "../common.h"

class TWrapCluster : public TView
{

public:

    TWrapCluster(const TRect& bounds, TSItem* aStrings, bool click = false) noexcept;
    ~TWrapCluster();

    virtual ushort dataSize();
    void drawBox(const char* icon, char marker);
    void drawMultiBox(const char* icon, const char* marker);
    virtual void getData(void* rec);
    ushort getHelpCtx();
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent& event);
    virtual Boolean mark(int item);
    virtual uchar multiMark(int item);
    void recreateItems(TSItem* aStrings);

    virtual void press(int item);
    virtual void movedTo(int item);
    virtual void setData(void* rec);
    virtual void setState(ushort aState, Boolean enable);
    virtual void setButtonState(uint32_t aMask, Boolean enable);
    //-----------------------------------------------------------
    virtual TAttrPair getColor(ushort color);
    bool isSelected() { return Selected; }
    void setSelected(bool val);

    void setDragged()
    {
        eventDragged = true;
    };

    TStringCollection* getItems() { return strings; }
protected:

    uint32_t value;
    uint32_t enableMask;
    int sel;
    TStringCollection* strings;

private:

    int column(int item);
    int findSel(TPoint p);
    int row(int item);
    void moveSel(int, int);

    virtual const char* streamableName() const
    {
        return name;
    }

protected:
    bool Selected; //-- компонент выбран пользователем
    bool eventClick; //-- специфическая реакция на клик по компоненту (только для дизайнера)
    bool eventDragged; //-- компонент находится в режиме перемещения (только для дизайнера)

    TWrapCluster(StreamableInit) noexcept;
    virtual void write(opstream&);
    virtual void* read(ipstream&);

public:
    Boolean buttonState(int);

    static const char* const _NEAR name;
    static TStreamable* build();

};

inline ipstream& operator >> (ipstream& is, TWrapCluster& cl)
{
    return is >> (TStreamable&)cl;
}
inline ipstream& operator >> (ipstream& is, TWrapCluster*& cl)
{
    return is >> (void*&)cl;
}

inline opstream& operator << (opstream& os, TWrapCluster& cl)
{
    return os << (TStreamable&)cl;
}
inline opstream& operator << (opstream& os, TWrapCluster* cl)
{
    return os << (TStreamable*)cl;
}


#endif
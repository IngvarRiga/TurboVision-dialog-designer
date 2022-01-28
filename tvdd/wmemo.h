#ifndef WMEMO_H
#define WMEMO_H
/*#define Uses_TKeys
#define Uses_TEditor
#define Uses_TMemo
#define Uses_TEvent
#define Uses_opstream
#define Uses_ipstream
#define Uses_ofpstream
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TDrawBuffer
//#define Uses_TScrollBar
//#define Uses_TEditor
//#define Uses_TMemo
#include <tvision/tv.h>

class TWrapMemo : public TEditor
{

public:
    static const char* const _NEAR name;
    TWrapMemo(const TRect&, TScrollBar*, TScrollBar*, TIndicator*, ushort , bool click = false) noexcept;
    virtual void getData(void* rec);
    virtual void setData(void* rec);
    virtual ushort dataSize();
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent&);
    static TStreamable* build();

    //-- переопределяем идиотский функционал получение аццкой палитры
    //virtual TAttrPair getColor(ushort color);
    bool isSelected();
    void setSelected(bool val);

private:

    virtual const char* streamableName() const
    {
        return name;
    }

protected:
    bool Selected; //-- компонент выбран пользователем
    bool eventClick; //-- специфическая реакция на клик по компоненту (только для дизайнера)
    bool eventDragged; //-- компонент находится в режиме перемещения (только для дизайнера)

    TWrapMemo(StreamableInit) noexcept;
    virtual void write(opstream&);
    virtual void* read(ipstream&);
};

inline ipstream& operator >> (ipstream& is, TWrapMemo& cl)
{
    return is >> (TStreamable&)cl;
}
inline ipstream& operator >> (ipstream& is, TWrapMemo*& cl)
{
    return is >> (void*&)cl;
}

inline opstream& operator << (opstream& os, TWrapMemo& cl)
{
    return os << (TStreamable&)cl;
}
inline opstream& operator << (opstream& os, TWrapMemo* cl)
{
    return os << (TStreamable*)cl;
}
*/

#endif /* WMEMO_H */


#ifndef WMEMO_H
#define WMEMO_H
#define Uses_TKeys
#define Uses_TEditor
#define Uses_TMemo
#define Uses_TEvent
#define Uses_TDrawBuffer
//#define Uses_TScrollBar
//#define Uses_TEditor
//#define Uses_TMemo
#include <tvision/tv.h>

class TWrapMemo : public TEditor
{

public:
    TWrapMemo(const TRect&, TScrollBar*, TScrollBar*, TIndicator*, ushort , bool click = false) noexcept;
    ~TWrapMemo()
        ;
    virtual void getData(void* rec);
    virtual void setData(void* rec);
    virtual ushort dataSize();
    virtual void draw();
    virtual void drawLines(int y, int count, uint linePtr);

    void setDragged()
    {
        eventDragged = true;
    };

    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent&);
    TAttrPair getColor(ushort color);


    //-- переопределяем идиотский функционал получение аццкой палитры
    //virtual TAttrPair getColor(ushort color);
    bool isSelected();
    void setSelected(bool val);


protected:
    bool Selected; //-- компонент выбран пользователем
    bool eventClick; //-- специфическая реакция на клик по компоненту (только для дизайнера)
    bool eventDragged; //-- компонент находится в режиме перемещения (только для дизайнера)

};

#endif /* WMEMO_H */


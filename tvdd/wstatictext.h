#ifndef TWRAPSTATICTEXT_H
#define TWRAPSTATICTEXT_H

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

#include <tvision/tv.h>
#include "../common.h"

/* Переопределение */


class TWrapStaticText : public TView
{
  public:
    static const char * const name;
    static TStreamable *build();

    TWrapStaticText(const TRect& bounds, TStringView aText) noexcept;
    TWrapStaticText(const TRect& bounds, TStringView aText, bool click) noexcept;

    ~TWrapStaticText()
    {
    };

    virtual void draw();
    virtual TPalette& getPalette() const;
    //-- Установка и чтение свойств...
    //-- отображаемый текст
    virtual void setCaption(char *val);
    virtual char* getCaption();
    virtual void handleEvent(TEvent& event);
    virtual TAttrPair getColor( ushort color );

    //-- ... используемый при обычной отрисовке текст
    virtual void setWColor(ushort val);
    virtual ushort getWColor();

    bool isSelected();
    void setSelected(bool val);

    //-- ... данная функция оставлена для совместимости библиотек с TStaticText
    virtual void getText(char *);

    void setDragged()
    {
        eventDragged = true;
    };
  protected:
    char text[StringMaxLen];
    bool Selected; //-- компонент выбран пользователем
    bool eventClick; //-- специфическая реакция на клик по компоненту (только для дизайнера)
    bool eventDragged; //-- компонент находится в режиме перемещения (только для дизайнера)

    TWrapStaticText(StreamableInit) noexcept;
    virtual void write(opstream&);
    virtual void *read(ipstream&);

  private:

    virtual const char *streamableName() const
    {
        return name;
    }
};

inline ipstream& operator>>(ipstream& is, TWrapStaticText& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TWrapStaticText*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TWrapStaticText& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TWrapStaticText* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TTRIALSTATICTEXT_H */

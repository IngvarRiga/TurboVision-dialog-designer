#ifndef TWRAPSTATICTEXT_H
#define TWRAPSTATICTEXT_H

//      class Wrapped StaticText
//      Palette layout 1 = Text 
#define Uses_TView
#define Uses_TEvent
#define Uses_TPalette
#define Uses_TDrawBuffer
#define Uses_TText

#include <tvision/tv.h>
#include "common.h"

/* Переопределение */


class TWrapStaticText : public TView
{
  public:

    TWrapStaticText(const TRect& bounds, TStringView aText, bool click = false) noexcept;

    ~TWrapStaticText()
    {
    };

    virtual void draw();
    virtual TPalette& getPalette() const;
    //-- Установка и чтение свойств...
    //-- отображаемый текст
    virtual void setCaption(const char *val);
    /// <summary>
    /// Получить отображаемый текст
    /// </summary>
    /// <returns>Отображаемый текст</returns>
    virtual char* getCaption();
    virtual void handleEvent(TEvent& event);
    virtual TAttrPair getColor( ushort color );


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

};


#endif /* TTRIALSTATICTEXT_H */

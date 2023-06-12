#ifndef WBUTTON_H
#define WBUTTON_H

/*      TButton object                                                    */
/*                                                                        */
/*      Palette layout                                                    */
/*        1 = Normal text                                                 */
/*        2 = Default text                                                */
/*        3 = Selected text                                               */
/*        4 = Disabled text                                               */
/*        5 = Normal shortcut                                             */
/*        6 = Default shortcut                                            */
/*        7 = Selected shortcut                                           */
/*        8 = Shadow                                                      */
/* ---------------------------------------------------------------------- */
#define Uses_TGroup
#define Uses_TKeys
#define Uses_TInputLine
#define Uses_TDrawBuffer
#define Uses_TEvent
#define Uses_TValidator
#define Uses_TText
#include <tvision/tv.h>
#include "common.h"

class TWrapButton : public TView
{

public:
    TWrapButton(const TRect& bounds,
            TStringView aTitle,
            ushort aCommand,
            ushort aFlags,
                bool click = false
    ) noexcept;
    ~TWrapButton() {}

    virtual void draw();
    void drawState(Boolean down);
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent& event);
    void makeDefault(Boolean enable);
    virtual void press();
    virtual void setState(ushort aState, Boolean enable);

    /// <summary>
    /// Переопределяем идиотский функционал получения аццкой палитры
    /// </summary>
    /// <param name="color"></param>
    /// <returns></returns>
    virtual TAttrPair getColor(ushort color);

    bool isSelected();
    void setSelected(bool val);

    void setCaption(char* val);
    /// <summary>
    /// Получить текст, отображаемый на кнопке
    /// </summary>
    /// <returns></returns>
    char* getCaption();

    void setDragged()
    {
        eventDragged = true;
    };

    char title[StringMaxLen];

protected:
    bool Selected; //-- компонент выбран пользователем
    bool eventClick; //-- специфическая реакция на клик по компоненту (только для дизайнера)
    bool eventDragged; //-- компонент находится в режиме перемещения (только для дизайнера)

    ushort command;
    uchar flags;
    Boolean amDefault;

private:

    void drawTitle(TDrawBuffer&, int, int, TAttrPair, Boolean);
    void pressButton(TEvent&);
    TRect getActiveRect();

    static const char* _NEAR shadows;
    static const char* _NEAR markers;

};




#endif /* WBUTTON_H */


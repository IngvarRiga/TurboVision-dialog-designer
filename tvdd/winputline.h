#ifndef WINPUTLINE_H
#define WINPUTLINE_H

/* ---------------------------------------------------------------------- */
/*      class TInputLine                                                  */
/*                                                                        */
/*      Palette layout                                                    */
/*        1 = Passive                                                     */
/*        2 = Active                                                      */
/*        3 = Selected                                                    */
/*        4 = Arrows                                                      */
/* ---------------------------------------------------------------------- */
#define Uses_TGroup
#define Uses_TKeys
#define Uses_TInputLine
#define Uses_TDrawBuffer
#define Uses_TEvent
#define Uses_TValidator
#define Uses_TText
#include <tvision/tv.h>


class TWrapInputLine : public TView
{
  public:

    TWrapInputLine(const TRect& bounds, uint aMaxLen, TValidator *aValid = 0, bool click = false) noexcept;
    ~TWrapInputLine();

    virtual ushort dataSize();
    virtual void draw();
    virtual void getData(void *rec);
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent& event);
    void selectAll(Boolean enable, Boolean scroll = True);
    virtual void setData(void *rec);
    virtual void setState(ushort aState, Boolean enable);
    virtual Boolean valid(ushort cmd);
    void setValidator(TValidator* aValid);


    //-- переопределяем идиотский функционал получение аццкой палитры
    virtual TAttrPair getColor( ushort color );
    
    bool isSelected();
    void setSelected(bool val);
    

    void setDragged()
    {
        eventDragged = true;
    };

    char* data;
    uint maxLen;
    int curPos;
    int firstPos;
    int selStart;
    int selEnd;

  private:

    Boolean canScroll(int delta);
    int mouseDelta(TEvent& event);
    int mousePos(TEvent& event);
    int displayedPos(int pos);
    void deleteSelect();
    void deleteCurrent();
    void adjustSelectBlock();
    void saveState();
    void restoreState();
    Boolean checkValid(Boolean);

    static const char rightArrow;
    static const char leftArrow;

    TValidator* validator;

    int anchor;
    char* oldData;
    int oldCurPos;
    int oldFirstPos;
    int oldSelStart;
    int oldSelEnd;

  protected:
    bool Selected; //-- компонент выбран пользователем
    bool eventClick; //-- специфическая реакция на клик по компоненту (только для дизайнера)
    bool eventDragged; //-- компонент находится в режиме перемещения (только для дизайнера)
};

#endif /* WINPUTLINE_H */


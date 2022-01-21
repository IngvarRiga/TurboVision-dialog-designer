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
#define Uses_opstream
#define Uses_ipstream
#define Uses_TText
#define Uses_TStreamable
#define Uses_TStreamableClass
#include <tvision/tv.h>


class TWrapInputLine : public TView
{
  public:
    static const char * const name;

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
    
    void setEditValue(char* val);
    char* GetEditValue();
    
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

    virtual const char *streamableName() const
    {
        return name;
    }

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

    TWrapInputLine(StreamableInit) noexcept;
    virtual void write(opstream&);
    virtual void *read(ipstream&);

  public:
    static TStreamable *build();

};

inline ipstream& operator>>(ipstream& is, TWrapInputLine& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TWrapInputLine*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TWrapInputLine& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TWrapInputLine* cl)
{
    return os << (TStreamable *) cl;
}


#endif /* WINPUTLINE_H */

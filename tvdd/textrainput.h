
#ifndef TEXTRAINPUT				
#define TEXTRAINPUT

#define Uses_TEvent
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TRect
#define Uses_MsgBox
#include <tvision/tv.h>
#include <math.h>
#include "multilang.h"


//-- определение класса TInputLong
class TInputLong : public TInputLine
{
private:
    /// <summary>
    /// Редактируемое значение
    /// </summary>
    long value;
    /// <summary>
    /// Допустимый диапазон изменений значения
    /// </summary>
    long minv, maxv;
    /// <summary>
    /// 
    /// </summary>
    /// <param name="tmp"></param>
    /// <param name="out"></param>
    /// <returns></returns>
    bool convertl(const char* tmp, long* out);
    /// <summary>
    /// Отобразить ошибку ввода
    /// </summary>
    void ShowError();

public:

    TInputLong(const TRect& bounds, long MinValue = LONG_MIN, long MaxValue = LONG_MAX, long DefValue = 0);
    ~TInputLong() {};

    virtual void handleEvent(TEvent& event);
    /// <summary>
    /// Нормализованное получение данных 
    /// </summary>
    /// <returns></returns>
    long getValue() { return value; }
    /// <summary>
    /// Нормализованная установка данных
    /// </summary>
    /// <param name="val"></param>
    void setValue(long val);
    /// <summary>
    /// Проверка попадания в диапазон допустимых значений
    /// </summary>
    /// <param name="val"> - проверяемое значение</param>
    /// <returns></returns>
    bool CheckValue(long val);

    virtual void setState(ushort aState, Boolean enable);
};

/* ---------------------------------------------------------------------- */
/*      class TExtInputLine                                                  */
/*                                                                        */
/*      Palette layout                                                    */
/*        1 = Passive                                                     */
/*        2 = Active                                                      */
/*        3 = Selected                                                    */
/*        4 = Arrows                                                      */
/* ---------------------------------------------------------------------- */


//const ushort
//ilMaxBytes = 0,
//ilMaxWidth = 1,
//ilMaxGraphemes = 2;

//class _FAR TRect;
//struct _FAR TEvent;
//class _FAR TValidator;

/// <summary>
/// Переделка базового класса TInputLine. Потоковая загрузка удалена как устаревшая
/// </summary>
class TExtInputLine : public TView
{

public:

    TExtInputLine(const TRect& bounds, uint limit, TValidator* aValid = nullptr, ushort limitMode = ilMaxBytes) noexcept;
    ~TExtInputLine();

    virtual ushort dataSize();
    virtual void draw();
    virtual void getData(void* rec);
    virtual TPalette& getPalette() const;
    virtual void handleEvent(TEvent& event);
    void selectAll(Boolean enable, Boolean scroll = True);
    virtual void setData(void* rec);
    virtual void setState(ushort aState, Boolean enable);
    virtual Boolean valid(ushort cmd);
    void setValidator(TValidator* aValid);

    char* data;
    uint maxLen;
    uint maxWidth;
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

    static const char rightArrow = '\x10';
    static const char leftArrow = '\x11';

    TValidator* validator;

    int anchor;
    char* oldData;
    int oldCurPos;
    int oldFirstPos;
    int oldSelStart;
    int oldSelEnd;
};


#endif


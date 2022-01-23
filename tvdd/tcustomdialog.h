
#ifndef TCUSTOMDIALOG_H
#define TCUSTOMDIALOG_H

#define Uses_TDialog
#define Uses_TEvent
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream

#include <tvision/tv.h>
#include <cstdlib>

//-- Формируем наследника диалогового окна с заранее заданными свойствами

class TCustomDialog : public TDialog
{
  public:
    static const char * const name;

    //-- стандартный конструктор TurboVision. Но имеет как мне кажется недостаток в том
    //-- что координаты задаются прямоугольником с абсолютными координатами
    TCustomDialog(const TRect& bounds, TStringView aTitle,
                  bool sizable = false, //-- возможность изменения размеров
                  bool centered = true, //-- диалог центрирован по умолчанию при отображении
                  bool restrictSize = true //-- при возможности изменения размера установить ограничение на минимум заданный в констроукторе
                  );
    //-- Дополнительный конструктор, в котором задаём только высоту и ширину диалога
    //-- а он самостоятельно центрируется на экране
    //-- Высота - это по Y / ширина - по X
    TCustomDialog(const int width, const int height, TStringView aTitle,
                  bool sizeable = false, //-- возможность изменения размеров
                  bool restrictSize = true //-- при возможности изменения размера установить ограничение на минимум заданный в констроукторе
                  );

    TCustomDialog(StreamableInit) :
    TDialog(streamableInit),
    TWindowInit(TCustomDialog::initFrame)
    {
    }

    ~TCustomDialog()
    {
    }
    virtual bool valid(ushort);
    static TStreamable *build();
    virtual const char *streamableName() const
    {
        return name;
    }

    virtual void setData(void *val);
    virtual void getData(void *val);
    virtual void handleEvent(TEvent& event);

  private:
    bool     frestrictSize;


  protected:
    virtual void write(opstream&);
    virtual void *read(ipstream&);

};

inline ipstream& operator>>(ipstream& is, TCustomDialog& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TCustomDialog*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TCustomDialog& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TCustomDialog* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TCUSTOMDIALOG_H */


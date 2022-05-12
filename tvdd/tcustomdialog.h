
#ifndef TCUSTOMDIALOG_H
#define TCUSTOMDIALOG_H

#define Uses_TDialog
#define Uses_TEvent

#include <tvision/tv.h>
#include <cstdlib>

//-- Формируем наследника диалогового окна с заранее заданными свойствами

class TCustomDialog : public TDialog
{
  public:

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

    ~TCustomDialog()
    {
    }
    virtual bool valid(ushort);

    virtual void setData(void *val);
    virtual void getData(void *val);
    virtual void handleEvent(TEvent& event);

  private:
    bool     frestrictSize;
};


#endif /* TCUSTOMDIALOG_H */


#ifndef TRIALDIALOG_H
#define TRIALDIALOG_H

#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TEvent
#define Uses_TFileDialog
#include <tvision/tv.h>

#include "tcustomdialog.h"
#include "ttrialdialogbackground.h"
#include "twinsizeindicator.h"
#include "twinextmenu.h"

class TTrialDialog : public TCustomDialog
{
  public:
    static const char * const name;
    
    //-- используем упрощенную форму задания размера диалога
    TTrialDialog(const int width, const int height, TStringView aTitle, bool sizeable = true);

    TTrialDialog(StreamableInit) :
    TCustomDialog(streamableInit),
    TWindowInit(TTrialDialog::initFrame)
    {
    };

    virtual ~TTrialDialog();
    virtual bool valid( ushort );
    static TStreamable *build();
    virtual void close();
    virtual void handleEvent(TEvent& event);
    virtual void setState(ushort aState, bool enable);
    virtual const char *streamableName() const
    {
        return name;
    }

    void editDialogProperties();
    void saveDialogToRes();
    void saveDialogToSrc();

  private:
    bool DialSaved; //-- признак сохраненности диалога
    char class_name[StringMaxLen]; //-- название класса диалога
    char base_class_name[StringMaxLen]; //-- название базового класса диалога
    TTrialDialogBackground *Background; //-- хрень отвечающая за отрисовку подложки диалога в режиме конструктора
    bool Centered; //-- диалог должен быть отцентрирован
    //bool GenDefaults;
    TWinSizeIndicator *ind; //-- индикатор размеров окна
    TWinExtMenu * emnu; //-- дополнительное управляющее меню
    //    

    virtual void GenCode(ofstream *res); //-- генерация кода диалога

  protected:

    virtual void write(opstream&);
    virtual void *read(ipstream&);
};

inline ipstream& operator>>(ipstream& is, TTrialDialog& cl)
{
    return is >> (TStreamable&) cl;
}

inline ipstream& operator>>(ipstream& is, TTrialDialog*& cl)
{
    return is >> (void *&) cl;
}

inline opstream& operator<<(opstream& os, TTrialDialog& cl)
{
    return os << (TStreamable&) cl;
}

inline opstream& operator<<(opstream& os, TTrialDialog* cl)
{
    return os << (TStreamable *) cl;
}

#endif /* TRIALDIALOG_H */


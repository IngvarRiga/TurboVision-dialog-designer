#ifndef TCOMPONENTDIALOG_H
#define TCOMPONENTDIALOG_H

#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TInputLine
#define Uses_TRadioButtons
#define Uses_TCheckBoxes
#define Uses_TScrollBar
#define Uses_TSItem
#define Uses_TSortedListBox
#define Uses_TMemo
#include <tvision/tv.h>

#include "tcustomdialog.h"
#include "wstatictext.h"
#include "winputline.h"
#include "wbutton.h"


class TComponentDialog : public TCustomDialog
{
  public:
    TComponentDialog();
    virtual ~TComponentDialog(){}
    virtual void handleEvent(TEvent& event);

  private:

};

#endif /* TCOMPONENTDIALOG_H */


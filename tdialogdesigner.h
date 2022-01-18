#ifndef TDIALOGDESIGNER_H
#define TDIALOGDESIGNER_H
#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_TInputLine
#define Uses_TCheckBoxes
#define Uses_TRadioButtons
#define Uses_TSItem
#define Uses_TSortedListBox
#define Uses_TScrollBar

#include <tvision/tv.h>
#include "tcustomdialog.h"
class TDialogDesigner : TWindow
{
  public:
    TDialogDesigner (const TRect& bounds, TStringView aTitle, short Number = wnNoNumber);
    virtual ~TDialogDesigner(){}
  private:
    TCustomDialog* ConstructDialog();

};

#endif /* TDIALOGDESIGNER_H */



#ifndef TPRG_H
#define TPRG_H

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
#define Uses_ifpstream
#define Uses_TFileDialog

#include <tvision/tv.h>
#include "trialdialog.h"
#include "tcustomdialog.h"
#include "tselectcolordialog.h"
#include "wstatictext.h"
#include "tcomponentdialog.h"

class TPrg : public TApplication
{
  public:

    TPrg();

    virtual void handleEvent(TEvent& event);
    static TMenuBar *initMenuBar(TRect);
    static TStatusLine *initStatusLine(TRect);

  private:
    TDialog *dlgGadgets; // Диалог, иммитирующий панель компонентов


    //-- создание диалога О программе
    TDialog* AboutDialog();

    /// создание нового дизайнера диалогов
    TTrialDialog* CreateDialogDesigner();
    /// создание диалога с тестом палитры цветов
    TSelectColorDialog* CreateColorTestDialog();
    ///- создание "палитры компонентов"
    TComponentDialog* ConstructComponentPalette();
};

#endif /* TPRG_H */


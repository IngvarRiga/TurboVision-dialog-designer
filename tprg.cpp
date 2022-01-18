#include "multilang.h"


#include "tprg.h"
#include "common.h"

TPrg::TPrg() :
TProgInit(&TPrg::initStatusLine,
&TPrg::initMenuBar,
&TPrg::initDeskTop
)
{
}

void TPrg::handleEvent(TEvent& event)
{
    TApplication::handleEvent(event);
    if (event.what == evCommand)
    {
        switch (event.message.command)
        {
            case cmAbout:
                deskTop->execView(AboutDialog());
                clearEvent(event);
                break;
            case cm_test_ToolWin:
                //-- Insert - делает окно немодальным :)
                deskTop->insert(ConstructComponentPalette());
                clearEvent(event);
                break;
            case cmNewDialog:
                deskTop->insert(CreateDialogDesigner());
                clearEvent(event);
                break;
            case cmLoadDialog:
            {
                TFileDialog *fd = new TFileDialog("*.dlg", txt_dlg_LoadAsCaption, txt_dlg_SaveAsName, fdOpenButton, 100);

                if (fd != 0 && execView(fd) != cmCancel)
                {
                    char fileName[MAXPATH];
                    fd->getFileName(fileName);
                    TTrialDialog *loaded;
                    ifpstream is;
                    is.open(fileName);
                    is >> loaded;
                    is.close();
                    deskTop->insert(loaded);
                }
                destroy(fd);

                clearEvent(event);
                break;
            }
            case cmColorTest:
                deskTop->insert(CreateColorTestDialog());
                clearEvent(event);
                break;
            default:

                break;
        }
    }
}

TMenuBar *TPrg::initMenuBar(TRect r)
{

    r.b.y = r.a.y + 1;
    //-- Формирование меню программы. 
    return new TMenuBar(r,
            //-- первым идёт так называемое - системное меню
            *new TSubMenu("~\360~", kbAltSpace) +
            * new TMenuItem(winAboutCapt, cmAbout, kbNoKey) +
            newLine() +
            * new TMenuItem(txt_cmExit, cmQuit, kbAltX, hcNoContext, "Alt-X")+
            //-- перечень реализованных алгоритмов
            * new TSubMenu(txt_mnu_Designer, kbNoKey) +
            (TMenuItem &) (
            * new TMenuItem(txt_mnu_NewDialogWindow, cmNewDialog, kbNoKey) +
            * new TMenuItem(txt_mnu_LoadFromResource, cmLoadDialog, kbNoKey) +
            //            newLine()+
            //            * new TMenuItem(txt_mnu_StaticText, cmUnreleased, kbNoKey) +
            //            * new TMenuItem(txt_mnu_Button, cmUnreleased, kbNoKey) +
            //            * new TMenuItem(txt_mnu_InputLine, cmUnreleased, kbNoKey) +
            //            * new TMenuItem("Radio Buttons", cmUnreleased, kbNoKey) +
            //            * new TMenuItem("Check Boxes", cmUnreleased, kbNoKey) +
            //            * new TMenuItem("ListBox", cmUnreleased, kbNoKey) +
            newLine()+
            * new TMenuItem("Test gadget win ;)", cm_test_ToolWin, kbNoKey)
            //            * new TMenuItem("Тест сохранения окна", cmDialogSaveToRes, kbNoKey)
            ) +
            * new TSubMenu(txt_mnu_AlgoritmTest, kbNoKey) +
            (TMenuItem &) (
            * new TMenuItem(txt_mnu_ColorSelect, cmColorTest, kbNoKey)
            //            +
            //            * new TMenuItem("Меню", cmNewMenu, kbNoKey) +
            //            * new TMenuItem("Палитра", cmNewPalette, kbNoKey)
            )
            );

}

/// Формирование линии статуса приложения

TStatusLine *TPrg::initStatusLine(TRect r)
{
    r.a.y = r.b.y - 1;
    return new TStatusLine(r,
            *new TStatusDef(0, 0xFFFF) +
            * new TStatusItem(txt_cmStatusExit, kbAltX, cmQuit) +
            * new TStatusItem(0, kbF10, cmMenu)
            );
}


//------------------------------------------------------------------------------
//-- регион с определением команд

TDialog* TPrg::AboutDialog()
{
    //    TView *control;
    TCustomDialog* dlg = new TCustomDialog(49, 10, winAboutCapt);
    if (!dlg) return 0;
    dlg->insert(new TStaticText(TRect(3, 2, 47, 3), winAboutText1));
    dlg->insert(new TStaticText(TRect(3, 3, 47, 4), "\003Основано на:"));
    dlg->insert(new TStaticText(TRect(3, 4, 47, 5), "\003Turbo Vision by maglibot"));
    dlg->insert(new TStaticText(TRect(3, 5, 47, 6), "\003(C) Ingvar «Rex» Riga"));
    dlg->insert(new TButton(TRect(20, 7, 30, 9), txt_btnOk, cmOK, bfDefault));
    //    control->options &= ~ofSelectable;
    //    dlg->insert(control);
    dlg->selectNext(False);
    return dlg;
}

TSelectColorDialog* TPrg::CreateColorTestDialog()
{
    return new TSelectColorDialog();
}

TComponentDialog* TPrg::ConstructComponentPalette()
{
    return new TComponentDialog();
}

TTrialDialog* TPrg::CreateDialogDesigner()
{
    //-- используем упрощённое создание диалогового окна с автоматической центровкой
    return new TTrialDialog(50, 20, txt_DefaultNewDialogCaption);
}
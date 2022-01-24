#define Uses_TRect
#define Uses_TGroup
#define Uses_TEvent
#define Uses_TKeys
#define Uses_TMenu
#define Uses_TMenuItem
#define Uses_TMenuBox
#include <tvision/tv.h>

#include "twinextmenu.h"
#include "multilang.h"
#include "common.h"

const char * const TWinExtMenu::name = "TWinExtMenu";

TWinExtMenu::TWinExtMenu(const TRect &rect) :
TView(rect)
{
    //-- символ, отображающий служебное меню задан напрямую в функци  draw
    //    drawtext = new char[StringMaxLen];
    //    memset(drawtext, 0x0, StringMaxLen);
    //    strcat(drawtext, "\360");
    eventMask = 0xfce2; //-- установлен флаг получения кликом мышкой
    options |= ofPreProcess;
}

TWinExtMenu::~TWinExtMenu()
{
    //delete drawtext;
}

void TWinExtMenu::draw()
{
    TColorAttr color;
    TDrawBuffer b;
    color = 0x0a;
    setBounds(TRect(0, 2, 1, 3));
    b.moveStr(0, "\360", color);
    writeBuf(0, 0, size.x, 1, b);
}

void TWinExtMenu::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        if (event.what == evMouseUp)
        {
            clearEvent(event);
            auto r = getBounds();
            r.a.x += 10;
            r.b.x = r.a.x + 20;
            r.b.y = r.a.y + 20;
            TMenuBox *contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
                    new TMenu(
                    * new TMenuItem(txt_PropertyDialogCaption, cmOption_Dialog, kbAlt1, hcNoContext, "Alt+1") +
                    (TMenuItem &) (
                    * new TSubMenu(txt_DlgInsertSubMenu, kbNoKey)+
                    * new TMenuItem(txt_mnu_StaticText, cm_ed_InsertStaticText, kbNoKey) +
                    * new TMenuItem(txt_mnu_Button, cm_ed_InsertButton, kbNoKey) +
                    * new TMenuItem(txt_mnu_InputLine, cm_ed_InsertInputLine, kbNoKey) +
                    * new TMenuItem(txt_mnu_RadioButtons, cm_ed_InsertRadioButtons, kbNoKey) +
                    * new TMenuItem(txt_mnu_CheckBoxes, cm_ed_InsertCheckBoxes, kbNoKey) +
                    * new TMenuItem(txt_mnu_ListBox, cm_ed_InsertListBox, kbNoKey) +
                    * new TMenuItem(txt_mnu_Memo, cm_ed_InsertMemo, kbNoKey)
                    ) +
                    newLine()+
                    * new TMenuItem(txt_mnu_DlgPropShowPosition, cmDialogPosOnOff, kbAlt2, hcNoContext, "Alt+2") +
                    * new TMenuItem(txt_mnu_DlgPropShowSize, cmDialogSizeOnOff, kbAlt3, hcNoContext, "Alt+3") +
                    newLine()+
                    * new TMenuItem(txt_mnu_DlgPropShowSizePos, cmDialogPosSizeOnOff, kbAlt4, hcNoContext, "Alt+4") +
                    newLine()+
                    * new TMenuItem(txt_mnu_SaveToRes, cmDialogSaveToRes, kbAlt5, hcNoContext, "Alt+5")+
                    * new TMenuItem(txt_mnu_GenCode, cmDialogGenCode, kbAlt6, hcNoContext, "Alt+6")
                    ), nullptr);
            contextMenu->options |= ofCentered;
            auto res = owner->owner->execView(contextMenu);
            destroy(contextMenu);
            //-- рассылаем команды
            message(owner, evBroadcast, res, nullptr);
        }
    }
    TView::handleEvent(event);
}

void TWinExtMenu::write(opstream& os)
{
    TView::write(os);
    os << eventMask << options;
}

void *TWinExtMenu::read(ipstream& is)
{
    TView::read(is);
    is >> eventMask >> options;
    return this;
}

TStreamable *TWinExtMenu::build()
{
    return new TWinExtMenu(streamableInit);
}

TStreamableClass RWinExtMenu(TWinExtMenu::name,
        TWinExtMenu::build,
        __DELTA(TWinExtMenu)
        );

__link(RView)
__link(RWinExtMenu)


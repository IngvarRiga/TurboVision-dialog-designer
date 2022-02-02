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
    eventMask = 0xFF; //-- установлен флаг получения кликом мышкой
    options |= ofPreProcess;
}


void TWinExtMenu::draw()
{
    TColorAttr color;
    TDrawBuffer b;
    color = 0xAC;
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
                    * new TMenuItem(txt_PropertyDialogCaption, cmOption_Dialog, kbAlt1, hcNoContext, "Ctrl+Enter") +
                    newLine()+
                    * new TMenuItem(txt_mnu_DlgPropShowPosition, cmDialogPosOnOff, kbAlt2, hcNoContext, "Alt+2") +
                    * new TMenuItem(txt_mnu_DlgPropShowSize, cmDialogSizeOnOff, kbAlt3, hcNoContext, "Alt+3") +
                    newLine()+
                    * new TMenuItem(txt_mnu_DlgPropShowSizePos, cmDialogPosSizeOnOff, kbAlt4, hcNoContext, "Alt+4") +
                    newLine()+
                    * new TMenuItem(txt_mnu_SaveToRes, cmDialogSaveToRes, kbAlt5, hcNoContext, "Ctrl+S")+
                    * new TMenuItem(txt_mnu_GenCode, cmDialogGenCode, kbAlt6, hcNoContext, "Ctrl+C")
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


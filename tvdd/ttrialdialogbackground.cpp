#include "ttrialdialogbackground.h"
#include "common.h"

#include <math.h>

const char * const TTrialDialogBackground::name = "TTrialDialogBackground";

TTrialDialogBackground::TTrialDialogBackground(TRect& Bounds) :
TView(Bounds)
{
    
    growMode = gfGrowHiX + gfGrowHiY;
    Patterned = true;
}

void TTrialDialogBackground::draw()
{
    //-- коды указаны для ASCII, символы в консоле - другие
    // #$B0 = light hatch ░ 
    // #$B1 = med.  hatch ▒
    TDrawBuffer bf1;
    char ch1;
    if (Patterned)
        ch1 = 0xb0;
    else
        ch1 = 0x20;
    //-- заполняем буфер легкой штриховки
    bf1.moveChar(0, ch1, 0x8E, size.x); // 76
    for (int i = 0; i < size.y; i++)
        writeLine(0, i, size.x, 1, bf1);
}

void TTrialDialogBackground::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_Dialog, nullptr);
            clearEvent(event);
        }

        if (event.what | evMouseUp)
        {
            //-- вызов контекстного меню для диалога
            if (event.mouse.buttons == mbRightButton)
            {
                message(owner, evBroadcast, cmPopupMenu_Dialog, &event.mouse.where);
            }
        }

    }

    //-- вызываем унаследованный метод обработки сообщений
    TView::handleEvent(event);
}

Boolean TTrialDialogBackground::valid(ushort command)
{
    bool rslt = TView::valid(command);
    if (rslt && (command == cmOK))
    {
    }
    return rslt;
}

void TTrialDialogBackground::write(opstream& os)
{
    TView::write(os);
    os.writeBytes(&Patterned, sizeof(Patterned));
}

void *TTrialDialogBackground::read(ipstream& is)
{
    TView::read(is);
    is.readBytes(&Patterned, sizeof (Patterned));
    return this;
}

TStreamable *TTrialDialogBackground::build()
{
    return new TTrialDialogBackground(streamableInit);
}

TStreamableClass RTrialDialogBackground(
        TTrialDialogBackground::name,
        TTrialDialogBackground::build,
        __DELTA(TTrialDialogBackground)
        );

__link(RView)
__link(RTrialDialogBackground)

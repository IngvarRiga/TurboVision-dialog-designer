#include "tcomponentdialog.h"
#include "multilang.h"

TComponentDialog::TComponentDialog() :
TCustomDialog(TRect(2, 1, 22, 30), txt_dlg_GadgetsPanel, true, false),
TWindowInit(&TCustomDialog::initFrame)
{
    insert(new TWrapStaticText(TRect(2, 1, 18, 2), "StaticText", true));
    insert(new TInputLine(TRect(2, 3, 18, 4), 255));
    insert(new TButton(TRect(1, 5, 18, 7), txt_btnButton, -1, bfDefault));
    insert(new TCheckBoxes(TRect(2, 7, 18, 9), new TSItem(txt_btnCheck1,
            new TSItem(txt_btnCheck2, 0))));
    insert(new TRadioButtons(TRect(2, 10, 18, 12), new TSItem(txt_btnCheck1,
            new TSItem(txt_btnCheck2, 0))));


    //    TScrollBar *sb = new TScrollBar(TRect(19, 15, 20, 20));
    //    insert(sb);

    TSortedListBox *lst = new TSortedListBox(TRect(2, 13, 18, 18), 1, 0);

    insert(lst);

    setState(sfModal, false); //-- окно становится немодальным

}

void TComponentDialog::handleEvent(TEvent& event)
{
    if (event.what == evBroadcast)
    {
        if (event.message.command == cm_cmp_CreateStaticText)
        {

            auto pt = ((TPoint*)event.message.infoPtr);
            auto v = new TWrapStaticText(TRect(pt->x, pt->y-1, pt->x+10, pt->y), "---------");
            //-- прикручиваем тень к объекту, чтобы он "парил"
            v->setState(sfShadow, true);
            v->options |= ofPreProcess | ofPostProcess;
            v->drawView();
            v->setDragged();
            owner->insert(v);
            message(v, evMouseDown, -1, 0);
            //message(v, evBroadcast, cm_cmp_BeginDragMode, 0);
            clearEvent(event);
        }
    }
    TCustomDialog::handleEvent(event);
}

#include "tdialogdesigner.h"

TDialogDesigner::TDialogDesigner(const TRect& bounds, TStringView aTitle, short Number) :
TWindow(bounds, aTitle, Number),
TWindowInit(&TDialogDesigner::initFrame)
{
    options |= ofCentered;
    insert(ConstructDialog());
    TRect r;
    r.a.x = bounds.a.x;
    r.a.y = bounds.a.y;
    r.b.x = bounds.b.x - 2;
    r.b.y = bounds.a.y + 1;

    insert(new TMenuBar(r,
            //-- первым идёт так называемое - системное меню
            *new TSubMenu("Редактор", kbNoKey) +
            *new TMenuItem("Открыть из ресурса", -1, kbNoKey) +
            *new TMenuItem("Сохранить в ресурс", -1, kbNoKey) +
            newLine() +
            *new TMenuItem("Генерировать исходный код", -1, kbNoKey) +
            newLine() +
            *new TMenuItem("Закрыть окно редактора", -1, kbNoKey, hcNoContext, "Alt-X")+
            
            *new TSubMenu("Диалог", kbNoKey) +
            *new TMenuItem("Свойства »", -1, kbNoKey) +
            newLine() +
            *new TMenuItem("Протестировать »", -1, kbNoKey) 
            ));
}

TCustomDialog* TDialogDesigner::ConstructDialog()
{
    TCustomDialog* dlg = new TCustomDialog(TRect(2, 2, 22, 30), "Gadgets", false, false);
    if (!dlg) return 0;
    dlg->insert(new TStaticText(TRect(2, 1, 18, 2), "« Static text »"));
    dlg->insert(new TInputLine(TRect(2, 3, 18, 4), 255));
    dlg->insert(new TButton(TRect(1, 5, 18, 7), "Button", -1, bfDefault));
    dlg->insert(new TCheckBoxes(TRect(2, 7, 18, 9), new TSItem("Select 1",
            new TSItem("Select 2", 0))));
    dlg->insert(new TRadioButtons(TRect(2, 10, 18, 12), new TSItem("Select 1",
            new TSItem("Select 2", 0))));


    // TScrollBar *sb = new TScrollBar(TRect(19, 15, 20, 20));
    // insert(sb);

    // TSortedListBox *lst = new TSortedListBox(TRect(2, 13, 18, 18), 1, sb);

    //dlg->insert(lst);
    dlg->selectNext(False);
    // dlg->setState(sfDragging, false);
    dlg->setState(sfModal, false); //-- окно становится не модальным
    dlg->flags = 0x0; //-- запрещаем перемещать окно и изменять его размеры
    return dlg;
}



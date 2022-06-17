#include "tdialogproperties.h"
#include "multilang.h"

TDialogProperties::TDialogProperties() :
    TCustomDialog(TRect(29, 20, 90, 37), txt_PropertyDialogCaption),
    TWindowInit(&TDialog::initFrame)
{
    insert(new TStaticText(TRect(2, 2, 45, 3), "Заголовок окна"));
    insert(new TStaticText(TRect(2, 4, 45, 5), "Имя класса окна"));
    insert(new TStaticText(TRect(2, 6, 45, 7), "Имя базового класса"));
    insert(new TStaticText(TRect(2, 8, 45, 9), "Дополнительные свойства:"));
    insert(new TStaticText(TRect(7, 10, 45, 11), "Флаги окна"));
    caption = new TInputLine(TRect(2, 3, 59, 4), 241);
    insert(caption);
    class_name = new TInputLine(TRect(2, 5, 59, 6), 241);
    insert(class_name);
    base_name = new TInputLine(TRect(2, 7, 59, 8), 241);
    insert(base_name);
    add_prop = new TCheckBoxes(TRect(2, 9, 45, 10),
                               new TSItem("Центрировать TDialog на экране", 0));
    insert(add_prop);
    dlg_WinFlagDef = new TCheckBoxes(TRect(2, 10, 7, 11),
                                     new TSItem(" ", 0));
    insert(dlg_WinFlagDef);
    dlg_WinFlags = new TCheckBoxes(TRect(2, 11, 27, 13),
                                   new TSItem("wfMove",
                                              new TSItem("wfGrow",
                                                         new TSItem("wfClose",
                                                                    new TSItem("wfZoom", 0)))));
    insert(dlg_WinFlags);
    insert(new TButton(TRect(47, 11, 58, 13), "Ключи", cmKeys, bfDefault));
    insert(new TButton(TRect(1, 14, 11, 16), "Отмена", cmCancel, bfDefault));
    insert(new TButton(TRect(11, 14, 21, 16), "O~K~", cmOK, bfDefault));
    selectNext(false);
}


void TDialogProperties::setData(dataTDP* val)
{
    if (val != nullptr)
    {
        base_name->setData(val->dlgBaseClass);
        class_name->setData(val->dlgClassName);
        caption->setData(val->dlgCaption);
        if (val->dlgOpt_Centered)
            add_prop->press(0);
        if (val->wfDef)
            dlg_WinFlagDef->press(0);
        if (val->wfMove)
            dlg_WinFlags->press(0);
        if (val->wfGrow)
            dlg_WinFlags->press(1);
        if (val->wfClose)
            dlg_WinFlags->press(2);
        if (val->wfZoom)
            dlg_WinFlags->press(3);

    }
}

void TDialogProperties::getData(dataTDP* val)
{
    if (val != nullptr)
    {
        base_name->getData(val->dlgBaseClass);
        class_name->getData(val->dlgClassName);
        caption->getData(val->dlgCaption);
        val->dlgOpt_Centered = add_prop->mark(0);
        val->wfDef = dlg_WinFlagDef->mark(0);
        val->wfMove = dlg_WinFlags->mark(0);
        val->wfGrow = dlg_WinFlags->mark(1);
        val->wfClose = dlg_WinFlags->mark(2);
        val->wfZoom = dlg_WinFlags->mark(3);
    }
}

dataTDP::dataTDP()
{
    //-- очистка строковых массивов
    memset(dlgBaseClass, 0x0, StringMaxLen);
    memset(dlgClassName, 0x0, StringMaxLen);
    memset(dlgCaption, 0x0, StringMaxLen);
    dlgOpt_Centered = true;
}

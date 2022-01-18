#include "tselectcolordialog.h"
#include "common.h"

TSelectColorDialog::TSelectColorDialog() :
TCustomDialog(70, 30, "Тест цвета"),
TWindowInit(&TCustomDialog::initFrame)
{
    cf = new TColorField(2, 2);
    insert(cf);
    insert(new TStaticText(TRect(43, 6, 62, 8), "> Sample text out <\n>  Пример текста  <"));
    insert(new TStaticText(TRect(41, 2, 64, 3), "Click on color cell..."));
    //insert(new TButton(TRect(30, 17, 40, 19), "O~K~", cmOK, bfDefault));
    insert(new TStaticText(TRect(41, 4, 52, 5), "Color:"));
    val = new TInputLine(TRect(53, 4, 64, 5), 11);
    insert(val);
    setState(sfModal, false); //-- окно становится немодальным
}


void TSelectColorDialog::handleEvent(TEvent& event)
{
    const char *pref ="0x";
    //-- двойной клик на неиспользуемом пространстве - вызов редактора
    if (event.what == evBroadcast)
    {
        if (event.message.command == cm_ColorFieldClicked)
        {
            char valp[StringMaxLen];
            char res[StringMaxLen];
            memset(valp,0x0, StringMaxLen);
            memset(res,0x0, StringMaxLen);
            itoa(cf->getColor(), valp, 16);
            strncat(res, pref, strlen(pref));
            strncat(res,valp, strlen(valp));
            val->setData(res);
        }
        clearEvent(event);
    }
    TCustomDialog::handleEvent(event);
}

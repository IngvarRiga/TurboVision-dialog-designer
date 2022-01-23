#include "tdialogproperties.h"
#include "multilang.h"

TDialogProperties::TDialogProperties() :
TCustomDialog(33, 12, txt_PropertyDialogCaption),
TWindowInit(&TDialog::initFrame)
{
    dcn = new TInputLine(TRect(2, 3, 25, 4), StringMaxLen);
    insert(dcn);
    insert(new TLabel(TRect(1, 2, 25, 3), txt_pd_ClassName, dcn));
    dbc = new TInputLine(TRect(2, 5, 25, 6), StringMaxLen);
    insert(dbc);
    insert(new TLabel(TRect(1, 4, 25, 5), txt_pd_BaseClassName, dbc));
    cpt = new TInputLine(TRect(2, 7, 25, 8), StringMaxLen);
    insert(cpt);
    insert(new TLabel(TRect(1, 6, 25, 7), txt_pd_DialogCaption, cpt));

    insert(new TButton(TRect(21, 9, 31, 11), txt_btnOk, cmOK, bfDefault));
    insert(new TButton(TRect(11, 9, 21, 11), txt_btnCancel, cmCancel, bfNormal));
}

TDialogProperties::~TDialogProperties()
{
    //-- очищаем мусор 
}

void TDialogProperties::setData(dataTDP *val)
{
    if (val != nullptr)
    {
        dbc->setData(val->dlgBaseClass);
        dcn->setData(val->dlgClassName);
        cpt->setData(val->dlgCaption);
    }
}

void TDialogProperties::getData(dataTDP *val)
{
    if (val != nullptr)
    {
        dbc->getData(val->dlgBaseClass);
        dcn->getData(val->dlgClassName);
        cpt->getData(val->dlgCaption);
    }
}

dataTDP::dataTDP()
{
    //-- очистка строковых массивов
    memset(dlgBaseClass, 0x0, StringMaxLen);
    memset(dlgClassName, 0x0, StringMaxLen);
    memset(dlgCaption, 0x0, StringMaxLen);
}

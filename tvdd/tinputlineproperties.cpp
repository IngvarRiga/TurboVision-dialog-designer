#include "tinputlineproperties.h"
#include "multilang.h"

TInputLineProperties::TInputLineProperties() :
TCustomDialog(37, 8, txt_PropertyInputLine),
TWindowInit(&TDialog::initFrame)
{
    insert(new TStaticText(TRect(2, 2, 16, 3), txt_pd_StringLen));
    insert(new TStaticText(TRect(2, 3, 16, 4), txt_pd_VariableName));
    var_len = new TInputLine(TRect(17, 2, 35, 3), 5);
    insert(var_len);
    var_name = new TInputLine(TRect(17, 3, 35, 4), 256);
    insert(var_name);
    insert(new TButton(TRect(25, 5, 35, 7), txt_btnOk, cmOK, bfDefault));
    insert(new TButton(TRect(15, 5, 25, 7), txt_btnCancel, cmCancel, bfDefault));
    selectNext(False);
}


void TInputLineProperties::setData(dataTILP *val)
{
    if (val != nullptr)
    {
        var_len->setData((void*)std::to_string(val->var_len).c_str());
        var_name->setData((void*) val->var_name);
    }
}

void TInputLineProperties::getData(dataTILP *val)
{
    if (val != nullptr)
    {
        char tmp[StringMaxLen];
        memset(tmp, 0x0, StringMaxLen);
        memset(val->var_name, 0x0, StringMaxLen);
        var_name->getData(val->var_name);
        var_len->getData((void *) tmp);
        val->var_len=atoi(tmp);
    }
}

dataTILP::dataTILP()
{
    //-- очистка строковых массивов
    memset(var_name, 0x0, StringMaxLen);
    var_len = 255;
}



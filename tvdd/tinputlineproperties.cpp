#include "tinputlineproperties.h"
#include "multilang.h"

TInputLineProperties::TInputLineProperties() :
TCustomDialog(36, 8, txt_PropertyInputLIne),
TWindowInit(&TDialog::initFrame)
{
    insert(new TStaticText(TRect(2, 2, 14, 3), "Длина строки"));
    insert(new TStaticText(TRect(2, 3, 16, 4), "Имя переменной"));
    var_len = new TInputLine(TRect(17, 2, 34, 3), 5);
    insert(var_len);
    var_name = new TInputLine(TRect(17, 3, 34, 4), 256);
    insert(var_name);
    insert(new TButton(TRect(25, 5, 35, 7), txt_btnOk, cmOK, bfDefault));
    insert(new TButton(TRect(15, 5, 25, 7), txt_btnCancel, cmCancel, bfDefault));

    selectNext(False);

}

TInputLineProperties::~TInputLineProperties()
{
    //-- очищаем мусор 
}

void TInputLineProperties::setData(dataTILP *val)
{
    if (val != nullptr)
    {
        char tmp[StringMaxLen];
        memset(tmp, 0x0, StringMaxLen);
        _itoa(val->var_len, tmp, 10);
        var_len->setData((void*) tmp);
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



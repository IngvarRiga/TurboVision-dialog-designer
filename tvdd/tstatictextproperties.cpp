#include "tstatictextproperties.h"
#include "multilang.h"

TStaticTextProperties::TStaticTextProperties() :
TCustomDialog(54, 14, txt_PropertyStaticText),
TWindowInit(&TDialog::initFrame)
{
    insert(new TLabel(TRect(1, 1, 7, 2), txt_pd_Text, text));
    insert(new TStaticText(TRect(8, 8, 23, 9), txt_pd_ClassName));

    sbv = new TScrollBar(TRect(51, 2, 52, 6));
    insert(sbv);
    sbh = new TScrollBar(TRect(2, 6, 51, 7));
    insert(sbh);

    text = new TMemo(TRect(2, 2, 51, 6), (TScrollBar*) sbh, (TScrollBar*) sbv, 0, 255);
    insert(text);


    var_name = new TInputLine(TRect(24, 9, 52, 10), 27);
    insert(var_name);

    var_name_use = new TCheckBoxes(TRect(2, 9, 23, 10), new TSItem(txt_pd_VariableName, 0));
    insert(var_name_use);

    class_name = new TInputLine(TRect(24, 8, 52, 9), 27);
    insert(class_name);

    insert(new TButton(TRect(42, 11, 52, 13), txt_btnOk, cmOK, bfDefault));
    insert(new TButton(TRect(32, 11, 42, 13), txt_btnCancel, cmCancel, bfDefault));

    selectNext(False);
}


void TStaticTextProperties::setData(dataTSTP *val)
{
    if (val != nullptr)
    {
        auto rec = new TDesc();
        memset(rec->buffer, 0x0, StringMaxLen);
        strncpy(rec->buffer, val->caption, StringMaxLen);
        rec->length = strlen(val->caption);
        text->setData(rec);

        class_name->setData((void*) val->class_name);
        var_name->setData((void*) val->var_name);
        if (val->use_var_name)
            var_name_use->press(0);

        delete rec;
    }
}

void TStaticTextProperties::getData(dataTSTP *val)
{
    if (val != nullptr)
    {
        auto rec = new TDesc();
        text->getData(rec);
        memset(val->caption, 0x0, StringMaxLen);
        strncpy(val->caption, rec->buffer, StringMaxLen);
        
        memset(val->class_name, 0x0, StringMaxLen);
        memset(val->var_name, 0x0, StringMaxLen);
        class_name->getData(val->class_name);
        var_name->getData(val->var_name);
        val->use_var_name = var_name_use->mark(0);        
    }
}

dataTSTP::dataTSTP()
{
    //-- очистка строковых массивов
    memset(caption, 0x0, StringMaxLen);
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    use_var_name = false;

}

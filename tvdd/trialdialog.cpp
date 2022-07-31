#include <stdlib.h>
#include <sys/stat.h>

#include "trialdialog.h"
#include "multilang.h"
#include "tdialogproperties.h"
#include "ttrialstatictext.h"
#include "ttrialinputline.h"
#include "ttrialbutton.h"
#include "ttrialcheckboxes.h"
#include "ttrialradiobuttons.h"
#include "ttriallistbox.h"
#include "ttrialmemo.h"
#include "tstatictextproperties.h"
#include "tinputlineproperties.h"
#include "tbuttonproperties.h"
#include "tcheckboxesproperties.h"

const char* _class_name = "TNewDialog";
const char* _base_class_name = "TDialog";


TTrialDialog::TTrialDialog(const int width, const int height, TStringView aTitle, bool sizeable) :
    TCustomDialog(width, height, aTitle, sizeable),
    TWindowInit(&TCustomDialog::initFrame)
{
    isDest = false;
    //----- ШТРИХОВКА ----------------------------------------------------------
    //-- задаем внутреннюю штриховку разрабатываемого окна так,
    //-- чтобы она НЕ перекрывала границу окна
    TRect inner;
    inner.a.x = clip.a.x + 1;
    inner.a.y = clip.a.y + 1;
    inner.b.x = clip.b.x - 1;
    inner.b.y = clip.b.y - 1;
    Background = new TTrialDialogBackground(inner);
    insert(Background);
    //----- ШТРИХОВКА ----------------------------------------------------------
    setState(sfModal, false); //-- окно НЕ модально, поскольку в режиме разработки
    DialSaved = false;
    //-- окно можно перемещать за границы зоны видимости. для запрета - раскомментарить строку ниже
    //dragMode = dmLimitAll;
    flags |= wfGrow; // это позволяет изменять размеры диалога, хотя по умолчанию опция включена в предке

    memset(dlg_file_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    memset(base_class_name, 0x0, StringMaxLen);
    memcpy(dlg_file_name, _class_name, strlen(_class_name));
    strcat(dlg_file_name, ".json");
    dlg_loaded = false;
    memcpy(class_name, _class_name, strlen(_class_name) + 1);
    memcpy(base_class_name, _base_class_name, strlen(_base_class_name) + 1);
    prp_Centered = true;
    //-- по умолчанию все флаги такие как заданы библиотекой
    wfDef = false;
    tr_wfClose = false;
    tr_wfMove = false;
    tr_wfGrow = false;
    tr_wfZoom = false;
    //-- Дополнительное меню в заголовке
    emnu = new TWinExtMenu(TRect(10, size.y - 1, 20, size.y));
    insert(emnu);
    //-- индикатор размеров окна
    ind = new TWinSizeIndicator(TRect(10, size.y - 1, 20, size.y));
    insert(ind);
}

TTrialDialog::~TTrialDialog()
{
    //-- перед удалением обнуляем все буферы
    memset(class_name, 0x0, StringMaxLen);
    memset(base_class_name, 0x0, StringMaxLen);
}

void TTrialDialog::setState(ushort aState, bool enable)
{
    //-- вызываем обработчик -установщик унаследованного окна
    TCustomDialog::setState(aState, enable);
}

/// <summary>
/// Изменение свойств диалога
/// </summary>
void TTrialDialog::editDialogProperties()
{
    auto data = new dataTDP();
    memcpy(data->dlgClassName, class_name, strlen(class_name));
    memcpy(data->dlgBaseClass, base_class_name, strlen(base_class_name));
    memcpy(data->dlgCaption, title, strlen(title));
    data->dlgOpt_Centered = prp_Centered;
    data->wfDef = wfDef;
    data->wfMove = tr_wfMove;
    data->wfGrow = tr_wfGrow;


    data->wfClose = tr_wfClose;
    data->wfZoom = tr_wfZoom;
    TDialogProperties* win = new TDialogProperties();
    win->setData(data);
    if (owner->execView(win) == cmOK)
    {
        win->getData(data);
        setClassName(data->dlgClassName);
        setBaseClassName(data->dlgClassName);
        setCentered(data->dlgOpt_Centered);
        setCaption(data->dlgCaption);
        set_wfDef(data->wfDef);
        set_wfMove(data->wfMove);
        set_wfGrow(data->wfGrow);
        set_wfClose(data->wfClose);
        set_wfZoom(data->wfZoom);
        drawView();
        frame->drawView();
        DialSaved = false;
    }
    delete data;
    destroy(win);
}

void TTrialDialog::setClassName(const char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    memcpy(class_name, val, strlen(val));
}
void TTrialDialog::setBaseClassName(const char* val)
{
    memset(base_class_name, 0x0, StringMaxLen);
    memcpy(base_class_name, val, strlen(val));
}

void TTrialDialog::setDialogFileName(const char* val)
{
    memset(dlg_file_name, 0x0, StringMaxLen);
    memcpy(dlg_file_name, val, strlen(val));
}

const char* TTrialDialog::getDialogFileName()
{
    return dlg_file_name;
}

void TTrialDialog::setCaption(const char* val)
{
    delete title;
    auto lenCapt = strlen(val) + 1;
    title = new char[lenCapt];
    memset((void*)title, 0x0, lenCapt);
    memcpy((void*)title, val, lenCapt - 1);
}
void TTrialDialog::setCentered(bool val)
{
    prp_Centered = val;
}
void TTrialDialog::close()
{
    if (!DialSaved)
    {
        auto res = messageBox(txt_SaveDialogQuest, mfConfirmation | mfYesNoCancel);
        if (res == cmYes)
        {
            saveDialogToJSON();
        }
        if (res == cmCancel)
            return;
    }
    isDest = true;
    TCustomDialog::close();
}

void TTrialDialog::handleEvent(TEvent& event)
{
    //-- Обрати внимание, что функция clearEvent(event); вызывается в каждом событии!!!!
    //-- Казалось бы можно сократить код, но тогда при редактировании нескольких окон одновременно
    //-- будут сложности! А так, Drag&Drop срабатывает на то окно, на котором или бросили компонент
    //-- или на том, которое сверху и компонент вставляется правильно.

    if (event.what | evMouse)
    {
        if (!isDest)
            //-- отключаем отображение позиции курсора в текущем диалоге
            message(Background, evBroadcast, cm_DisableCursorPaint, 0);
    }
    if (event.what == evBroadcast)
    {
        if (event.message.command == cm_DisableCursorPaint)
        {
            message(Background, evBroadcast, cm_DisableCursorPaint, 0);
            clearEvent(event);
            return;
        }

        switch (event.message.command)
        {
            case cmPopupMenu_Dialog:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);

                    //auto contextMenu = dialogMenu();
                    ////-- смещаем левую верхнюю точку меню в точку клика мышкой на экране
                    //auto b = contextMenu->getBounds();
                    //auto dx = b.b.x - b.a.x;
                    //auto dy = b.b.y - b.a.y;
                    //b.a.x = tmp.x;
                    //b.a.y = tmp.y - 1;
                    //b.b.x = b.a.x + dx;
                    //b.b.y = b.a.y + dy;
                    //contextMenu->setBounds(b);
                    ////---------------------------------------------------------------------
                    //auto res = this->owner->execView(contextMenu);
                    //destroy(contextMenu);
                    auto res = popupMenu(tmp, dialogMenu());
                    //-- рассылаем команды
                    if (res != 0)
                        //-- в качестве параметра передаем точку клика мышки, так можно будет указывать точное место вставки компонента
                        message(owner, evBroadcast, res, &tmp);
                    break;
                }
            case cmOption_Dialog:
                {
                    //-- вызов редактора свойств диалога
                    editDialogProperties();
                    clearEvent(event);
                    break;
                }
            case cmOption_StaticText:
                {
                    //-- вызов настройки статического текста
                    auto data = new dataTSTP();
                    strncpy(data->caption, ((TTrialStaticText*)event.message.infoPtr)->getCaption(), StringMaxLen);
                    strncpy(data->class_name, ((TTrialStaticText*)event.message.infoPtr)->getClassName(), StringMaxLen);
                    strncpy(data->var_name, ((TTrialStaticText*)event.message.infoPtr)->getVarName(), StringMaxLen);
                    data->use_var_name = ((TTrialStaticText*)event.message.infoPtr)->getUsedVarName();

                    TStaticTextProperties* win = new TStaticTextProperties();
                    win->setData(data);
                    if (owner->execView(win) == cmOK)
                    {
                        win->getData(data);
                        std::string sc = data->caption;
                        sc.erase(std::remove(sc.begin(), sc.end(), '\r'));

                        ((TTrialStaticText*)event.message.infoPtr)->setCaption(sc.c_str());
                        ((TTrialStaticText*)event.message.infoPtr)->setClassName(data->class_name);
                        ((TTrialStaticText*)event.message.infoPtr)->setVarName(data->var_name);
                        ((TTrialStaticText*)event.message.infoPtr)->setUsedVarName(data->use_var_name);
                        drawView();
                        DialSaved = false;
                    }
                    delete data;
                    destroy(win);
                    clearEvent(event);
                    break;
                }
            case cmOption_Button:
                {
                    //-- вызов настройки TButton
                    auto data = new dataTBTNP();
                    strncpy(data->caption, ((TTrialButton*)event.message.infoPtr)->getCaption(), StringMaxLen);
                    //strncpy(data->class_name, ((TTrialButton*)event.message.infoPtr)->getClassName(), StringMaxLen);
                    strncpy(data->var_name, ((TTrialButton*)event.message.infoPtr)->getVarName(), StringMaxLen);
                    data->use_var_name = ((TTrialButton*)event.message.infoPtr)->getUsedVarName();

                    TButtonProperties* win = new TButtonProperties();
                    win->setData(data);
                    if (owner->execView(win) == cmOK)
                    {
                        win->getData(data);
                        ((TTrialButton*)event.message.infoPtr)->setCaption(data->caption);
                        //((TTrialButton*)event.message.infoPtr)->setClassName(data->class_name);
                        ((TTrialButton*)event.message.infoPtr)->setVarName(data->var_name);
                        ((TTrialButton*)event.message.infoPtr)->setUsedVarName(data->use_var_name);
                        drawView();
                        DialSaved = false;
                    }
                    delete data;
                    destroy(win);
                    clearEvent(event);
                    break;
                }
            case cmOption_CheckBoxes:
                {
                    //-- вызов настройки TCheckBoxes
                    auto data = new dataTCBP();
                    TTrialCheckBoxes* cb = ((TTrialCheckBoxes*)event.message.infoPtr);
                    strncpy(data->class_name, cb->getClassName(), StringMaxLen);
                    strncpy(data->var_name, cb->getVarName(), StringMaxLen);
                    auto itm = cb->getItems();
                    auto cnt = itm->getCount();
                    int rep = 1;
                    strncpy(data->v0, (char*)itm->at(0), strlen((char*)itm->at(0))); rep++;
                    if (rep <= cnt) { strncpy(data->v1, (char*)itm->at(1), strlen((char*)itm->at(1))); rep++; }
                    if (rep <= cnt) { strncpy(data->v2, (char*)itm->at(2), strlen((char*)itm->at(2))); rep++; }
                    if (rep <= cnt) { strncpy(data->v3, (char*)itm->at(3), strlen((char*)itm->at(3))); rep++; }
                    if (rep <= cnt) { strncpy(data->v4, (char*)itm->at(4), strlen((char*)itm->at(4))); rep++; }
                    if (rep <= cnt) { strncpy(data->v5, (char*)itm->at(5), strlen((char*)itm->at(5))); rep++; }
                    if (rep <= cnt) { strncpy(data->v6, (char*)itm->at(6), strlen((char*)itm->at(6))); rep++; }
                    if (rep <= cnt) { strncpy(data->v7, (char*)itm->at(7), strlen((char*)itm->at(7))); rep++; }
                    if (rep <= cnt) { strncpy(data->v8, (char*)itm->at(8), strlen((char*)itm->at(8))); rep++; }
                    if (rep <= cnt) { strncpy(data->v9, (char*)itm->at(9), strlen((char*)itm->at(9))); rep++; }
                    if (rep <= cnt) { strncpy(data->v10, (char*)itm->at(10), strlen((char*)itm->at(10))); rep++; }
                    if (rep <= cnt) { strncpy(data->v11, (char*)itm->at(11), strlen((char*)itm->at(11))); rep++; }
                    if (rep <= cnt) { strncpy(data->v12, (char*)itm->at(12), strlen((char*)itm->at(12))); rep++; }
                    if (rep <= cnt) { strncpy(data->v13, (char*)itm->at(13), strlen((char*)itm->at(13))); rep++; }
                    if (rep <= cnt) { strncpy(data->v14, (char*)itm->at(14), strlen((char*)itm->at(14))); rep++; }
                    if (rep <= cnt) { strncpy(data->v15, (char*)itm->at(15), strlen((char*)itm->at(15))); rep++; }
                    TCheckBoxesProperties* win = new TCheckBoxesProperties();
                    win->setData(data);
                    if (owner->execView(win) == cmOK)
                    {
                        win->getData(data);
                        bool br = false;
                        auto its = new TSItem(TStringView(data->v0), nullptr);
                        auto itsn = its;
                        if (strlen(data->v1) > 0) { itsn->next = new TSItem(TStringView(data->v1), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v2) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v2), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v3) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v3), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v4) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v4), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v5) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v5), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v6) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v6), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v7) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v7), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v8) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v8), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v9) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v9), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v10) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v10), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v11) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v11), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v12) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v12), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v13) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v13), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v14) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v14), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v15) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v15), nullptr); }

                        cb->recreateItems(its);

                        cb->setClassName(data->class_name);
                        cb->setVarName(data->var_name);
                        cb->drawView();
                        DialSaved = false;
                    }
                    delete data;
                    destroy(win);
                    clearEvent(event);
                    break;
                }
            case cmOption_InputLine:
                {
                    //-- вызов настройки статического текста
                    auto data = new dataTILP();
                    strncpy(data->var_name, ((TTrialInputLine*)event.message.infoPtr)->getVarName(), StringMaxLen);
                    data->var_len = ((TTrialInputLine*)event.message.infoPtr)->getVarLen();

                    TInputLineProperties* win = new TInputLineProperties();
                    win->setData(data);
                    if (owner->execView(win) == cmOK)
                    {
                        win->getData(data);
                        ((TTrialInputLine*)event.message.infoPtr)->setVarName(data->var_name);
                        ((TTrialInputLine*)event.message.infoPtr)->setVarLen(data->var_len);
                        drawView();
                        DialSaved = false;
                    }
                    delete data;
                    destroy(win);
                    clearEvent(event);
                    break;
                }
            case cmOption_ListBox:
                {
                    //-- вызов настройки
                    clearEvent(event);
                    break;
                }
            case cmOption_Memo:
                {
                    //-- вызов настройки
                    clearEvent(event);
                    break;
                }
            case cmOption_RadioButtons:
                {
                    //-- вызов настройки TRadioButtons
                    auto data = new dataTCBP();
                    TTrialRadioButtons* cb = ((TTrialRadioButtons*)event.message.infoPtr);
                    strncpy(data->class_name, cb->getClassName(), StringMaxLen);
                    strncpy(data->var_name, cb->getVarName(), StringMaxLen);
                    auto itm = cb->getItems();
                    auto cnt = itm->getCount();
                    int rep = 1;
                    strncpy(data->v0, (char*)itm->at(0), strlen((char*)itm->at(0))); rep++;
                    if (rep <= cnt) { strncpy(data->v1, (char*)itm->at(1), strlen((char*)itm->at(1))); rep++; }
                    if (rep <= cnt) { strncpy(data->v2, (char*)itm->at(2), strlen((char*)itm->at(2))); rep++; }
                    if (rep <= cnt) { strncpy(data->v3, (char*)itm->at(3), strlen((char*)itm->at(3))); rep++; }
                    if (rep <= cnt) { strncpy(data->v4, (char*)itm->at(4), strlen((char*)itm->at(4))); rep++; }
                    if (rep <= cnt) { strncpy(data->v5, (char*)itm->at(5), strlen((char*)itm->at(5))); rep++; }
                    if (rep <= cnt) { strncpy(data->v6, (char*)itm->at(6), strlen((char*)itm->at(6))); rep++; }
                    if (rep <= cnt) { strncpy(data->v7, (char*)itm->at(7), strlen((char*)itm->at(7))); rep++; }
                    if (rep <= cnt) { strncpy(data->v8, (char*)itm->at(8), strlen((char*)itm->at(8))); rep++; }
                    if (rep <= cnt) { strncpy(data->v9, (char*)itm->at(9), strlen((char*)itm->at(9))); rep++; }
                    if (rep <= cnt) { strncpy(data->v10, (char*)itm->at(10), strlen((char*)itm->at(10))); rep++; }
                    if (rep <= cnt) { strncpy(data->v11, (char*)itm->at(11), strlen((char*)itm->at(11))); rep++; }
                    if (rep <= cnt) { strncpy(data->v12, (char*)itm->at(12), strlen((char*)itm->at(12))); rep++; }
                    if (rep <= cnt) { strncpy(data->v13, (char*)itm->at(13), strlen((char*)itm->at(13))); rep++; }
                    if (rep <= cnt) { strncpy(data->v14, (char*)itm->at(14), strlen((char*)itm->at(14))); rep++; }
                    if (rep <= cnt) { strncpy(data->v15, (char*)itm->at(15), strlen((char*)itm->at(15))); rep++; }
                    TCheckBoxesProperties* win = new TCheckBoxesProperties();
                    win->setData(data);

                    if (owner->execView(win) == cmOK)
                    {
                        win->getData(data);
                        bool br = false;
                        auto its = new TSItem(TStringView(data->v0), nullptr);
                        auto itsn = its;
                        if (strlen(data->v1) > 0) { itsn->next = new TSItem(TStringView(data->v1), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v2) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v2), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v3) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v3), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v4) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v4), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v5) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v5), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v6) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v6), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v7) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v7), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v8) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v8), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v9) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v9), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v10) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v10), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v11) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v11), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v12) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v12), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v13) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v13), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v14) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v14), nullptr); itsn = itsn->next; }
                        else { br = true; }
                        if ((strlen(data->v15) > 0 && !br)) { itsn->next = new TSItem(TStringView(data->v15), nullptr); }

                        cb->recreateItems(its);

                        cb->setClassName(data->class_name);
                        cb->setVarName(data->var_name);
                        cb->drawView();
                        DialSaved = false;
                    }
                    delete data;
                    destroy(win);
                    clearEvent(event);
                    break;
                }
            case cmDialogPosOnOff:
                {
                    ind->setPosInfo(!ind->getPosInfo());
                    drawView();
                    frame->drawView();
                    clearEvent(event);
                    break;
                }
            case cmDialogSizeOnOff:
                {
                    ind->setSizeInfo(!ind->getSizeInfo());
                    frame->drawView();
                    clearEvent(event);
                    break;
                }
            case cmDialogPosSizeOnOff:
                {
                    if (ind->getPosInfo() || ind->getSizeInfo())
                    {
                        ind->setSizeInfo(false);
                        ind->setPosInfo(false);
                    }
                    else
                    {
                        ind->setSizeInfo(true);
                        ind->setPosInfo(true);
                    }
                    frame->drawView();
                    clearEvent(event);
                    break;
                }
            case cm_ed_InsertStaticText:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);
                    auto lc = makeLocal(tmp);
                    //-- добавление нового TStaticText
                    auto v = new TTrialStaticText(TRect(lc.x, lc.y, lc.x + 10, lc.y + 1), txt_btnStaticText);
                    forEach(&unselected, 0);
                    v->setSelected(true);
                    insert(v);
                    DialSaved = false;
                    break;
                }
            case cm_drp_DropStaticText:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    auto lc = makeLocal(tmp);
                    auto b = getExtent();
                    //-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                    //-- чтобы не вставлять то, что не увидится
                    if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
                    {
                        clearEvent(event);
                        //-- добавление нового TStaticText
                        auto v = new TTrialStaticText(TRect(lc.x, lc.y, lc.x + 10, lc.y + 1), txt_btnStaticText);
                        forEach(&unselected, 0);
                        v->setSelected(true);
                        insert(v);
                        DialSaved = false;
                        this->focus();
                    }
                    break;
                }
            case cm_ed_InsertInputLine:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);
                    auto lc = makeLocal(tmp);
                    //-- добавление нового TInputLine
                    auto v = new TTrialInputLine(TRect(lc.x, lc.y, lc.x + 12, lc.y + 1), 255);
                    forEach(&unselected, 0);
                    v->setSelected(true);
                    insert(v);
                    DialSaved = false;
                    break;
                }
            case cm_drp_DropInputLine:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    auto lc = makeLocal(tmp);
                    auto b = getExtent();
                    //-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                    //-- чтобы не вставлять то, что не увидится
                    if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
                    {
                        clearEvent(event);
                        //-- добавление нового TStaticText
                        auto v = new TTrialInputLine(TRect(lc.x, lc.y, lc.x + 12, lc.y + 1), 255);
                        forEach(&unselected, 0);
                        v->setSelected(true);
                        insert(v);
                        DialSaved = false;
                        this->focus();
                    }
                    break;
                }
            case cm_ed_InsertButton:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);
                    auto lc = makeLocal(tmp);
                    //-- добавление нового TInputLine
                    auto v = new TTrialButton(TRect(lc.x, lc.y, lc.x + 10, lc.y + 2), txt_btnButton, -1);
                    forEach(&unselected, 0);
                    v->setSelected(true);
                    insert(v);
                    DialSaved = false;
                    break;
                }
            case cm_drp_DropButton:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;

                    auto lc = makeLocal(tmp);
                    auto b = getExtent();
                    //-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                    //-- чтобы не вставлять то, что не увидится
                    if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
                    {
                        clearEvent(event);
                        //-- добавление нового TStaticText
                        auto v = new TTrialButton(TRect(lc.x, lc.y, lc.x + 10, lc.y + 2), txt_btnButton, -1);
                        forEach(&unselected, 0);
                        v->setSelected(true);
                        insert(v);
                        DialSaved = false;
                        this->focus();
                    }
                    break;
                }
            case cm_ed_InsertCheckBoxes:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);
                    auto lc = makeLocal(tmp);
                    //-- добавление нового TCheckBoxes
                    insert(new TTrialCheckBoxes(TRect(lc.x, lc.y, lc.x + 12, lc.y + 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr))));
                    DialSaved = false;
                    break;
                }
            case cm_drp_DropCheckBoxes:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;

                    auto lc = makeLocal(tmp);
                    auto b = getExtent();
                    //-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                    //-- чтобы не вставлять то, что не увидится
                    if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
                    {
                        clearEvent(event);
                        //-- добавление нового TStaticText
                        auto v = new TTrialCheckBoxes(TRect(lc.x, lc.y, lc.x + 12, lc.y + 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr)));
                        forEach(&unselected, 0);
                        v->setSelected(true);
                        insert(v);
                        DialSaved = false;
                        this->focus();
                    }
                    break;
                }
            case cm_ed_InsertRadioButtons:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);
                    auto lc = makeLocal(tmp);

                    //-- добавление нового TCheckBoxes
                    insert(new TTrialRadioButtons(TRect(lc.x, lc.y, lc.x + 12, lc.y + 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr))));
                    DialSaved = false;
                    break;
                }
            case cm_drp_DropRadioButtons:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;

                    auto lc = makeLocal(tmp);
                    auto b = getExtent();
                    //-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                    //-- чтобы не вставлять то, что не увидится
                    if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
                    {
                        clearEvent(event);
                        //-- добавление нового TStaticText
                        auto v = new TTrialRadioButtons(TRect(lc.x, lc.y, lc.x + 12, lc.y + 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr)));
                        forEach(&unselected, 0);
                        v->setSelected(true);
                        insert(v);
                        DialSaved = false;
                        this->focus();
                    }
                    break;
                }
            case cm_ed_InsertListBox:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);
                    auto lc = makeLocal(tmp);

                    //-- добавление нового TListBox
                    insert(new TTrialListBox(TRect(lc.x, lc.y, lc.x + 10, lc.y + 3), 1, 0));
                    DialSaved = false;
                    break;
                }
            case cm_drp_DropListBox:
                {
                    //-- добавление нового TListBox
                    insert(new TTrialListBox(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), 1, 0));
                    DialSaved = false;
                    clearEvent(event);
                    break;
                }
            case cm_ed_InsertMemo:
                {
                    TPoint tmp;
                    tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    clearEvent(event);
                    auto lc = makeLocal(tmp);
                    //-- добавление нового TInputLine
                    auto v = new TTrialMemo(TRect(lc.x, lc.y, lc.x + 10, lc.y + 3), nullptr, nullptr, nullptr, 255);
                    forEach(&unselected, 0);
                    v->setSelected(true);
                    insert(v);
                    DialSaved = false;
                    break;
                }
            case cm_drp_DropMemo:
                {
                    //TPoint tmp;
                    //tmp.x = ((TPoint*)event.message.infoPtr)->x;
                    //tmp.y = ((TPoint*)event.message.infoPtr)->y;
                    //clearEvent(event);

                    //auto lc = makeLocal(tmp);
                    //auto b = getExtent();
                    ////-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                    ////-- чтобы не вставлять то, что не увидится
                    //if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
                    //{
                    //	//-- добавление нового TStaticText
                    //	auto v = new TTrialMemo(TRect(lc.x, lc.y, lc.x + 12, lc.y + 2), nullptr, nullptr, nullptr, 255);
                    //	forEach(&unselected, 0);
                    //	v->setSelected(true);
                    //	insert(v);
                    //	DialSaved = false;
                    //}
                    //break;
                }
            case cmDialogSaveToJson:
                {
                    clearEvent(event);
                    saveDialogToJSON();
                    break;
                }
            case cmDialogSaveToJsonAs:
                {
                    clearEvent(event);
                    SaveDialogAs();
                    break;
                }
            case cmDialogGenCode:
                {
                    clearEvent(event);
                    saveDialogToSrc();
                    break;
                }
            case cm_ed_Paste:
                {
                    clearEvent(event);
                    if (!copy_buffer.is_null())
                        this->insert(object_fromJSON(copy_buffer));
                    else
                    {
                        messageBox(txt_CopyPasteBufferIsEmpty, mfInformation | mfOKButton);
                    }
                    break;
                }
        }
    }
    //-- переопределяем действия клавиш в режиме разработки
    if (event.what == evKeyDown)
    {
        //-- обработка нажатий служебных клавиш
        if (event.keyDown.keyCode == kbCtrlEnter)
        {
            clearEvent(event);
            editDialogProperties();
            return;
        }
        if (event.keyDown.keyCode == kbCtrlC)
        {
            clearEvent(event);
            saveDialogToSrc();
            return;
        }
        if (event.keyDown.keyCode == kbShiftIns)
        {
            clearEvent(event);
            if (!copy_buffer.is_null())
                this->insert(object_fromJSON(copy_buffer));
            else
            {
                messageBox(txt_CopyPasteBufferIsEmpty, mfInformation | mfOKButton);
            }
            return;
        }
    }

    /*

    //-- Реализованный алгоритм удаления - приводит к непонятным ошибкам, когда попытка удаления одного компонента
    //-- приводит к удалению нескольких сразу. В чем косяк пока не разобрался и времени на это нет
    //-- обработку клавиш повесил непосредственно на сами компоненты
    if (event.what == evKeyDown)
    {
        //-- обработка нажатий служебных клавиш
        if (event.keyDown.keyCode == kbCtrlDel)
        {
            //-- удаление выбранного элемента
            forEach(&deleteSelected, 0);
        }
    }*/
    TCustomDialog::handleEvent(event);
}


/// <summary>
/// Сохранение текущего диалога в JSON-файле
/// </summary>
void TTrialDialog::saveDialogToJSON()
{
    //-- Формируем описание в JSON
    std::string serialized_string = DialogToJSON().dump(2);
    //-- если диалог был загружен из файла
    if (dlg_loaded)
    {
        struct stat buf;
        errno_t err;
        auto res = stat(dlg_file_name, &buf);
        if (res != 0)
        {
            if (errno == ENOENT)
            {
                //-- такого файла не существует - сохраняем его
                ofstream os;
                os.open(dlg_file_name);
                os << serialized_string;
                os.close();
                DialSaved = true;
            }
        }
        else
        {
            //-- файл существует
            auto res1 = messageBox(txt_RewriteDialogFile, mfConfirmation | mfYesNoCancel);
            if (res1 == cmCancel) return;
            if (res1 == cmYes)
            {
                ofstream os;
                os.open(dlg_file_name);
                os << serialized_string;
                os.close();
                DialSaved = true;
            }
            if (res1 == cmNo)
            {
                SaveDialogAs();
            }
        }
    }
    else
    {
        SaveDialogAs();
    }
}

void TTrialDialog::SaveDialogAs()
{
    std::string serialized_string = DialogToJSON().dump(2);
    //-- Диалоговое окно было создано а не загружено - сохраняем его
    //-- первоначально формируем имя файла из имени класса
    std::string fn(class_name);
    fn+=".json";
    auto fd = new TFileDialog(fn, txt_dlg_SaveAsCaption, txt_dlg_SaveAsName, fdOKButton, 100);
    if (fd != 0 && owner->execView(fd) != cmCancel)
    {
        char fileName[MAXPATH];
        fd->getFileName(fileName);
        ofstream os;
        os.open(fileName);
        os << serialized_string;
        os.close();
        DialSaved = true;
        setDialogFileName(fileName);
        //-- теперь этот файл "существует" и мы считаем его "загруженным"
        setLoaded();
    }
    destroy(fd);
}

nlohmann::json TTrialDialog::DialogToJSON()
{
    nlohmann::json sav;
    std::vector<nlohmann::json> src;

    //-- Формируем JSON описание диалога. В это описание входят только те свойства, которые реально
    //-- имеют значение для конечного пользователя. Т.е. всякие индикаторы во время разработки не участвуют 
    //-- в сохранении
    sav[str_type] = otDialog; //-- тип сохраняемого ресурса
    sav[str_class_name] = class_name; //-- имя класса
    sav[str_base_class_name] = base_class_name; //-- имя базового класса
    //--  запоминаем размеры
    auto sz = getBounds();
    sav[str_size][str_x] = sz.b.x - sz.a.x;
    sav[str_size][str_y] = sz.b.y - sz.a.y;
    sav[str_caption] = title;
    sav[str_centered] = prp_Centered;
    //-- перечень объектов в окне
    sav[str_wfDef] = wfDef;
    sav[str_wfClose] = tr_wfClose;
    sav[str_wfGrow] = tr_wfGrow;
    sav[str_wfMove] = tr_wfMove;
    sav[str_wfZoom] = tr_wfZoom;

    //-- перечень объектов в окне
    forEach(&generateDialogJSON, &src);

    for (int i = src.size() - 1; i > -1; i--)
        sav[str_objects].push_back(src[i]);
    return sav;
}

void TTrialDialog::saveDialogToSrc()
{
    auto fd = new TFileDialog("*.src", txt_dlg_SaveCodeAsCaption, txt_dlg_SaveAsName, fdOKButton, 100);

    if (fd != 0 && owner->execView(fd) != cmCancel)
    {
        char fileName[MAXPATH];
        fd->getFileName(fileName);
        ofstream out;
        out.open(fileName);
        GenCode(&out);
        out.close();
    }
    destroy(fd);
}

bool TTrialDialog::valid(ushort command)
{
    bool rslt = TCustomDialog::valid(command);
    if (rslt && (command == cmOK))
    {
    }
    return rslt;
}

void TTrialDialog::GenCode(ofstream* res)
{
    std::vector<std::string> elem;
    auto r = getBounds();
    //-- генерируем код
    *res << class_name << "::" << class_name << "() :\n ";
    *res << base_class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << title << "\"),\n";
    *res << " TWindowInit(&" << base_class_name << "::initFrame)\n{\n";
    //-- если установлен признак центрирования диалога
    if (prp_Centered)
        *res << " options |= ofCentered;\n";
    //-- проверяем и прописываем в исходный код флаги окна
    if (wfDef)
    {
        if (tr_wfMove)
            *res << " flags |= wfMove;\n";
        if (tr_wfGrow)
            *res << " flags |= wfGrow;\n";
        if (tr_wfClose)
            *res << " flags |= wfClose;\n";
        if (tr_wfZoom)
            *res << " flags |= wfZoom;\n";
    }
    forEach(&generateDialogCode, &elem);
    for (int i = 0; i < elem.size(); i++)
        *res << elem[i] << "\n";
    //-- формируем заканчивающий код диалога
    *res << "\n selectNext(false);\n}\n";
}



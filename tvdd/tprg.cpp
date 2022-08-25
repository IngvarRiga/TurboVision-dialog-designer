#include "multilang.h"
#include "tprg.h"
#include "ttrialinputline.h"
#include "ttrialstatictext.h"
#include "ttrialbutton.h"
#include "ttrialradiobuttons.h"
#include "ttrialcheckboxes.h"
#include "ttrialmemo.h"
#include "tcustomwindow.h"
#include "textrainput.h"



TPrg::TPrg() :
    TProgInit(&TPrg::initStatusLine,
              &TPrg::initMenuBar,
              &TPrg::initDeskTop
    )
{
    //-- панель компонентов выводим сразу
    //-- Insert - делает окно не модальным :)
    deskTop->insert(new TComponentDialog());
}

void TPrg::handleEvent(TEvent& event)
{
    if (event.what == evBroadcast)
    {
        if (event.message.command == cm_DisableCursorPaint)
        {
            message(0, evBroadcast, cm_DisableCursorPaint, 0);
            clearEvent(event);
            return;
        }
    }
    TApplication::handleEvent(event);
    if (event.what == evCommand)
    {
        switch (event.message.command)
        {
            case cmAbout:
                deskTop->execView(AboutDialog());
                clearEvent(event);
                break;
            case cmNewDialog:
                deskTop->insert(new TTrialDialog(50, 20, txt_DefaultNewDialogCaption));
                clearEvent(event);
                break;
            case cmLoadJSON:
                {
                    auto fd = new TFileDialog("*.json", txt_dlg_LoadAsCaption, txt_dlg_SaveAsName, fdOpenButton, 100);

                    if (fd != 0 && execView(fd) != cmCancel)
                    {
                        char fileName[MAXPATH];
                        fd->getFileName(fileName);
                        LoadFromJSON(fileName);
                    }
                    destroy(fd);
                    clearEvent(event);
                    break;
                }
            case cmDialogAutoSize:
                {
                    //-- получаем ссылку на диалог
                    auto dlg = (TTrialDialog*)deskTop->current;
                    //-- получаем текущие размеры
                    auto rect = dlg->getBounds();
                    //-- пытаемся выровнять размеры диалога
                    TRect r = TRect(0, 0, 0, 0);
                    dlg->forEach(&scanComponentsSize, &r);
                    if ((r.b.x > 0) && (r.b.y > 0))
                    {
                        rect.b.x = r.b.x + 1;
                        rect.b.y = r.b.y + 1;
                        char dlg_name[StringMaxLen];
                        auto jsn = dlg->DialogToJSON();

                        memset(dlg_name, 0x0, StringMaxLen);
                        memcpy(dlg_name, dlg->getDialogFileName(), strlen(dlg->getDialogFileName()));
                        int xold = jsn[str_size][str_x];
                        int yold = jsn[str_size][str_y];


                        jsn[str_size][str_x] = rect.b.x;
                        jsn[str_size][str_y] = rect.b.y;
                        dlg->setSaved();
                        dlg->close();
                        auto win = LoadDialogJSON(jsn, dlg_name);
                        //-- восстанавливаем положение на экране
                        win->moveTo(rect.a.x, rect.a.y);
                    }
                    clearEvent(event);
                    return;
                }

            case cmDialogSaveToJson:
            case cmDialogSaveToJsonAs:
                //-- передаем команду непосредственно активному элементу
                message(deskTop->current, evBroadcast, event.message.command, NULL);
                clearEvent(event);
                break;
            case cmDialogTest:
                {
                    //-- тестирование активного диалога
                    //-- получаем ссылку на текущий диалог 
                    auto obj = deskTop->current;
                    if (dynamic_cast<TTrialDialog*> (obj))
                    {
                        //-- если это разрабатываемый диалог - тогда отображаем его
                        auto dlg = dynamic_cast<TTrialDialog*> (obj);
                        auto jsn = dlg->DialogToJSON();
                        doTestDialog(jsn);
                    }
                    clearEvent(event);
                    break;
                }
            case cmColorTest:
                deskTop->insert(new TSelectColorDialog());
                clearEvent(event);
                break;
            case cmTest:
                deskTop->execView(TestDialog());
                clearEvent(event);
                break;
            case cmTestWin:
                deskTop->insert(TestEditWindow());
                clearEvent(event);
                break;
            default:
                break;
        }
    }
}

void TPrg::LoadFromJSON(const char* fname)
{
    std::string json_txt;
    std::ifstream src(fname);
    nlohmann::json json;
    try
    {
        //-- здесь и далее, если произойдет ошибка программа должна выдать сообщение, что JSON
        //-- некорректный. 

        src >> json;
        src.close();
        //-- определяем тип ресурса, который содержится в загруженном JSON
        objType typ = json[str_type];
        switch (typ)
        {
            case otDialog:
                //-- при загрузке передаём имя файла, чтобы сохранять файл одним нажатием на F2
                LoadDialogJSON(json, fname);
                break;
            default:
                break;
        }
    }
    catch (...)
    {
        src.close();
        //-- парирование ошибки, если подсунуто непонятно что
        messageBox(txt_error_NotJSON, mfError | mfOKButton);
    }
}

TTrialDialog* TPrg::LoadDialogJSON(nlohmann::json json, const char* fname)
{
    //-- загрузка диалога из JSON файла
    //-- создаём сам диалог
    auto win = new TTrialDialog(json[str_size][str_x], json[str_size][str_y], json[str_caption]);
    //-- устанавливаем имя файла, откуда он был загружен, чтобы при сохранении по F2
    //-- не запрашивать путь сохранения и не выводить диалог
    win->setDialogFileName(fname);
    //-- устанавливаем признак того, что диалог загружен из файла
    win->setLoaded();
    //-- устанавливаем все переменные
    std::string tmp = json[str_class_name];
    win->setClassName(tmp.c_str());
    tmp = json[str_base_class_name];
    win->setBaseClassName(tmp.c_str());
    win->setCentered(json[str_centered]);
    //-- окно может...
    //-- значения указаны для диалога по умолчанию
    win->set_wfDef(json.contains(str_wfDef) ? (bool)json[str_wfDef] : true); //-- перемещаться
    win->set_wfMove(json.contains(str_wfMove) ? (bool)json[str_wfMove] : false); //-- перемещаться
    win->set_wfGrow(json.contains(str_wfGrow) ? (bool)json[str_wfGrow] : false); //-- изменять размеры
    win->set_wfClose(json.contains(str_wfClose) ? (bool)json[str_wfClose] : false); //-- иметь кнопку закрытия
    win->set_wfZoom(json.contains(str_wfZoom) ? (bool)json[str_wfZoom] : false); //-- изменять размеры

    tmp = json[str_caption];
    win->setCaption(tmp.c_str());
    //-- формируем перечень объектов, которые уже вставлены в диалоговое окно
    auto obj = json[str_objects];
    for (int i = 0; i < obj.size(); i++)
        win->insert(object_fromJSON(obj[i]));
    //-- вставляем окно на Desktop
    deskTop->insert(win);
    return win;
}

void TPrg::doTestDialog(nlohmann::json json)
{
    std::string serialized_string = json.dump(2);

    //-- загрузка диалога из JSON файла
    auto win = new TDialog(TRect(0, 0, json[str_size][str_x], json[str_size][str_y]), json[str_caption]);
    win->options |= ofCentered;
    if (json[str_wfDef])
    {
        win->flags = 0x0;
        if (json[str_wfMove])
            win->flags |= wfMove;
        if (json[str_wfGrow])
            win->flags |= wfGrow;
        if (json[str_wfClose])
            win->flags |= wfClose;
        if (json[str_wfZoom])
            win->flags |= wfZoom;
    }
    std::string tmp;
    auto obj = json[str_objects];
    for (int i = 0; i < obj.size(); i++)
        win->insert(object_fromJSON(obj[i], true));
    //-- вставляем окно
    win->selectNext(false);
    deskTop->execView(win);
}

TMenuBar* TPrg::initMenuBar(TRect r)
{

    r.b.y = r.a.y + 1;
    //-- Формирование меню программы. 
    return new TMenuBar(r,
                        //-- первым идёт так называемое - системное меню
                        *new TSubMenu("~\360~", kbAltSpace) +
                        *new TMenuItem(winAboutCapt, cmAbout, kbNoKey) +
                        newLine() +
                        *new TMenuItem(txt_cmExit, cmQuit, kbAltX, hcNoContext, "Alt-X") +
                        //-- перечень реализованных алгоритмов
                        *new TSubMenu(txt_mnu_DialogDesign, kbNoKey) +
                        (TMenuItem&)(
                            *new TMenuItem(txt_mnu_NewDialogWindow, cmNewDialog, kbCtrlN, hcNoContext, "Ctrl-N") +
                            newLine() +
                            *new TMenuItem(txt_mnu_LoadFromJSON, cmLoadJSON, kbF3, hcNoContext, "F3") +
                            newLine() +
                            *new TMenuItem(txt_mnu_SaveToJson, cmDialogSaveToJson, kbF2, hcNoContext, "F2") +
                            *new TMenuItem(txt_mnu_SaveToJsonAs, cmDialogSaveToJsonAs, kbShiftF2, hcNoContext, "Shift+F2") +
                            newLine() +
                            *new TMenuItem(txt_DialogAlignSize, cmDialogAutoSize, kbAltC, hcNoContext, "Alt+C") +
                            *new TMenuItem(txt_DialogTest, cmDialogTest, kbF9, hcNoContext, "F9")
                            ) 
#if _DEBUG
                        +
                        *new TSubMenu(txt_mnu_AlgoritmTest, kbNoKey) +
                        (TMenuItem&)(
                            *new TMenuItem(txt_mnu_ColorSelect, cmColorTest, kbNoKey) +
                            *new TMenuItem("Тест редакторов ввода", cmTest, kbNoKey) +
                            *new TMenuItem("Тест окна редактирования", cmTestWin, kbNoKey)
                            )
#endif
    );

}

/// <summary>
/// Формирование линии статуса приложения
/// </summary>
/// <param name="r"></param>
/// <returns></returns>
TStatusLine* TPrg::initStatusLine(TRect r)
{
    r.a.y = r.b.y - 1;
    return new TStatusLine(r,
                           *new TStatusDef(0, 0xFFFF) +
                           *new TStatusItem(txt_cmStatusExit, kbAltX, cmQuit) +
                           *new TStatusItem(0, kbF10, cmMenu)
    );
}

//------------------------------------------------------------------------------
//-- регион с определением команд

/// <summary>
/// Окно О программе...
/// </summary>
/// <returns></returns>
TDialog* TPrg::AboutDialog()
{
    TCustomDialog* dlg = new TCustomDialog(49, 11, winAboutCapt);
    if (!dlg) return 0;
    dlg->insert(new TStaticText(TRect(3, 2, 47, 3), winAboutText1));
    dlg->insert(new TStaticText(TRect(3, 3, 47, 4), "\003Основано на:"));
    dlg->insert(new TStaticText(TRect(3, 4, 47, 5), "\003Turbo Vision by magiblot"));
    dlg->insert(new TStaticText(TRect(3, 5, 47, 6), "\003JSON C++ by nlohmann"));
    dlg->insert(new TStaticText(TRect(3, 6, 47, 7), "\003(C) Иван Рог"));
    dlg->insert(new TButton(TRect(20, 8, 30, 10), txt_btnOk, cmOK, bfDefault));
    dlg->selectNext(False);
    return dlg;
}

/// <summary>
/// Тест диалог
/// </summary>
/// <returns></returns>
TDialog* TPrg::TestDialog()
{
    TCustomDialog* dlg = new TCustomDialog(49, 11, "Integer test");
    if (!dlg) return 0;
    dlg->insert(new TInputLong(TRect(3, 2, 47, 3), -33, 445, 0));
    dlg->insert(new TInputLong(TRect(3, 4, 47, 5), -33, 44, 0));
    //    dlg->insert(new TInputDouble(TRect(3, 6, 47, 7), 15, -3456.55, 86757865.34));
    dlg->insert(new TButton(TRect(20, 8, 30, 10), txt_btnOk, cmOK, bfDefault));
    dlg->selectNext(False);
    return dlg;
}

TWindow* TPrg::TestEditWindow()
{
    auto win = new TCustomWindow(60, 40, "test");
    if (!win) return 0;
    return win;
}





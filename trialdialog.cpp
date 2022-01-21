#include <strings.h>
#include <stdlib.h>
#define Uses_MsgBox
#define Uses_TFrame
#define Uses_TStreamable
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#include <tvision/tv.h>
#include <tvision/tkeys.h>

#include "trialdialog.h"
#include "common.h"
#include "multilang.h"
#include "tdialogproperties.h"
#include "ttrialstatictext.h"
#include "ttrialinputline.h"
#include "ttrialbutton.h"
#include "ttrialcheckboxes.h"
#include "ttrialradiobuttons.h"
#include "ttriallistbox.h"
#include "tstatictextproperties.h"
#include "tinputlineproperties.h"

const char *_BaseName = "TCustomDialog";
const char *_TypeName = "TNewDialog";

const char * const TTrialDialog::name = "TTrialDialog";

TTrialDialog::TTrialDialog(const int width, const int height, TStringView aTitle, bool sizeable) :
TCustomDialog(width, height, aTitle, sizeable),
TWindowInit(&TCustomDialog::initFrame)
{
    //flags |= wfZoom;
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
    //-- окно можно перемещать за границы зоны видимости для запрета - раскомментарить строку ниже
    //dragMode = dmLimitAll;
    flags |= wfGrow; // это позволяет изменять размеры диалога, хотя по умолчанию опция включена в предке
    memset(BaseName, 0x0, StringMaxLen);
    memset(TypeName, 0x0, StringMaxLen);
    memcpy(BaseName, _BaseName, strlen(_BaseName) + 1);
    memcpy(TypeName, _TypeName, strlen(_TypeName) + 1);

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
    memset(BaseName, 0x0, StringMaxLen);
    memset(TypeName, 0x0, StringMaxLen);
}

void TTrialDialog::setState(ushort aState, bool enable)
{
    //-- вызываем обработчик -установщик унаследованного окна
    TCustomDialog::setState(aState, enable);
}

void TTrialDialog::close()
{
    ushort res;
    if (!DialSaved)
    {
        res = messageBox(txt_SaveDialogQuest, mfConfirmation | mfYesNoCancel);
        if (res == cmYes)
        {
            //-- сохранение диалога
        }
    }
    if (res != cmCancel)
        TCustomDialog::close();

}

void TTrialDialog::handleEvent(TEvent& event)
{
    //-- Обрати внимание, что функция clearEvent(event); вызывается в каждом событии!!!!
    //-- Казалось бы можно сократить код, но тогда при редактировании нескольких окон одновременно
    //-- будут сложности! А так, Drag&Drop срабатывает на то окно, на котором или бросили компонент
    //-- или на том, которое сверху и компонент вставляется правильно.

    
    //-- двойной клик на неиспользуемом пространстве - вызов редактора
    //    if (event.mouse.eventFlags == meDoubleClick)
    if (event.what == evBroadcast)
    {
        switch (event.message.command)
        {
            case cmOption_Dialog:
            {
                //-- вызов редактора свойств диалога
                auto data = new dataTDP();
                memcpy(data->dlgBaseClass, BaseName, strlen(BaseName));
                memcpy(data->dlgClassName, TypeName, strlen(TypeName));
                memcpy(data->dlgCaption, title, strlen(title));
                TDialogProperties *win = new TDialogProperties();
                win->setData(data);
                if (owner->execView(win) == cmOK)
                {
                    win->getData(data);
                    memset(BaseName, 0x0, StringMaxLen);
                    memset(TypeName, 0x0, StringMaxLen);
                    memcpy(BaseName, data->dlgBaseClass, strlen(data->dlgBaseClass));
                    memcpy(TypeName, data->dlgClassName, strlen(data->dlgClassName));
                    //-- с заголовком окна немного позамороченнее --------------
                    delete title;
                    auto lenCapt = strlen(data->dlgCaption) + 1;
                    title = new char[lenCapt];
                    memset((void*) title, 0x0, lenCapt);
                    memcpy((void*) title, data->dlgCaption, lenCapt - 1);
                    //----------------------------------------------------------
                    drawView();
                    frame->drawView();
                }
                delete data;
                destroy(win);
                clearEvent(event);
                break;
            }
            case cmOption_StaticText:
            {
                //-- вызов настройки статического текста
                auto data = new dataTSTP();
                strncpy(data->caption, ((TTrialStaticText*) event.message.infoPtr)->getCaption(), StringMaxLen);
                strncpy(data->class_name, ((TTrialStaticText*) event.message.infoPtr)->getClassName(), StringMaxLen);
                strncpy(data->var_name, ((TTrialStaticText*) event.message.infoPtr)->getVarName(), StringMaxLen);
                data->use_var_name = ((TTrialStaticText*) event.message.infoPtr)->getUsedVarName();

                TStaticTextProperties *win = new TStaticTextProperties();
                win->setData(data);
                if (owner->execView(win) == cmOK)
                {
                    win->getData(data);
                    ((TTrialStaticText*) event.message.infoPtr)->setCaption(data->caption);
                    ((TTrialStaticText*) event.message.infoPtr)->setClassName(data->class_name);
                    ((TTrialStaticText*) event.message.infoPtr)->setVarName(data->var_name);
                    ((TTrialStaticText*) event.message.infoPtr)->setUsedVarName(data->use_var_name);
                    drawView();
                }
                delete data;
                destroy(win);
                clearEvent(event);
                break;
            }
            case cmOption_Button:
            {
                //-- вызов настройки статического кнопки
                clearEvent(event);
                break;
            }
            case cmOption_CheckBoxes:
            {
                //-- вызов настройки 

                clearEvent(event);
                break;
            }
            case cmOption_InputLine:
            {
                //-- вызов настройки статического текста
                auto data = new dataTILP();
                strncpy(data->var_name, ((TTrialInputLine*) event.message.infoPtr)->getVarName(), StringMaxLen);
                data->var_len = ((TTrialInputLine*) event.message.infoPtr)->getVarLen();

                TInputLineProperties *win = new TInputLineProperties();
                win->setData(data);
                if (owner->execView(win) == cmOK)
                {
                    win->getData(data);
                    ((TTrialInputLine*) event.message.infoPtr)->setVarName(data->var_name);
                    ((TTrialInputLine*) event.message.infoPtr)->setVarLen(data->var_len);
                    drawView();
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
            case cmOption_RadioButtons:
            {
                //-- вызов настройки
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
                } else
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
                //-- добавление нового TStaticText
                insert(new TTrialStaticText(TRect(size.x - 13, size.y - 3, size.x - 3, size.y - 2), txt_btnStaticText));
                clearEvent(event);
                break;
            }
            case cm_drp_DropStaticText:
            {
                TPoint tmp;
                tmp.x = ((TPoint*) event.message.infoPtr)->x;
                tmp.y = ((TPoint*) event.message.infoPtr)->y;
                auto lc = makeLocal(tmp);
                auto b = getExtent();
                //-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                //-- чтобы не вставлять то, что не увидится
                if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1)&& (lc.y < b.b.y - 1))
                {
                    //-- добавление нового TStaticText
                    insert(new TTrialStaticText(TRect(lc.x, lc.y, lc.x + 10, lc.y + 1), txt_btnStaticText));
                clearEvent(event);
                }
                break;
            }
            case cm_ed_InsertInputLine:
            {
                //-- добавление нового TInputLine
                insert(new TTrialInputLine(TRect(size.x - 13, size.y - 3, size.x - 3, size.y - 2), 11));
                clearEvent(event);
                break;
            }
            case cm_drp_DropInputLine:
            {
                TPoint tmp;
                tmp.x = ((TPoint*) event.message.infoPtr)->x;
                tmp.y = ((TPoint*) event.message.infoPtr)->y;
                auto lc = makeLocal(tmp);
                auto b = getExtent();
                //-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
                //-- чтобы не вставлять то, что не увидится
                if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1)&& (lc.y < b.b.y - 1))
                {
                    //-- добавление нового TStaticText
                    insert(new TTrialInputLine(TRect(lc.x, lc.y, lc.x + 10, lc.y + 1), 255));
                clearEvent(event);
                }
                break;
            }
            case cm_ed_InsertButton:
            {
                //-- добавление нового TInputLine
                insert(new TTrialButton(TRect(size.x - 13, size.y - 4, size.x - 2, size.y - 2), txt_btnButton));
                clearEvent(event);
                break;
            }
            case cm_ed_InsertCheckBoxes:
            {
                //-- добавление нового TCheckBoxes
                insert(new TTrialCheckBoxes(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr))));
                clearEvent(event);
                break;
            }
            case cm_ed_InsertRadioButtons:
            {
                //-- добавление нового TCheckBoxes
                insert(new TTrialRadioButtons(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr))));
                clearEvent(event);
                break;
            }
            case cm_ed_InsertListBox:
            {
                //-- добавление нового TListBox
                insert(new TTrialListBox(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), 1, 0));
                clearEvent(event);
                break;
            }

            case cmDialogSaveToRes:
            {
                TFileDialog *fd = new TFileDialog("*.dlg", txt_dlg_SaveAsCaption, txt_dlg_SaveAsName, fdOKButton, 100);

                if (fd != 0 && owner->execView(fd) != cmCancel)
                {
                    char fileName[MAXPATH];
                    fd->getFileName(fileName);
                    //fd->helpCtx = hcFOFileOpenDBox;
                    ofpstream os;
                    os.open(fileName);
                    os << this;
                    os.close();
                }
                destroy(fd);
                clearEvent(event);

                break;
            }
            case cmDialogGenCode:
            {
                TFileDialog *fd = new TFileDialog("*.cpp", txt_dlg_SaveCodeAsCaption, txt_dlg_SaveAsName, fdOKButton, 100);

                if (fd != 0 && owner->execView(fd) != cmCancel)
                {
                    char fileName[MAXPATH];
                    fd->getFileName(fileName);
                    char res[8192];
                    memset(res, 0x0, 8192);
                    //-- генерируем код
                    forEach(&generateCode, res);
                    //-- записываем файл
                    ofstream out;
                    out.open(fileName);
                    out << res;
                    out.close();
                }
                destroy(fd);
                clearEvent(event);

                break;
            }
        }

    }
    if (event.what == evKeyDown)
    {
        //-- обработка нажатий служебных клавиш
        if (event.keyDown.keyCode == kbCtrlDel)
        {
            //-- удаление выбранного элемента
            forEach(&deleteSelected, 0);
        }
    }
    TCustomDialog::handleEvent(event);
}

bool TTrialDialog::valid(ushort command)
{
    bool rslt = TCustomDialog::valid(command);
    if (rslt && (command == cmOK))
    {
    }
    return rslt;
}

void TTrialDialog::write(opstream& os)
{
    TCustomDialog::write(os);
    os.writeBytes((void*) BaseName, StringMaxLen);
    os.writeBytes((void*) TypeName, StringMaxLen);
}

void *TTrialDialog::read(ipstream& is)
{
    TCustomDialog::read(is);
    is.readBytes((void*) BaseName, StringMaxLen);
    is.readBytes((void*) TypeName, StringMaxLen);

    //    //-- небольшой момент, при чтении из потока указатель создаётся не нужной нам размерности
    //    //-- а четко по размеру прочитанной строки, что вызывает ошибки при удалении экземпляра
    //    //-- окна и очистке памяти, поэтому читаем и переносим то что нам нужно через буферные переменные
    //    memset(BaseName, 0x0, StringMaxLen);
    //    memset(TypeName, 0x0, StringMaxLen);
    //    char *_BaseName = is.readString();
    //    char *_TypeName = is.readString();
    //    strncpy(BaseName, _BaseName, strlen(_BaseName));
    //    strncpy(TypeName, _TypeName, strlen(_TypeName));
    //--------------------------------------------------------------------------
    return this;
}

TStreamable *TTrialDialog::build()
{
    return new TTrialDialog(streamableInit);
}

TStreamableClass RTrialDialog(
        TTrialDialog::name,
        TTrialDialog::build,
        __DELTA(TTrialDialog)
        );

__link(RWinSizeIndicator)
__link(RWinExtMenu)
__link(RTrialDialog)
__link(RTrialDialogBackground)

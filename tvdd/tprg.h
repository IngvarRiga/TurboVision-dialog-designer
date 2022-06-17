
#ifndef TPRG_H
#define TPRG_H

#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#define Uses_ifpstream
#define Uses_TFileDialog

#include <tvision/tv.h>
#include "trialdialog.h"
#include "tcustomdialog.h"
#include "tselectcolordialog.h"
#include "wstatictext.h"
#include "tcomponentdialog.h"

/// <summary>
/// Основной класс приложения
/// </summary>
class TPrg : public TApplication
{
  public:

    TPrg();

    /// <summary>
    /// Обработка возникающих событий
    /// </summary>
    /// <param name="event"></param>
    virtual void handleEvent(TEvent& event);
    /// <summary>
    /// Инициализация панели меню
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static TMenuBar *initMenuBar(TRect);
    /// <summary>
    /// Инициализация линии статуса
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static TStatusLine *initStatusLine(TRect);
    /// <summary>
    /// Тестирование текущего диалога
    /// </summary>
    /// <param name="json"></param>
    void doTestDialog(nlohmann::json json);

  private:
    /// <summary>
    /// Создание диалога О программе
    /// </summary>
    /// <returns></returns>
    TDialog* AboutDialog();

    TDialog* TestDialog();
    TWindow* TestEditWindow();

    /// <summary>
    /// Загрузка разрабатываемого ресурса из JSON-файла
    /// </summary>
    /// <param name="fname">Имя файла, откуда будет загружаться JSON с описанием ресурса</param>
    void LoadFromJSON(const char* fname);
    /// <summary>
    /// Загрузка диалога из JSON-файла
    /// </summary>
    /// <param name="json">JSON-объект, содержащий описание диалога</param>
    TTrialDialog* LoadDialogJSON(nlohmann::json json, const char* fname = NULL);

};

#endif /* TPRG_H */


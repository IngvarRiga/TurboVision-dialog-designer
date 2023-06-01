#ifndef COMMON_H
#define COMMON_H

#define Uses_TView
//#define Uses_TInputLine
//#define Uses_TFileInputLine
#define Uses_TPoint
#define Uses_TEvent
#define Uses_TGroup
#define Uses_TMenu
#define Uses_TMenuBox
#define Uses_TMenuItem
#define Uses_MsgBox
#define Uses_TSubMenu
#define Uses_TEvent
#define Uses_TFileDialog
#define Uses_TFrame
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#include <tvision/tv.h>
#include <tvision/tkeys.h>

#include "include/nlohmann/json.hpp"
//-- значение имени переменной по умолчанию
#define txt_control "control"
//-- значение имен классов по умолчанию
#define txt_TStaticText "TStaticText"
#define txt_TInputLine "TInputLine"
#define txt_TInputLong "TInputLong"
#define txt_TInputDouble "TInputDouble"
#define txt_TButton "TButton"
#define txt_TCheckBoxes "TCheckBoxes"
#define txt_TRadioButtons "TRadioButtons"
#define txt_TListBox "TListBox"
#define txt_TMemo "TMemo"

//-- определение перечня строковых констант для чтения/записи JSON объектов


#define color_DraggedColor 0xDF //-- цвет компонента при Drag&Drop белый шрифт на фиолетовом поле
#define color_SelectedColor 0x4F //-- цвет компонента при Drag&Drop белый шрифт на красном поле


//-- максимальная длина строки для поля ввода и вообще...
const int StringMaxLen = 255;
//-- максимальная длина генерируемого исходного кода
const int TextMaxLen = 65535;

//-- все команды приложения вынесены в одну точку, чтобы не путаться 

enum class TDDCommand : ushort
{
	//-- перечень общих команд
	cmUnreleased = 0, //-- не реализованная команда
	cmAbout = 10001, //-- о программе
	cmNewDialog, //-- создание нового дизайнера диалогов
	cmKeys, //-- диалог вызова дополнительных ключей объекта
	cmLoadJSON, //-- загрузить ресурс из файла JSON

	cmNewMenu, //-- новое меню
	cmNewPalette, //-- редактор палитр
	cmColorDialog,
	cmColorTest,
	cmTest,
	cmTestWin,
	cmDialogSizeOnOff, //-- Включение / выключение отображения размеров диалога
	cmDialogPosOnOff, //-- Включение / выключение отображения начальной позиции окна
	cmDialogPosSizeOnOff, //-- Включение / выключение отображения всех параметров окна
	//cmDialogSaveToRes, //-- (УДАЛЕНО ИЗ АЛГОРИТМА КАК УСТАРЕВШЕЕ) Сохранить диалог в ресурсах
	cmDialogGenCode, //-- Генерация исходного кода диалога
	cmDialogSaveToJson, //-- Сохранить диалог в ресурсах JSON
	cmDialogAutoSize, //-- Автоматический подбор размера диалога по содержимому
	cmDialogTest, //-- Тестирование разрабатываемого диалога
	cmDialogSaveToJsonAs, //-- Сохранить диалог в ресурсах JSON как...
	//-- вызов диалогов редактирования параметров объектов
	cmOption_Dialog, //-- Вызов окна свойств диалога
	cmOption_StaticText, //-- Вызов окна свойств статического текста
	cmOption_InputLine, //-- Вызов окна свойств строки ввода
	cmOption_Button, //-- Вызов окна свойств кнопки
	cmOption_CheckBoxes, //-- Вызов окна свойств списка check boxes
	cmOption_RadioButtons, //-- Вызов окна свойств списка RadioButtons
	cmOption_ListBox, //-- Вызов окна свойств списка ListBox
	cmOption_Memo, //-- Вызов окна свойств TMemo
	cmOption_InputLong, //-- Вызов окна свойств строки ввода Long чисел
	cmOption_InputDouble, //-- Вызов окна свойств строки ввода Long Double чисел


	cmPopupMenu_Dialog, //-- Вызов контекстного меню диалога

	//-- вставка новых объектов
	//-- Стандартные объекты TurboVision 2.x / Standard objects
	cm_ed_InsertStaticText, //-- вставка TStaticText
	cm_ed_InsertInputLine, //-- вставка TInputLine
	cm_ed_InsertButton, //-- вставка TButton
	cm_ed_InsertCheckBoxes, //-- вставка TCheckBoxes
	cm_ed_InsertRadioButtons, //-- вставка TCheckBoxes
	cm_ed_InsertListBox, //-- вставка TListBox
	cm_ed_InsertMemo, //-- вставка TMemo
	cm_ed_InsertInputLong, //-- вставка TInputLong
	cm_ed_InsertInputDouble, //-- вставка TInputDouble
	cm_ed_Copy, //-- Копировать текущий объект
	cm_ed_Paste, //-- Вставить скопированный объект


	cm_ed_DestroyStaticText, //-- удаление TStaticText
	cm_ed_DestroyInputLine, //-- удаление TInputLine
	cm_ed_DestroyButton, //-- удаление TButton
	cm_ed_DestroyCheckBoxes, //-- удаление TCheckBoxes
	cm_ed_DestroyRadioButtons, //-- удаление TCheckBoxes
	cm_ed_DestroyListBox, //-- удаление TListBox
	cm_ed_DestroyMemo, //-- удаление TMemo
	cm_ed_DestroyInputLong, //-- удаление TInputLong
	cm_ed_DestroyInputDouble, //-- удаление TInputDouble

	//-- "бросание компонентов при переносе"
	cm_drp_DropStaticText, //-- вставка TStaticText
	cm_drp_DropInputLine, //-- вставка TInputLine
	cm_drp_DropButton, //-- вставка TButton
	cm_drp_DropCheckBoxes, //-- вставка TCheckBoxes
	cm_drp_DropRadioButtons, //-- вставка TCheckBoxes
	cm_drp_DropListBox, //-- вставка TListBox
	cm_drp_DropMemo, //-- вставка TMemo
	cm_drp_DropInputLong, //-- вставка TInputLong
	cm_drp_DropInputDouble, //-- вставка TInputDouble

	//-- Команды "тулбару" на создание компонентов
	cm_cmp_BeginDragMode,
	cm_cmp_CreateStaticText,
	cm_cmp_CreateInputLine,
	cm_cmp_CreateButton,
	cm_cmp_CreateCheckBoxes,
	cm_cmp_CreateRadioButtons,
	cm_cmp_CreateListBox,
	cm_cmp_CreateMemo,
	cm_cmp_CreateInputLong,
	cm_cmp_CreateInputDouble,

	//-- служебные команды
	cm_ColorFieldClicked, //-- произошел клик по цветовому полю
	cm_DisableCursorPaint, //-- запретить отрисовку положения мыши на подложке проектируемого диалога
	cm_AlignSize, //-- принудительное выравнивание размера компонента по содержимому (данный алгоритм персонален для каждого компонента в отдельности)

};

//-- Функция реализующая просчёт перемещения или изменения размеров отображаемых объектов
//-- наследников от TView
void DragObject(TView* obj, TEvent event);
//-- Снять признак выбранности со всех компонентов
void unselected(TView* obj, void*);
/// <summary>
/// Генерировать исходный код для диалога
/// </summary>
/// <param name="obj"></param>
/// <param name="val"></param>
void generateDialogCode(TView* obj, void* val);
/// <summary>
/// Генерировать исходный код для диалога в части перечисления всех переменных для заголовочной части
/// </summary>
/// <param name="obj"></param>
/// <param name="val"></param>
void generateDialogHeader(TView* obj, void* val);
/// <summary>
/// Генерировать исходный код для диалога в части директив "Uses_" TurboVision
/// </summary>
/// <param name="obj"></param>
/// <param name="val"></param>
void generateDialogUses(TView* obj, void* val);
/// <summary>
/// Генерировать JSON для диалога 
/// </summary>
/// <param name="obj"></param>
/// <param name="val"></param>
void generateDialogJSON(TView* obj, void* val);
/// <summary>
/// Определение максимальных размеров компонентов в диалоговом окне
/// </summary>
/// <param name="obj"></param>
/// <param name="val"></param>
void scanComponentsSize(TView* obj, void* val);

/// <summary>
/// Создание контекстного меню редактируемого диалогового окна
/// </summary>
/// <returns></returns>
//TMenuBox* dialogMenu();
TMenuItem& dialogMenu();
/// <summary>
/// Перечень типов объектов, которые могут сохраняться в JSON
/// </summary>
enum class objType
{
	//-- Стандартные типы объектов
	otDialog = 0,
	otInputLine = 1000,
	otStaticText,
	otButton,
	otRadioButton,
	otCheckBox,
	otMemo,
	otListBox,
	otInputLong,
	otInputDouble
};

enum class TLineType
{
	lt_InputLine = 0,
	lt_InputLong,
	lt_InputDouble
};

/// <summary>
/// Переменная, содержащая JSON-описание копируемого объекта
/// </summary>
extern nlohmann::json copy_buffer;


extern const char* str_pos;
extern const char* str_size;
extern const char* str_values;
extern const char* str_values_min;
extern const char* str_values_max;
extern const char* str_values_def;
extern const char* str_x;
extern const char* str_y;
extern const char* str_type;
extern const char* str_class_name;
extern const char* str_var_name;
extern const char* str_base_class_name;
extern const char* str_caption;
extern const char* str_centered;
extern const char* str_objects;
extern const char* str_items;
extern const char* str_text;
extern const char* str_variable;
extern const char* str_use_var_name;
extern const char* str_max_len;
//-- окно может...
extern const char* str_wfDef; //-- все значения по умолчанию
extern const char* str_wfMove; //-- перемещаться
extern const char* str_wfGrow; //-- изменять размеры
extern const char* str_wfClose; //-- иметь кнопку закрытия
extern const char* str_wfZoom; //-- изменять размеры

extern const char* str_ofSelectable;
extern const char* str_ofTopSelect;
extern const char* str_ofFirstClick;
extern const char* str_ofFramed;
extern const char* str_ofPreProcess;
extern const char* str_ofPostProcess;
extern const char* str_ofBuffered;
extern const char* str_ofTileable;
extern const char* str_ofCenterX;
extern const char* str_ofCenterY;
extern const char* str_ofValidate;

/// <summary>
/// Создание объекта из JSON-описания.
/// </summary>
/// <param name="json_text">- JSON-описание</param>
/// <param name="test">- если параметр = true, то объект создаётся для тестирования диалога</param>
/// <returns></returns>
TView* object_fromJSON(nlohmann::json json_text, bool test = false);

#endif /* COMMON_H */


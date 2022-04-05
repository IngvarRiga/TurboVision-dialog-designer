#ifndef COMMON_H
#define COMMON_H

#define Uses_TView
#define Uses_TPoint
#define Uses_TEvent
#define Uses_TGroup
#define Uses_TMenu
#define Uses_TMenuBox
#define Uses_TMenuItem
#define Uses_MsgBox
#define Uses_TSubMenu
#define Uses_TStreamable
#define Uses_TStreamableClass
#define Uses_TEvent
#define Uses_TFileDialog

#include <tvision/tv.h>
#include <nlohmann/json.hpp>

//-- значение имени переменной по умолчанию
#define txt_control "control"
//-- значение имен классов по умолчанию
#define txt_TStaticText "TStaticText"
#define txt_TInputLine "TInputLine"
#define txt_TButton "TButton"
#define txt_TCheckBoxes "TCheckBoxes"
#define txt_TRadioButtons "TRadioButtons"
#define txt_TListBox "TListBox"
#define txt_TMemo "TMemo"


#define color_DraggedColor 0xDF //-- цвет компонента при Drag&Drop белый шрифт на фиолетовом поле
#define color_SelectedColor 0x4F //-- цвет компонента при Drag&Drop белый шрифт на красном поле


//-- максимальная длина строки для поля ввода и вообще...
const int StringMaxLen = 255;
//-- максимальная длина генерируемого исходного кода
const int TextMaxLen = 65535;

//-- все команды приложения вынесены в одну точку, чтобы не путаться 

//-- перечень общих команд
const int cmUnreleased = -1; //-- не реализованная команда
const int cmAbout = 10001; //-- о программе
const int cmNewDialog = 10002; //-- создание нового дизайнера диалогов
const int cmLoadDialog = 10003; //-- загрузить диалог из ресурсного файла
const int cmLoadJSON = 10004; //-- загрузить ресурс из файла JSON

const int cmNewMenu = 10094; //-- новое меню
const int cmNewPalette = 10095; //-- редактор палитр
const int cmColorDialog = 10096;
const int cmColorTest = 10097;



const int cmDialogSizeOnOff = 10101; //-- Включение / выключение отображения размеров диалога
const int cmDialogPosOnOff = 10102; //-- Включение / выключение отображения начальной позиции окна
const int cmDialogPosSizeOnOff = 10103; //-- Включение / выключение отображения всех параметров окна
const int cmDialogSaveToRes = 10104; //-- Сохранить диалог в ресурсах
const int cmDialogGenCode = 10105; //-- Генерация исходного кода диалога
const int cmDialogSaveToJson = 10106; //-- Сохранить диалог в ресурсах JSON
const int cmDialogAutoSize = 10107; //-- Автоматический подбор размера диалога по содержимому


//-- вызов диалогов редактирования параметров объектов
const int cmOption_Dialog = 10201; //-- Вызов окна свойств диалога
const int cmOption_StaticText = 10202; //-- Вызов окна свойств статического текста
const int cmOption_InputLine = 10203; //-- Вызов окна свойств строки ввода
const int cmOption_Button = 10204; //-- Вызов окна свойств кнопки
const int cmOption_CheckBoxes = 10205; //-- Вызов окна свойств списка check boxes
const int cmOption_RadioButtons = 10206; //-- Вызов окна свойств списка RadioButtons
const int cmOption_ListBox = 10207; //-- Вызов окна свойств списка ListBox
const int cmOption_Memo = 10208; //-- Вызов окна свойств TMemo


const int cmPopupMenu_Dialog = 10301; //-- Вызов контекстного меню диалога

//-- вставка новых объектов
//-- Стандартные объекты TurboVision 2.x / Standard objects
const int cm_ed_InsertStaticText = 20001; //-- вставка TStaticText
const int cm_ed_InsertInputLine = 20002; //-- вставка TInputLine
const int cm_ed_InsertButton = 20003; //-- вставка TButton
const int cm_ed_InsertCheckBoxes = 20004; //-- вставка TCheckBoxes
const int cm_ed_InsertRadioButtons = 20005; //-- вставка TCheckBoxes
const int cm_ed_InsertListBox = 20006; //-- вставка TListBox
const int cm_ed_InsertMemo = 20007; //-- вставка TMemo
const int cm_ed_Copy = 20008; //-- Копировать текущий объект
const int cm_ed_Paste = 20009; //-- Вставить скопированный объект


const int cm_ed_DestroyStaticText = 20201; //-- удаление TStaticText
const int cm_ed_DestroyInputLine = 20202; //-- удаление TInputLine
const int cm_ed_DestroyButton = 20203; //-- удаление TButton
const int cm_ed_DestroyCheckBoxes = 20204; //-- удаление TCheckBoxes
const int cm_ed_DestroyRadioButtons = 20205; //-- удаление TCheckBoxes
const int cm_ed_DestroyListBox = 20206; //-- удаление TListBox
const int cm_ed_DestroyMemo = 20207; //-- удаление TMemo

//-- "бросание компонентов при переносе"
const int cm_drp_DropStaticText = 20101; //-- вставка TStaticText
const int cm_drp_DropInputLine = 20102; //-- вставка TInputLine
const int cm_drp_DropButton = 20103; //-- вставка TButton
const int cm_drp_DropCheckBoxes = 20104; //-- вставка TCheckBoxes
const int cm_drp_DropRadioButtons = 20105; //-- вставка TCheckBoxes
const int cm_drp_DropListBox = 20106; //-- вставка TListBox
const int cm_drp_DropMemo = 20107; //-- вставка TMemo

//-- Команды "тулбару" на создание компонентов
const int cm_cmp_BeginDragMode = 30000;
const int cm_cmp_CreateStaticText = 30001;
const int cm_cmp_CreateInputLine = 30002;
const int cm_cmp_CreateButton = 30003;
const int cm_cmp_CreateCheckBoxes = 30004;
const int cm_cmp_CreateRadioButtons = 30005;
const int cm_cmp_CreateListBox = 30006;
const int cm_cmp_CreateMemo = 30007;

//-- служебные команды
const int cm_ColorFieldClicked = 60001; //-- произошел клик по цветовому полю
const int cm_DisableCursorPaint = 60002; //-- запретить отрисовку положения мыши на подложке проектируемого диалога
const int cm_AlignSize = 60003; //-- принудительное выравнивание размера компонента по содержимому (данный алгоритм персонален для каждого компонента в отдельности)


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
TMenuBox* dialogMenu();
/// <summary>
/// Перечень типов объектов, которые могут сохраняться в JSON
/// </summary>
enum objType
{
	//-- Стандартные типы объектов
	otDialog = 0, 
	otInputLine=1000,
	otStaticText,
	otButton,
	otRadioButton,
	otCheckBox,
	otMemo,
	otListBox
};




#endif /* COMMON_H */


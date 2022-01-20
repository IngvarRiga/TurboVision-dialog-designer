#ifndef COMMON_H
#define COMMON_H

#define Uses_TView
#define Uses_TPoint
#define Uses_TEvent
#define Uses_TGroup
#include <tvision/tv.h>

//-- значение имени переменной по умолчанию
#define txt_control "control"
//-- значение имен классов по умолчанию
#define txt_TStaticText "TStaticText"
#define txt_TInputLine "TInputLine"
#define txt_TButton "TButton"
#define txt_TCheckBoxes "TCheckBoxes"
#define txt_TRadioButtons "TRadioButtons"
#define txt_TMemo "TMemo"

//-- максимальная длина строки для поля ввода и вообще...
const int StringMaxLen = 255;
//-- максимальная длина строки при генерации кода
const int CodeMaxLen = 1024;

//-- все команды приложения вынесены в одну точку, чтобы не путаться 

//-- перечень общих команд
const int cmUnreleased = -1; //-- не реализованная команда
const int cmAbout = 10001; //-- о программе
const int cmNewDialog = 10002; //-- создание нового дизайнера диалогов
const int cmLoadDialog = 10003; //-- загрузить диалог из ресурсного файла

const int cmNewMenu = 10094; //-- новое меню
const int cmNewPalette = 10095; //-- редактор палитр
const int cmColorDialog = 10096;
const int cmColorTest = 10097;

const int cm_test_ToolWin = 10999; //-- тестирование окна с компонентами

const int cmDialogSizeOnOff = 10101; //-- Включение / выключение отображения отображения размеров диалога
const int cmDialogPosOnOff = 10102; //-- Включение / выключение отображения начальной позиции окна
const int cmDialogPosSizeOnOff = 10103; //-- Включение / выключение отображения всех параметров окна
const int cmDialogSaveToRes = 10104; //-- Сохранить диалог в ресурсах
const int cmDialogGenCode = 10105; //-- Генерация исходного кода диалога

//-- вызов диалогов редактирования параметров объектов
const int cmOption_Dialog = 10201; //-- Вызов окна свойств диалога
const int cmOption_StaticText = 10202; //-- Вызов окна свойств статического текста
const int cmOption_InputLine = 10203; //-- Вызов окна свойств строки ввода
const int cmOption_Button = 10204; //-- Вызов окна свойств кнопки
const int cmOption_CheckBoxes = 10205; //-- Вызов окна свойств списка check boxes
const int cmOption_RadioButtons = 10206; //-- Вызов окна свойств списка RadioButtons
const int cmOption_ListBox = 10207; //-- Вызов окна свойств списка ListBox

//-- вставка новых объектов
//-- Стандартные объекты TurboVision 2.x / Standart objects
const int cm_ed_InsertStaticText = 20001; //-- вставка TStaticText
const int cm_ed_InsertInputLine = 20002; //-- вставка TInputLine
const int cm_ed_InsertButton = 20003; //-- вставка TButton
const int cm_ed_InsertCheckBoxes = 20004; //-- вставка TCheckBoxes
const int cm_ed_InsertRadioButtons = 20005; //-- вставка TCheckBoxes
const int cm_ed_InsertListBox = 20006; //-- вставка TListBox
const int cm_ed_InsertMemo = 20007; //-- вставка TMemo
//-- "бросание компонентов при переносе"
const int cm_drp_DropStaticText = 20101; //-- вставка TStaticText
const int cm_drp_DropInputLine = 20102; //-- вставка TInputLine
const int cm_drp_DropButton = 20103; //-- вставка TButton
const int cm_drp_DropCheckBoxes = 20104; //-- вставка TCheckBoxes
const int cm_drp_DropRadioButtons = 20105; //-- вставка TCheckBoxes
const int cm_drp_DropListBox = 20106; //-- вставка TListBox
const int cm_drp_DropMemo = 20107; //-- вставка TMemo

//-- Команды тулбару на создание комопнентов
const int cm_cmp_BeginDragMode = 30000;
const int cm_cmp_CreateStaticText = 30001;

//-- служебные команды
const int cm_ColorFieldClicked = 60001; //-- произошел клик по цветовому полю

//-- Функция реализующаяя просчет перемещения или изменения размеров отображаемых объектов
//-- наследников от TView
void DragObject(TView *obj, TEvent event);
//-- Снять признак выбранности со всех компонентов
void unselected(TView *obj, void *);
//-- Генерировать исходный код для всех компонентов
void generateCode(TView *obj, void *val);
//-- Удалить выбранный элемент
void deleteSelected(TView *obj, void *val);

#endif /* COMMON_H */


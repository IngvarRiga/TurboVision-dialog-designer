#ifndef MULTILANG_H
#define MULTILANG_H

#ifdef RUS  //-- Default language )))
#define winAboutText1 "\003Дизайнер диалоговых форм TurboVision 2.0 C++"
#define winAboutCapt "О программе..."

//-- тексты меню
#define txt_mnu_DialogDesign "Диалог"
#define txt_mnu_NewDialogWindow "Создать новое диалоговое окно"
#define txt_mnu_LoadFromJSON "Загрузить из файла JSON..."
#define txt_mnu_SaveToRes "(Устарело) Сохранить в файл ресурсов..."
#define txt_mnu_SaveToJson "Сохранить JSON ..."
#define txt_mnu_SaveToJsonAs "Сохранить JSON как ..."
#define txt_mnu_GenCode "Генерировать исходный код..."
#define txt_mnu_StaticText "Статический текст"
#define txt_mnu_Button "Кнопка"
#define txt_mnu_InputLine "Строка ввода"
#define txt_mnu_CheckBoxes "Check Box - список"
#define txt_mnu_RadioButtons "Radio Buttons - список"
#define txt_mnu_ListBox "ListBox"
#define txt_mnu_Memo "Memo"
#define txt_mnu_AlgoritmTest "Тест алгоритмов"
#define txt_mnu_ColorSelect "Тестирование выбора цвета"
#define txt_mnu_ComponentsPanel "Панель компонентов"
#define txt_mnu_cmDelete "Удалить"
#define txt_mnu_Copy "Копировать объект в буфер"
#define txt_mnu_Paste "Вставить из буфера"

//-- дополнительное меню свойств диалога
#define txt_mnu_DlgPropShowPosition "Отображать начальную позицию окна вкл/выкл"
#define txt_mnu_DlgPropShowSize "Отображать размер окна вкл/выкл"
#define txt_mnu_DlgPropShowSizePos "Отображать геометрические параметры окна вкл/выкл"
#define txt_cmExit "Выход"
#define txt_cmStatusExit "~Alt+X~ Выход"

#define txt_btnOk "O~K~"
#define txt_btnCancel "Отмена"
#define txt_btnButton "Кнопка"
#define txt_btnStaticText "StaticText"


#define txt_btnCheck1 "Выбор1"
#define txt_btnCheck2 "Выбор2"

#define txt_ColorTestDlgCaption "Тест цвета"
#define txt_DefaultNewDialogCaption "Новое диалоговое окно"
#define txt_DlgInsertSubMenu "Вставить элемент"
#define txt_SaveDialogQuest "Сохранить созданный диалог?"
#define txt_RewriteDialogFile "\003Файл диалога с таким именем уже существует. Перезаписать его?"
#define txt_PropertyDialogCaption "Свойства TDialog"
#define txt_PropertyStaticText "Свойства TStaticText"
#define txt_PropertyInputLIne "Свойства TInputLine"        
#define txt_PropertyButton "Свойства TButton"   
#define txt_PropertyRadioButtons "Свойства TRadioButtons"   
#define txt_PropertyCheckBoxes "Свойства TCheckBoxes"
#define txt_PropertyMemo "Свойства TMemo"
#define txt_PropertyListBox "Свойства TListBox"
#define txt_PropertyAlignSize "Авторазмер по содержимому"
#define txt_DialogAlignSize "Авторазмер диалога по содержимому"
#define txt_DialogTest "Тестировать диалог"
#define txt_CopyPasteBufferIsEmpty "\003Буфер обмена пуст, вставлять нечего!"


#define txt_pd_ClassName "Имя класса"
#define txt_pd_VariableName "Имя переменной"
#define txt_pd_StringLen "Длина строки"
#define txt_pd_BaseClassName "Имя базового класса"
#define txt_pd_AdditionalProp "Дополнительные свойства"
#define txt_pd_CenteredDialog "Центрировать TDialog на экране"
#define txt_pd_DialogCaption "Заголовок окна"
#define txt_pd_CaptionText "Текст надписи"
#define txt_pd_Text "Текст"
#define txt_pd_ValuesList "Список значений"

#define txt_dlg_SaveAsCaption "Сохранить диалог как..."
#define txt_dlg_SaveCodeAsCaption "Сохранить исходный код диалога как..."
#define txt_dlg_LoadAsCaption "Загрузить диалог из..."
#define txt_dlg_SaveAsName "Название файла"
#define txt_dlg_SaveCodeAsCaption "Сохранить исходный код диалога как..."

#define txt_dlg_GadgetsPanel "D&D"
#define txt_dlg_StaticText "Text"
#define txt_dlg_InputLine "ABC"
#define txt_dlg_Buton "OK"

//-- Сообщения об ошибках
#define txt_error_NotJSON "Ошибка чтения JSON-файла, возможно он содержит ошибки в структуре?"

#endif

#ifdef ENG
#define winAboutText1 "\003Dialog forms designer for TurboVision 2.0 C++"
#define winAboutCapt "About..."

#define txt_mnu_DialogDesign "Dialog"
#define txt_mnu_NewDialogWindow "Create new Dialog window"
#define txt_mnu_LoadFromJSON "Load from JSON..."
#define txt_mnu_SaveToRes "(obsolete) Save to resource file..."
#define txt_mnu_SaveToJson "Save to JSON..."
#define txt_mnu_SaveToJsonAs "Save to JSON as ..."
#define txt_mnu_GenCode "Generate source code..."
#define txt_mnu_StaticText "Static text"
#define txt_mnu_Button "Button"
#define txt_mnu_InputLine "Input line"
#define txt_mnu_CheckBoxes "Check Boxes"
#define txt_mnu_RadioButtons "Radio Buttons"
#define txt_mnu_ListBox "ListBox"
#define txt_mnu_Memo "Memo"
#define txt_mnu_AlgoritmTest "Algorithm test"
#define txt_mnu_ColorSelect "(test) Color select"
#define txt_mnu_ComponentsPanel "Component`s panel"
#define txt_mnu_cmDelete "Delete"
#define txt_mnu_Copy "Copy to buffer"
#define txt_mnu_Paste "Paste from buffer"

//-- additional Dialog Designer menu (click '=' on left border ) 
#define txt_mnu_DlgPropShowPosition "Show window position on/off"
#define txt_mnu_DlgPropShowSize "Show window size on/off"
#define txt_mnu_DlgPropShowSizePos "Show all window geometric params on/off"

#define txt_cmExit "E~x~it"
#define txt_cmStatusExit "~Alt+X~ Exit"

#define txt_btnOk "O~K~"
#define txt_btnCancel "~C~ancel"
#define txt_btnButton "Button"
#define txt_btnStaticText "StaticText"

#define txt_btnCheck1 "Check1"
#define txt_btnCheck2 "Check2"

#define txt_ColorTestDlgCaption "Color test"
#define txt_DefaultNewDialogCaption "New dialog window"
#define txt_DlgInsertSubMenu "Insert gadget"
#define txt_SaveDialogQuest "Save dialog?"
#define txt_RewriteDialogFile "\003Dialog file already exist. Rewrite it?"
#define txt_PropertyDialogCaption "Dialog properties"
#define txt_PropertyStaticText "TStaticText properties"
#define txt_PropertyInputLIne "TInputLine properties"
#define txt_PropertyButton "TButton properties"      
#define txt_PropertyRadioButtons "TRadioButtons properties"   
#define txt_PropertyCheckBoxes "TCheckBoxes properties"
#define txt_PropertyMemo "TMemo properties"
#define txt_PropertyListBox "TListBox properties"
#define txt_PropertyAlignSize "Auto resize"
#define txt_DialogAlignSize "Auto resize dialog window"
#define txt_DialogTest "Test"
#define txt_CopyPasteBufferIsEmpty "\003Copy/Paste buffer is empty!"

#define txt_pd_ClassName "Class name"
#define txt_pd_VariableName "Variable name"
#define txt_pd_StringLen "String length"
#define txt_pd_BaseClassName "Base class name"
#define txt_pd_AdditionalProp "Additional properties"
#define txt_pd_CenteredDialog "Centered TDialog on screen"
#define txt_pd_DialogCaption "Caption"
#define txt_pd_CaptionText "Caption"
#define txt_pd_Text "Text"
#define txt_pd_ValuesList "Values list"

#define txt_dlg_SaveAsCaption "Save dialog as..."
#define txt_dlg_SaveCodeAsCaption "Save source code как..."
#define txt_dlg_LoadAsCaption "Load dialog from..."
#define txt_dlg_SaveAsName "Name"
#define txt_dlg_SaveCodeAsCaption "Save dialog SRC code as..."

#define txt_dlg_GadgetsPanel "D&D"
#define txt_dlg_StaticText "Text"
#define txt_dlg_InputLine "ABC"
#define txt_dlg_Buton "~O~K"

#define txt_error_NotJSON "Error reading JSON, probably consist structure errors?"

#endif

#endif /* MULTILANG_H */


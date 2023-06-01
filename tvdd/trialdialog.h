#ifndef TRIALDIALOG_H
#define TRIALDIALOG_H
#include "tcustomdialog.h"
#include "ttrialdialogbackground.h"
#include "twinsizeindicator.h"
#include "twinextmenu.h"

/// <summary>
/// Описание класса, реализующего диалог в режиме конструктора
/// </summary>
class TTrialDialog : public TCustomDialog
{
public:

	//-- используем упрощенную форму задания размера диалога, поскольку всё равно новый диалог просто центрируется на экране
	TTrialDialog(const int width, const int height, TStringView aTitle, bool sizeable = true);

	virtual ~TTrialDialog();
	virtual bool valid(ushort);
	virtual void close();
	virtual void handleEvent(TEvent& event);
	virtual void setState(ushort aState, bool enable);

	void editDialogProperties();
	void saveDialogToJSON(); //-- сохранение в JSON
	void saveDialogToSrc(); //-- генерация кода диалога
	nlohmann::json DialogToJSON(); //-- генерация кода JSON по диалогу

	//-- установка свойств при загрузке из JSON
	void setClassName(const char* val);
	void setBaseClassName(const char* val);
	void setDialogFileName(const char* val);
	void setCaption(const char* val);
	void setLoaded() { dlg_loaded = true; } //-- установка признака, что диалог загружен из файла
	void SaveDialogAs(); //-- Сохранить диалог как...
	bool getSaved() { return DialSaved; }

	//-- Windows flags
	void set_wfDef(bool val) { wfDef = val; } //-- все значения по умолчанию
	void set_wfMove(bool val) { tr_wfMove = val; } //-- перемещаться
	void set_wfGrow(bool val) { tr_wfGrow = val; } //-- изменять размеры
	void set_wfClose(bool val) { tr_wfClose = val; } //-- иметь кнопку закрытия
	void set_wfZoom(bool val) { tr_wfZoom = val; } //-- изменять размеры

	void setCentered(bool val) { prp_Centered = val; }
	void set_ofSelectable(bool val) { tr_ofSelectable = val; }
	void set_ofTopSelect(bool val) { tr_ofTopSelect = val; }
	void set_ofFirstClick(bool val) { tr_ofFirstClick = val; }
	void set_ofFramed(bool val) { tr_ofFramed = val; }
	void set_ofPreProcess(bool val) { tr_ofPreProcess = val; }
	void set_ofPostProcess(bool val) { tr_ofPostProcess = val; }
	void set_ofBuffered(bool val) { tr_ofBuffered = val; }
	void set_ofTileable(bool val) { tr_ofTileable = val; }
	void set_ofCenterX(bool val) { tr_ofCenterX = val; }
	void set_ofCenterY(bool val) { tr_ofCenterY = val; }
	void set_ofValidate(bool val) { tr_ofValidate = val; }


	void setSaved(bool val = true) { DialSaved = val; }
	const char* getDialogFileName();

private:
	bool DialSaved; //-- признак сохранённости диалога
	bool dlg_loaded; //-- признак того, что диалог был загружен из файла
	//-- окно может...
	bool wfDef; //-- все значения по умолчанию
	bool tr_wfMove; //-- перемещаться
	bool tr_wfGrow; //-- изменять размеры
	bool tr_wfClose; //-- иметь кнопку закрытия
	bool tr_wfZoom; //-- изменять размеры

	bool tr_ofSelectable;
	bool tr_ofTopSelect;
	bool tr_ofFirstClick;
	bool tr_ofFramed;
	bool tr_ofPreProcess;
	bool tr_ofPostProcess;
	bool tr_ofBuffered;
	bool tr_ofTileable;
	bool tr_ofCenterX;
	bool tr_ofCenterY;
	bool tr_ofValidate;
	//bool tr_ofCentered; //-- данный флаг соответствует prp_Centered


	char dlg_file_name[StringMaxLen]; //-- имя файла диалога (при загрузке устанавливается из имени, при создании в имя класса)
	char class_name[StringMaxLen]; //-- название класса диалога
	char base_class_name[StringMaxLen]; //-- название базового класса диалога
	TTrialDialogBackground* Background; //-- хрень отвечающая за отрисовку подложки диалога в режиме конструктора
	TWinSizeIndicator* ind; //-- индикатор размеров окна
	TWinExtMenu* emnu; //-- дополнительное управляющее меню

	//-- СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ
	bool prp_Centered; //-- диалог должен быть отцентрирован

	//-----------------------------------------------------------

	void GenCode(ofstream* res); //-- генерация кода диалога

protected:
	bool isDest; //-- объект находится в стадии уничтожения
};

#endif /* TRIALDIALOG_H */


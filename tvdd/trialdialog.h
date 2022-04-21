#ifndef TRIALDIALOG_H
#define TRIALDIALOG_H
#include "common.h"

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
	static const char* const name;

	//-- используем упрощенную форму задания размера диалога, поскольку всё равно новый диалог просто центрируется на экране
	TTrialDialog(const int width, const int height, TStringView aTitle, bool sizeable = true);

	TTrialDialog(StreamableInit) :
		TCustomDialog(streamableInit),
		TWindowInit(TTrialDialog::initFrame)
	{}

	virtual ~TTrialDialog();
	virtual bool valid(ushort);
	static TStreamable* build();
	virtual void close();
	virtual void handleEvent(TEvent& event);
	virtual void setState(ushort aState, bool enable);
	virtual const char* streamableName() const
	{
		return name;
	}

	void editDialogProperties();
	void saveDialogToJSON(); //-- сохранение в JSON
	void saveDialogToSrc(); //-- генерация кода диалога
	nlohmann::json DialogToJSON(); //-- генерация кода JSON по диалогу

	//-- установка свойств при загрузке из JSON
	void setClassName(const char* val);
	void setBaseClassName(const char* val);
	void setDialogFileName(const char* val);
	void setCentered(bool val);
	void setCaption(const char* val);
	void setLoaded() { dlg_loaded = true; } //-- установка признака, что диалог загружен из файла
	void SaveDialogAs(); //-- Сохранить диалог как...
	bool getSaved() { return DialSaved; }

	void setSaved(bool val = true) { DialSaved = val; }
	const char * getDialogFileName();

private:
	bool DialSaved; //-- признак сохранённости диалога
	bool dlg_loaded; //-- признак того, что  диалог был загружен из файла
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
	virtual void write(opstream&);
	virtual void* read(ipstream&);
};

inline ipstream& operator>>(ipstream& is, TTrialDialog& cl)
{
	return is >> (TStreamable&)cl;
}

inline ipstream& operator>>(ipstream& is, TTrialDialog*& cl)
{
	return is >> (void*&)cl;
}

inline opstream& operator<<(opstream& os, TTrialDialog& cl)
{
	return os << (TStreamable&)cl;
}

inline opstream& operator<<(opstream& os, TTrialDialog* cl)
{
	return os << (TStreamable*)cl;
}

#endif /* TRIALDIALOG_H */


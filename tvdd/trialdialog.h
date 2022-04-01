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
	void saveDialogToRes(); //-- сохранение в потоковых ресурсах TVision
	void saveDialogToJSON(); //-- сохранение в JSON
	void saveDialogToSrc();

	//-- установка свойств при загрузке из JSON
	void setClassName(const char* val);
	void setBaseClassName(const char* val);
	void setCentered(bool val);
	void setCaption(const char* val);

private:
	bool DialSaved; //-- признак сохраненности диалога
	char class_name[StringMaxLen]; //-- название класса диалога
	char base_class_name[StringMaxLen]; //-- название базового класса диалога
	TTrialDialogBackground* Background; //-- хрень отвечающая за отрисовку подложки диалога в режиме конструктора
	//bool GenDefaults;
	TWinSizeIndicator* ind; //-- индикатор размеров окна
	TWinExtMenu* emnu; //-- дополнительное управляющее меню

	//-- СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ
	bool prp_Centered; //-- диалог должен быть отцентрирован

	//-----------------------------------------------------------

	void GenCode(ofstream* res); //-- генерация кода диалога
	void GenJSON(nlohmann::json res); //-- генерация описания объекта в JSON

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


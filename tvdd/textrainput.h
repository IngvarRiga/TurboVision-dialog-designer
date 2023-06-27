
#ifndef TEXTRAINPUT				
#define TEXTRAINPUT

#define Uses_TEvent
#define Uses_TInputLine
#define Uses_TKeys
#define Uses_TRect
#define Uses_MsgBox
#define Uses_TMenuBox
#define Uses_TMenu
#define Uses_TMenuItem
#define Uses_TGroup
#include <tvision/tv.h>
#include <math.h>
#include "multilang.h"

#ifndef _MSC_VER
#include <cfloat>
#endif

#define color_Error 0x4F
#define color_Info 0x47
#define color_Undefined 0x8e

#ifdef RUS
#define txt_set_Minimum "Установить минимум: "
#define txt_set_Maximum "Установить максимум: "
#define txt_set_Default "По умолчанию: "
#define txt_Undefined "«не задано»"
#endif

#ifdef ENG
#define txt_set_Minimum "Set min: "
#define txt_set_Maximum "Set max: "
#define txt_set_Default "Set default: "
#define txt_Undefined "«undefined»"
#endif

enum class TNumericInputCommand : ushort
{
	cmSetMinimum = 11001,
	cmSetMaximum = 11002,
	cmSetDefault = 11003,
};

//-- определение класса TInputLong
class TInputLong : public TInputLine
{
private:
	/// <summary>
	/// Редактируемое значение
	/// </summary>
	long value;
	/// <summary>
	/// Значение по умолчанию
	/// </summary>
	long def_value;
	/// <summary>
	/// Допустимый диапазон изменений значения
	/// </summary>
	long minv, maxv;
	/// <summary>
	/// Допустимо незаданное значение
	/// </summary>
	bool AllowNotDefined;
	/// <summary>
	/// признак, что хранимое значение не определено
	/// </summary>
	bool notDefined;
	/// <summary>
	/// Конвертация строки в Long
	/// </summary>
	/// <param name="tmp"></param>
	/// <param name="out"></param>
	/// <returns>Возвращает true, если конвертация успешна</returns>
	bool convert(const char* tmp, long* out);
	/// <summary>
	/// Отобразить ошибку ввода
	/// </summary>
	void ShowError();
	void draw();

	Boolean canScroll(int delta);
	static const char rightArrow = '\x10';
	static const char leftArrow = '\x11';
	int displayedPos(int pos);
	std::string getDiap();

public:

	TInputLong(const TRect& bounds, long MinValue = LONG_MIN, long MaxValue = LONG_MAX, long DefValue = 0, bool allow_not_def = false);
	~TInputLong() {};
	virtual void handleEvent(TEvent& event);

	/// <summary>
	/// Нормализованное получение данных 
	/// </summary>
	/// <returns></returns>
	long getValue();
	/// <summary>
	/// Нормализованная установка данных
	/// </summary>
	/// <param name="val"></param>
	void setValue(long val);
	/// <summary>
	/// Принудительная установка в неопределённое значение
	/// </summary>
	void setUndefined();
	/// <summary>
	/// Проверка попадания в диапазон допустимых значений
	/// </summary>
	/// <param name="val"> - проверяемое значение</param>
	/// <returns></returns>
	bool CheckValue(long val);
	/// <summary>
	/// Возвращает true, если значение не задано
	/// </summary>
	/// <returns></returns>
	bool isNotDefined();

	void setMaxValue(long val);
	void setMinValue(long val);
	void setDefValue(long val);
	void setAllowNotDefined(bool val);
	long getMaxValue();
	long getMinValue();
	long getDefValue();
	bool getAllowNotDefined();

	// virtual void setState(ushort aState, Boolean enable);
};

//-- определение класса TInputLong
class TInputDouble : public TInputLine
{
private:
	/// <summary>
	/// Редактируемое значение
	/// </summary>
	long double value;
	/// <summary>
	/// Точность представления (после запятой). Не может быть менее 1
	/// </summary>
	int prec;
	/// <summary>
	/// Значение по умолчанию
	/// </summary>
	long double def_value;
	/// <summary>
	/// Допустимый диапазон изменений значения
	/// </summary>
	long double minv, maxv;
	/// <summary>
	/// Допустимо незаданное значение
	/// </summary>
	bool AllowNotDefined;
	/// <summary>
	/// признак, что хранимое значение не определено
	/// </summary>
	bool notDefined;

	/// <summary>
	/// Конвертация строки в Long Double
	/// </summary>
	/// <param name="tmp"></param>
	/// <param name="out"></param>
	/// <returns>Возвращает true, если конвертация успешна</returns>
	bool convert(const char* tmp, long double* out);
	/// <summary>
	/// Отобразить ошибку ввода
	/// </summary>
	void ShowError();
	void draw();

	Boolean canScroll(int delta);
	static const char rightArrow = '\x10';
	static const char leftArrow = '\x11';
	int displayedPos(int pos);
	std::string getDiap();

public:

	TInputDouble(const TRect& bounds, long double MinValue = -FLT_MAX, long double MaxValue = FLT_MAX, long double DefValue = 0.0, uint precision = 5, bool allow_not_def = false);
	~TInputDouble() {};
	virtual void handleEvent(TEvent& event);

	/// <summary>
	/// Нормализованное получение данных 
	/// </summary>
	/// <returns></returns>
	long double getValue() { return value; }
	/// <summary>
	/// Нормализованная установка данных
	/// </summary>
	/// <param name="val"></param>
	void setValue(long double val);
	/// <summary>
    /// Принудительная установка в неопределённое значение
    /// </summary>
	void setUndefined();

	/// <summary>
	/// Проверка попадания в диапазон допустимых значений
	/// </summary>
	/// <param name="val"> - проверяемое значение</param>
	/// <returns></returns>
	bool CheckValue(long double val);
	/// <summary>
	/// Возвращает true, если значение не задано
	/// </summary>
	/// <returns></returns>
	bool isNotDefined();

	void setMaxValue(long double val);
	void setMinValue(long double val);
	void setDefValue(long double val);
	void setAllowNotDefined(bool val);
	long double getMaxValue();
	long double getMinValue();
	long double getDefValue();
	bool getAllowNotDefined();

	std::string convert_to_exp(long double val);
};

#endif


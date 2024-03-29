#include "common.h"
#include "multilang.h"
#include "ttrialstatictext.h"
#include "ttrialinputline.h"
#include "ttrialinputlong.h"
#include "ttrialinputdouble.h"
#include "textrainput.h"
#include "ttrialbutton.h"
#include "ttrialcheckboxes.h"
#include "ttrialradiobuttons.h"
#include "ttriallistbox.h"
#include "ttrialmemo.h"

nlohmann::json copy_buffer;

//-- определение перечня строковых констант для чтения/записи JSON объектов
const char* str_pos = "pos";
const char* str_size = "size";
const char* str_values = "values";
const char* str_values_min = "min";
const char* str_values_max = "max";
const char* str_values_def = "def";
const char* str_values_prec = "prec";
const char* str_allow_not_defined = "allow_not_def";
const char* str_x = "x";
const char* str_y = "y";
const char* str_type = "type";
const char* str_class_name = "class_name";
const char* str_var_name = "var_name";
const char* str_base_class_name = "base_class_name";
const char* str_caption = "caption";
const char* str_centered = "centered";
const char* str_objects = "objects";
const char* str_items = "items";
const char* str_text = "text";
const char* str_variable = "variable";
const char* str_use_var_name = "use_var_name";
const char* str_max_len = "max_len";
//-- окно может...
const char* str_wfDef = "wfDef"; //-- все значения по умолчанию
const char* str_wfMove = "wfMove"; //-- перемещаться
const char* str_wfGrow = "wfGrow"; //-- изменять размеры
const char* str_wfClose = "wfClose"; //-- иметь кнопку закрытия
const char* str_wfZoom = "wfZoom"; //-- изменять размеры

const char* str_ofSelectable = "ofSelectable";
const char* str_ofTopSelect = "ofTopSelect";
const char* str_ofFirstClick = "ofFirstClick";
const char* str_ofFramed = "ofFramed";
const char* str_ofPreProcess = "ofPreProcess";
const char* str_ofPostProcess = "ofPostProcess";
const char* str_ofBuffered = "ofBuffered";
const char* str_ofTileable = "ofTileable";
const char* str_ofCenterX = "ofCenterX";
const char* str_ofCenterY = "ofCenterY";
const char* str_ofValidate = "ofValidate";


void DragObject(TView* obj, TEvent event)
{
	//-- перетаскивание и изменение размеров исключительно левой кнопкой мыши!
	if (event.mouse.buttons == mbLeftButton)
	{
		TPoint MinSz, MaxSz;
		ushort d;
		//-- устанавливаем минимальные границы размера в размер хозяина объекта
		//-- так, чтобы изменение размеров и перемещение не выводило объект
		//-- за границы предка (окна в общем случае)
		auto lims = obj->owner->getExtent();
		lims.grow(-1, -1);
		obj->sizeLimits(MinSz, MaxSz);

		auto r = obj->getBounds();
		auto tx = r.b.x - r.a.x - 1;
		auto ty = r.b.y - r.a.y - 1;
		auto mp = obj->makeLocal(event.mouse.where);

		d = dmDragMove;
		if ((mp.x == tx) && (mp.y == ty))
			d = dmDragGrow;
		obj->dragView(event, obj->dragMode | d, lims, MinSz, MaxSz);
	}
}

void unselected(TView* obj, void*)
{
	obj->setState(sfSelected, false);
}

void generateDialogCode(TView* obj, void* res)
{
	std::vector<std::string>* src = (std::vector<std::string>*) res;
	std::stringstream ss;

	if (dynamic_cast<TTrialStaticText*> (obj))
	{
		TTrialStaticText* to = dynamic_cast<TTrialStaticText*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialButton*> (obj))
	{
		TTrialButton* to = dynamic_cast<TTrialButton*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialInputLong*> (obj))
	{
		TTrialInputLong* to = dynamic_cast<TTrialInputLong*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialInputDouble*> (obj))
	{
		TTrialInputDouble* to = dynamic_cast<TTrialInputDouble*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialInputLine*> (obj))
	{
		TTrialInputLine* to = dynamic_cast<TTrialInputLine*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialCheckBoxes*> (obj))
	{
		TTrialCheckBoxes* to = dynamic_cast<TTrialCheckBoxes*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialListBox*> (obj))
	{
		TTrialListBox* to = dynamic_cast<TTrialListBox*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialRadioButtons*> (obj))
	{
		TTrialRadioButtons* to = dynamic_cast<TTrialRadioButtons*> (obj);
		to->genCode(&ss);
	}
	if (dynamic_cast<TTrialMemo*> (obj))
	{
		TTrialMemo* to = dynamic_cast<TTrialMemo*> (obj);
		to->genCode(&ss);
	}

	std::vector<std::string> elem;
	std::vector<std::string>::iterator iter;
	std::string it;
	while (std::getline(ss, it))
	{
		if (it.length() > 0)
			elem.push_back(it);
	}
	auto cnt = elem.size() - 1;
	//-- cnt - is size_t! для нормальной работы цикла указываем тип int!
	for (int i = (int)cnt; i > -1; i--)
	{
		iter = src->begin();
		src->insert(iter, elem[i]);
	}
}

void generateDialogHeader(TView* obj, void* res)
{
	const char* tab = "    ";
	std::vector<std::string>* src = (std::vector<std::string>*) res;
	std::stringstream ss;

	//if (dynamic_cast<TTrialStaticText*> (obj))
	//{
	//    TTrialStaticText* to = dynamic_cast<TTrialStaticText*> (obj);
	//    to->genCode(&ss);
	//}
	//if (dynamic_cast<TTrialButton*> (obj))
	//{
	//    TTrialButton* to = dynamic_cast<TTrialButton*> (obj);
	//    to->genCode(&ss);
	//}
	if (dynamic_cast<TTrialInputLong*> (obj))
	{
		TTrialInputLong* to = dynamic_cast<TTrialInputLong*> (obj);
		ss << tab << "TInputLong* " << to->getVarName() << ";";
	}
	if (dynamic_cast<TTrialInputDouble*> (obj))
	{
		TTrialInputDouble* to = dynamic_cast<TTrialInputDouble*> (obj);
		ss << tab << "TInputDouble* " << to->getVarName() << ";";
	}
	if (dynamic_cast<TTrialInputLine*> (obj))
	{
		TTrialInputLine* to = dynamic_cast<TTrialInputLine*> (obj);
		ss << tab << "TInputLine* " << to->getVarName() << ";";
	}
	if (dynamic_cast<TTrialCheckBoxes*> (obj))
	{
		TTrialCheckBoxes* to = dynamic_cast<TTrialCheckBoxes*> (obj);
		ss << tab << to->getClassName() << "* " << to->getVarName() << ";";
	}
	if (dynamic_cast<TTrialListBox*> (obj))
	{
		//    TTrialListBox* to = dynamic_cast<TTrialListBox*> (obj);
	//        ss << tab << to->getClassName() << "* " << to->getVarName() << ";";
	}
	if (dynamic_cast<TTrialRadioButtons*> (obj))
	{
		TTrialRadioButtons* to = dynamic_cast<TTrialRadioButtons*> (obj);
		ss << tab << to->getClassName() << "* " << to->getVarName() << ";";
	}
	if (dynamic_cast<TTrialMemo*> (obj))
	{
		TTrialMemo* to = dynamic_cast<TTrialMemo*> (obj);
		ss << tab << "TMemo* " << to->getVarName() << ";";
	}

	std::vector<std::string> elem;
	std::vector<std::string>::iterator iter;
	std::string it;
	while (std::getline(ss, it))
	{
		if (it.length() > 0)
			elem.push_back(it);
	}
	auto cnt = elem.size() - 1;
	//-- cnt - is size_t! для нормальной работы цикла указываем тип int!
	for (int i = (int)cnt; i > -1; i--)
	{
		iter = src->begin();
		src->insert(iter, elem[i]);
	}
}

void generateDialogUses(TView* obj, void* res)
{
	std::vector<std::string>* src = (std::vector<std::string>*) res;
	std::stringstream ss;
	std::string tmp;

	if (dynamic_cast<TTrialStaticText*> (obj))
	{
		tmp = "#define Uses_TStaticText";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
	}
	if (dynamic_cast<TTrialButton*> (obj))
	{
		tmp = "#define Uses_TButton";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
	}
	//-- Следующие 2 компонента не являются частью TurboVision
	//-- поэтому #define Uses_ им не нужны
	//if (dynamic_cast<TTrialInputLong*> (obj))
	//{
	//}
	//if (dynamic_cast<TTrialInputDouble*> (obj))
	//{
	//    TTrialInputDouble* to = dynamic_cast<TTrialInputDouble*> (obj);
	//    to->genCode(&ss);
	//}
	if (dynamic_cast<TTrialInputLine*> (obj))
	{
		tmp = "#define Uses_TInputLine";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
	}
	if (dynamic_cast<TTrialCheckBoxes*> (obj))
	{
		tmp = "#define Uses_TCheckBoxes";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
		tmp = "#define Uses_TSItem";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
	}
	if (dynamic_cast<TTrialListBox*> (obj))
	{
		tmp = "#define Uses_TListBox";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
	}
	if (dynamic_cast<TTrialRadioButtons*> (obj))
	{
		tmp = "#define Uses_TRadioButtons";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
		tmp = "#define Uses_TSItem";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
	}
	if (dynamic_cast<TTrialMemo*> (obj))
	{
		tmp = "#define Uses_TMemo";
		if (std::find(src->begin(), src->end(), tmp) == src->end())
			src->push_back(tmp);
	}
}

void scanComponentsSize(TView* obj, void* val)
{
	TRect* r = (TRect*)val;

	if (dynamic_cast<TTrialStaticText*> (obj))
	{
		//-- используется одновременно для всех наследников TInputLong / TInputDouble
		TTrialStaticText* to = dynamic_cast<TTrialStaticText*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialButton*> (obj))
	{
		TTrialButton* to = dynamic_cast<TTrialButton*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialInputLine*> (obj))
	{
		TTrialInputLine* to = dynamic_cast<TTrialInputLine*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialInputLong*> (obj))
	{
		TTrialInputLong* to = dynamic_cast<TTrialInputLong*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialInputDouble*> (obj))
	{
		TTrialInputDouble* to = dynamic_cast<TTrialInputDouble*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialCheckBoxes*> (obj))
	{
		TTrialCheckBoxes* to = dynamic_cast<TTrialCheckBoxes*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialListBox*> (obj))
	{
		TTrialListBox* to = dynamic_cast<TTrialListBox*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialRadioButtons*> (obj))
	{
		TTrialRadioButtons* to = dynamic_cast<TTrialRadioButtons*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}
	if (dynamic_cast<TTrialMemo*> (obj))
	{
		TTrialMemo* to = dynamic_cast<TTrialMemo*> (obj);
		auto rect = to->getBounds();
		if (rect.b.x > r->b.x)
			r->b.x = rect.b.x;
		if (rect.b.y > r->b.y)
			r->b.y = rect.b.y;
	}

}

void generateDialogJSON(TView* obj, void* _src)
{
	nlohmann::json job;
	std::vector<nlohmann::json>* sav = (std::vector<nlohmann::json>*) _src;

	if (dynamic_cast<TTrialStaticText*> (obj))
	{
		TTrialStaticText* to = dynamic_cast<TTrialStaticText*> (obj);
		sav->push_back(to->genJSON());
	}
	if (dynamic_cast<TTrialButton*> (obj))
	{
		TTrialButton* to = dynamic_cast<TTrialButton*> (obj);
		sav->push_back(to->genJSON());
	}
	if (dynamic_cast<TTrialInputLine*> (obj))
	{
		TTrialInputLine* to = dynamic_cast<TTrialInputLine*> (obj);
		sav->push_back(to->genJSON());
	}
	if (dynamic_cast<TTrialCheckBoxes*> (obj))
	{
		TTrialCheckBoxes* to = dynamic_cast<TTrialCheckBoxes*> (obj);
		sav->push_back(to->genJSON());
	}
	if (dynamic_cast<TTrialInputLong*> (obj))
	{
		TTrialInputLong* to = dynamic_cast<TTrialInputLong*> (obj);
		sav->push_back(to->genJSON());
	}
	if (dynamic_cast<TTrialInputDouble*> (obj))
	{
		TTrialInputDouble* to = dynamic_cast<TTrialInputDouble*> (obj);
		sav->push_back(to->genJSON());
	}
	//if (dynamic_cast<TTrialListBox*> (obj))
	//{
	//	TTrialListBox* to = dynamic_cast<TTrialListBox*> (obj);
	//  sav->push_back(to->genJSON());
	//}
	if (dynamic_cast<TTrialRadioButtons*> (obj))
	{
		TTrialRadioButtons* to = dynamic_cast<TTrialRadioButtons*> (obj);
		sav->push_back(to->genJSON());
	}
	if (dynamic_cast<TTrialMemo*> (obj))
	{
		TTrialMemo* to = dynamic_cast<TTrialMemo*> (obj);
		sav->push_back(to->genJSON());
	}
}

TView* object_fromJSON(nlohmann::json object, bool test)
{
	objType type = object[str_type];
	std::string tmp;
	switch (type)
	{
	case objType::otInputLine:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		if (test)
		{
			auto cmp = new TInputLine(TRect(ax, ay, ax1, ay1), object[str_max_len]);
			return cmp;
		}
		else
		{
			auto cmp = new TTrialInputLine(TRect(ax, ay, ax1, ay1), object[str_max_len]);
			cmp->setData((void*)txt_dlg_InputLine);
			tmp = object[str_var_name];
			cmp->setVarName(tmp.c_str());
			return cmp;
		}
		break;
	}
	case objType::otInputLong:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		long minv = object[str_values][str_values_min];
		long maxv = object[str_values][str_values_max];
		long defv = object[str_values][str_values_def];
		bool allow_not_def = true;
		if (object[str_values].contains(str_allow_not_defined))
			allow_not_def = object[str_values][str_allow_not_defined];

		if (test)
		{
			auto cmp = new TInputLong(TRect(ax, ay, ax1, ay1), minv, maxv, defv, allow_not_def);
			return cmp;
		}
		else
		{
			auto cmp = new TTrialInputLong(TRect(ax, ay, ax1, ay1), object[str_max_len]);
			cmp->setData((void*)txt_dlg_InputLong);
			tmp = object[str_var_name];
			cmp->setVarName(tmp.c_str());
			cmp->setMaxValue(maxv);
			cmp->setMinValue(minv);
			cmp->setDefValue(defv);
			cmp->setAllowNotDefined(allow_not_def);
			return cmp;
		}
		break;
	}
	case objType::otInputDouble:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		long double minv = object[str_values][str_values_min];
		long double maxv = object[str_values][str_values_max];
		long double defv = object[str_values][str_values_def];
		int prec = object[str_values][str_values_prec];
		bool allow_not_def = true;
		if (object[str_values].contains(str_allow_not_defined))
			allow_not_def = object[str_values][str_allow_not_defined];
		if (test)
		{
			auto cmp = new TInputDouble(TRect(ax, ay, ax1, ay1), minv, maxv, defv, prec, allow_not_def);
			return cmp;
		}
		else
		{
			auto cmp = new TTrialInputDouble(TRect(ax, ay, ax1, ay1), object[str_max_len]);
			cmp->setData((void*)txt_dlg_InputDouble);
			tmp = object[str_var_name];
			cmp->setVarName(tmp.c_str());
			cmp->setMaxValue(maxv);
			cmp->setMinValue(minv);
			cmp->setDefValue(defv);
			return cmp;
		}
		break;
	}
	case objType::otStaticText:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		tmp = object[str_text];
		if (test)
		{
			auto cmp = new TStaticText(TRect(ax, ay, ax1, ay1), tmp.c_str());
			return cmp;
		}
		else
		{
			auto cmp = new TTrialStaticText(TRect(ax, ay, ax1, ay1), tmp.c_str());
			cmp->setUsedVarName(object[str_variable][str_use_var_name]);
			tmp = object[str_variable][str_var_name];
			cmp->setVarName(tmp.c_str());
			return cmp;
		}
		break;
	}
	case objType::otButton:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		tmp = object[str_text];
		if (test)
		{
			auto cmp = new TButton(TRect(ax, ay, ax1, ay1), tmp.c_str(), cmOK, bfDefault);
			return cmp;
		}
		else
		{
			auto cmp = new TTrialButton(TRect(ax, ay, ax1, ay1), tmp.c_str());
			cmp->setUsedVarName(object[str_variable][str_use_var_name]);
			tmp = object[str_variable][str_var_name];
			cmp->setVarName(tmp.c_str());
			return cmp;
		}
		break;
	}
	case objType::otRadioButton:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		auto cnt = object[str_items].size();
		tmp = object[str_items][0];
		auto its = new TSItem(TStringView(tmp.c_str()), nullptr);
		auto itsn = its;
		for (int i = 1; i < cnt; i++)
		{
			tmp = object[str_items][i];
			itsn->next = new TSItem(TStringView(tmp.c_str()), nullptr);
			itsn = itsn->next;
		}
		if (test)
		{
			auto cmp = new TRadioButtons(TRect(ax, ay, ax1, ay1), its);
			return cmp;
		}
		else
		{
			auto cmp = new TTrialRadioButtons(TRect(ax, ay, ax1, ay1), its);
			tmp = object[str_var_name];
			cmp->setVarName(tmp.c_str());
			return cmp;
		}
		break;
	}
	case objType::otCheckBox:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		auto cnt = object[str_items].size();
		tmp = object[str_items][0];
		auto its = new TSItem(TStringView(tmp.c_str()), nullptr);
		auto itsn = its;
		for (int i = 1; i < cnt; i++)
		{
			tmp = object[str_items][i];
			itsn->next = new TSItem(TStringView(tmp.c_str()), nullptr);
			itsn = itsn->next;
		}
		if (test)
		{
			auto cmp = new TCheckBoxes(TRect(ax, ay, ax1, ay1), its);
			return cmp;
		}
		else
		{
			auto cmp = new TTrialCheckBoxes(TRect(ax, ay, ax1, ay1), its);
			tmp = object[str_var_name];
			cmp->setVarName(tmp.c_str());
			return (cmp);
		}
		break;
	}
	case objType::otMemo:
	{
		int ax = object[str_pos][str_x];
		int ay = object[str_pos][str_y];
		int ax1 = object[str_pos][str_x]; ax1 += (int)object[str_size][str_x];
		int ay1 = object[str_pos][str_y]; ay1 += (int)object[str_size][str_y];
		if (test)
		{
			auto cmp = new TMemo(TRect(ax, ay, ax1, ay1), nullptr, nullptr, nullptr, 1024);
			return (cmp);
		}
		else
		{
			auto cmp = new TTrialMemo(TRect(ax, ay, ax1, ay1), nullptr, nullptr, nullptr, 0);
			tmp = object[str_var_name];
			cmp->setVarName(tmp.c_str());
			//tmp = object[str_class_name];
			//cmp->setClassName(tmp.c_str());
			return (cmp);
		}
		break;
	}
	case objType::otListBox:
		break;
		//-- здесь это не обслуживается
	case objType::otDialog:
	default:
		break;
	}
	return nullptr;
}

TMenuItem& dialogMenu()
{
	//-- создание контекстного меню диалога
	return
		*new TMenuItem(txt_PropertyDialogCaption, (ushort)TDDCommand::cmOption_Dialog, kbCtrlEnter, hcNoContext, "Ctrl+Enter") +
		newLine() +
		*new TMenuItem(txt_mnu_StaticText, (ushort)TDDCommand::cm_ed_InsertStaticText, kbNoKey) +
		*new TMenuItem(txt_mnu_Button, (ushort)TDDCommand::cm_ed_InsertButton, kbNoKey) +
		*new TMenuItem(txt_mnu_InputLine, (ushort)TDDCommand::cm_ed_InsertInputLine, kbNoKey) +
		*new TMenuItem(txt_mnu_InputLong, (ushort)TDDCommand::cm_ed_InsertInputLong, kbNoKey) +
		*new TMenuItem(txt_mnu_InputDouble, (ushort)TDDCommand::cm_ed_InsertInputDouble, kbNoKey) +
		*new TMenuItem(txt_mnu_RadioButtons, (ushort)TDDCommand::cm_ed_InsertRadioButtons, kbNoKey) +
		*new TMenuItem(txt_mnu_CheckBoxes, (ushort)TDDCommand::cm_ed_InsertCheckBoxes, kbNoKey) +
		*new TMenuItem(txt_mnu_ListBox, (ushort)TDDCommand::cm_ed_InsertListBox, kbNoKey) +
		*new TMenuItem(txt_mnu_Memo, (ushort)TDDCommand::cm_ed_InsertMemo, kbNoKey) +
		newLine() +
		*new TMenuItem(txt_mnu_Paste, (ushort)TDDCommand::cm_ed_Paste, kbNoKey);
}


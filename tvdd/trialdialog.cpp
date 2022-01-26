//#include <strings>
#include <stdlib.h>
#define Uses_MsgBox
#define Uses_TFrame
#define Uses_TStreamable
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream
#include <tvision/tv.h>
#include <tvision/tkeys.h>

#include "trialdialog.h"
#include "common.h"
#include "multilang.h"
#include "tdialogproperties.h"
#include "ttrialstatictext.h"
#include "ttrialinputline.h"
#include "ttrialbutton.h"
#include "ttrialcheckboxes.h"
#include "ttrialradiobuttons.h"
#include "ttriallistbox.h"
#include "tstatictextproperties.h"
#include "tinputlineproperties.h"
#include "tbuttonproperties.h"
#include "tcheckboxesproperties.h"

const char* _class_name = "TNewDialog";
const char* _base_class_name = "TDialog";

const char* const TTrialDialog::name = "TTrialDialog";

TTrialDialog::TTrialDialog(const int width, const int height, TStringView aTitle, bool sizeable) :
	TCustomDialog(width, height, aTitle, sizeable),
	TWindowInit(&TCustomDialog::initFrame)
{
	//flags |= wfZoom;
	//----- ШТРИХОВКА ----------------------------------------------------------
	//-- задаем внутреннюю штриховку разрабатываемого окна так,
	//-- чтобы она НЕ перекрывала границу окна
	TRect inner;
	inner.a.x = clip.a.x + 1;
	inner.a.y = clip.a.y + 1;
	inner.b.x = clip.b.x - 1;
	inner.b.y = clip.b.y - 1;
	Background = new TTrialDialogBackground(inner);
	insert(Background);
	//----- ШТРИХОВКА ----------------------------------------------------------
	setState(sfModal, false); //-- окно НЕ модально, поскольку в режиме разработки
	DialSaved = false;
	//-- окно можно перемещать за границы зоны видимости для запрета - раскомментарить строку ниже
	//dragMode = dmLimitAll;
	flags |= wfGrow; // это позволяет изменять размеры диалога, хотя по умолчанию опция включена в предке
	memset(class_name, 0x0, StringMaxLen);
	memset(base_class_name, 0x0, StringMaxLen);
	memcpy(class_name, _class_name, strlen(_class_name) + 1);
	memcpy(base_class_name, _base_class_name, strlen(_base_class_name) + 1);

	//-- Дополнительное меню в заголовке
	emnu = new TWinExtMenu(TRect(10, size.y - 1, 20, size.y));
	insert(emnu);
	//-- индикатор размеров окна
	ind = new TWinSizeIndicator(TRect(10, size.y - 1, 20, size.y));
	insert(ind);
}

TTrialDialog::~TTrialDialog()
{
	//-- перед удалением обнуляем все буферы
	memset(class_name, 0x0, StringMaxLen);
	memset(base_class_name, 0x0, StringMaxLen);
}

void TTrialDialog::setState(ushort aState, bool enable)
{
	//-- вызываем обработчик -установщик унаследованного окна
	TCustomDialog::setState(aState, enable);
}

void TTrialDialog::editDialogProperties()
{
	auto data = new dataTDP();
	memcpy(data->dlgClassName, class_name, strlen(class_name));
	memcpy(data->dlgBaseClass, base_class_name, strlen(base_class_name));
	memcpy(data->dlgCaption, title, strlen(title));
	TDialogProperties* win = new TDialogProperties();
	win->setData(data);
	if (owner->execView(win) == cmOK)
	{
		win->getData(data);
		memset(class_name, 0x0, StringMaxLen);
		memset(base_class_name, 0x0, StringMaxLen);
		memcpy(class_name, data->dlgClassName, strlen(data->dlgClassName));
		memcpy(base_class_name, data->dlgBaseClass, strlen(data->dlgBaseClass));
		//-- с заголовком окна немного позамороченнее --------------
		delete title;
		auto lenCapt = strlen(data->dlgCaption) + 1;
		title = new char[lenCapt];
		memset((void*)title, 0x0, lenCapt);
		memcpy((void*)title, data->dlgCaption, lenCapt - 1);
		//----------------------------------------------------------
		drawView();
		frame->drawView();
		DialSaved = false;
	}
	delete data;
	destroy(win);
}

void TTrialDialog::close()
{
	ushort res;
	if (DialSaved)
	{
		res = messageBox(txt_SaveDialogQuest, mfConfirmation | mfYesNoCancel);
		if (res == cmYes)
		{
			editDialogProperties();
		}
	}
	if (res != cmCancel)
		TCustomDialog::close();

}

void TTrialDialog::handleEvent(TEvent& event)
{
	//-- Обрати внимание, что функция clearEvent(event); вызывается в каждом событии!!!!
	//-- Казалось бы можно сократить код, но тогда при редактировании нескольких окон одновременно
	//-- будут сложности! А так, Drag&Drop срабатывает на то окно, на котором или бросили компонент
	//-- или на том, которое сверху и компонент вставляется правильно.


	//-- двойной клик на неиспользуемом пространстве - вызов редактора
	//    if (event.mouse.eventFlags == meDoubleClick)
	if (event.what == evBroadcast)
	{
		switch (event.message.command)
		{
			case cmOption_Dialog:
				{
					//-- вызов редактора свойств диалога
					editDialogProperties();
					clearEvent(event);
					break;
				}
			case cmOption_StaticText:
				{
					//-- вызов настройки статического текста
					auto data = new dataTSTP();
					strncpy(data->caption, ((TTrialStaticText*)event.message.infoPtr)->getCaption(), StringMaxLen);
					strncpy(data->class_name, ((TTrialStaticText*)event.message.infoPtr)->getClassName(), StringMaxLen);
					strncpy(data->var_name, ((TTrialStaticText*)event.message.infoPtr)->getVarName(), StringMaxLen);
					data->use_var_name = ((TTrialStaticText*)event.message.infoPtr)->getUsedVarName();

					TStaticTextProperties* win = new TStaticTextProperties();
					win->setData(data);
					if (owner->execView(win) == cmOK)
					{
						win->getData(data);
						((TTrialStaticText*)event.message.infoPtr)->setCaption(data->caption);
						((TTrialStaticText*)event.message.infoPtr)->setClassName(data->class_name);
						((TTrialStaticText*)event.message.infoPtr)->setVarName(data->var_name);
						((TTrialStaticText*)event.message.infoPtr)->setUsedVarName(data->use_var_name);
						drawView();
						DialSaved = false;
					}
					delete data;
					destroy(win);
					clearEvent(event);
					break;
				}
			case cmOption_Button:
				{
					//-- вызов настройки TButton
					auto data = new dataTBTNP();
					strncpy(data->caption, ((TTrialButton*)event.message.infoPtr)->getCaption(), StringMaxLen);
					//strncpy(data->class_name, ((TTrialButton*)event.message.infoPtr)->getClassName(), StringMaxLen);
					strncpy(data->var_name, ((TTrialButton*)event.message.infoPtr)->getVarName(), StringMaxLen);
					data->use_var_name = ((TTrialButton*)event.message.infoPtr)->getUsedVarName();

					TButtonProperties* win = new TButtonProperties();
					win->setData(data);
					if (owner->execView(win) == cmOK)
					{
						win->getData(data);
						((TTrialButton*)event.message.infoPtr)->setCaption(data->caption);
						//((TTrialButton*)event.message.infoPtr)->setClassName(data->class_name);
						((TTrialButton*)event.message.infoPtr)->setVarName(data->var_name);
						((TTrialButton*)event.message.infoPtr)->setUsedVarName(data->use_var_name);
						drawView();
						DialSaved = false;

					}
					delete data;
					destroy(win);
					clearEvent(event);
					break;
				}
			case cmOption_CheckBoxes:
				{
					//-- вызов настройки TButton
					auto data = new dataTCBP();
					strncpy(data->class_name, ((TTrialCheckBoxes*)event.message.infoPtr)->getClassName(), StringMaxLen);
					strncpy(data->var_name, ((TTrialCheckBoxes*)event.message.infoPtr)->getVarName(), StringMaxLen);
					auto itm = ((TTrialCheckBoxes*)event.message.infoPtr)->getItems();
					TCheckBoxesProperties* win = new TCheckBoxesProperties();
					win->setData(data);
					if (owner->execView(win) == cmOK)
					{
						win->getData(data);
						((TTrialCheckBoxes*)event.message.infoPtr)->setClassName(data->class_name);
						((TTrialCheckBoxes*)event.message.infoPtr)->setVarName(data->var_name);
						drawView();
						DialSaved = false;
					}
					delete data;
					destroy(win);
					clearEvent(event);
					break;
				}
			case cmOption_InputLine:
				{
					//-- вызов настройки статического текста
					auto data = new dataTILP();
					strncpy(data->var_name, ((TTrialInputLine*)event.message.infoPtr)->getVarName(), StringMaxLen);
					data->var_len = ((TTrialInputLine*)event.message.infoPtr)->getVarLen();

					TInputLineProperties* win = new TInputLineProperties();
					win->setData(data);
					if (owner->execView(win) == cmOK)
					{
						win->getData(data);
						((TTrialInputLine*)event.message.infoPtr)->setVarName(data->var_name);
						((TTrialInputLine*)event.message.infoPtr)->setVarLen(data->var_len);
						drawView();
						DialSaved = false;
					}
					delete data;
					destroy(win);
					clearEvent(event);
					break;
				}
			case cmOption_ListBox:
				{
					//-- вызов настройки
					clearEvent(event);
					break;
				}
			case cmOption_RadioButtons:
				{
					//-- вызов настройки
					clearEvent(event);
					break;
				}

			case cmDialogPosOnOff:
				{
					ind->setPosInfo(!ind->getPosInfo());
					drawView();
					frame->drawView();
					clearEvent(event);
					break;
				}
			case cmDialogSizeOnOff:
				{
					ind->setSizeInfo(!ind->getSizeInfo());
					frame->drawView();
					clearEvent(event);
					break;
				}
			case cmDialogPosSizeOnOff:
				{
					if (ind->getPosInfo() || ind->getSizeInfo())
					{
						ind->setSizeInfo(false);
						ind->setPosInfo(false);
					}
					else
					{
						ind->setSizeInfo(true);
						ind->setPosInfo(true);
					}
					frame->drawView();
					clearEvent(event);
					break;
				}
			case cm_ed_InsertStaticText:
				{
					//-- добавление нового TStaticText
					auto v = new TTrialStaticText(TRect(size.x - 13, size.y - 3, size.x - 3, size.y - 2), txt_btnStaticText);
					forEach(&unselected, 0);
					v->setSelected(true);
					insert(v);
					DialSaved = false;
					clearEvent(event);
					break;
				}
			case cm_drp_DropStaticText:
				{
					TPoint tmp;
					tmp.x = ((TPoint*)event.message.infoPtr)->x;
					tmp.y = ((TPoint*)event.message.infoPtr)->y;
					clearEvent(event);
					auto lc = makeLocal(tmp);
					auto b = getExtent();
					//-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
					//-- чтобы не вставлять то, что не увидится
					if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
					{
						//-- добавление нового TStaticText
						auto v = new TTrialStaticText(TRect(lc.x, lc.y, lc.x + 10, lc.y + 1), txt_btnStaticText);
						forEach(&unselected, 0);
						v->setSelected(true);
						insert(v);
						DialSaved = false;
					}
					break;
				}
			case cm_ed_InsertInputLine:
				{
					//-- добавление нового TInputLine
					auto v = new TTrialInputLine(TRect(size.x - 13, size.y - 3, size.x - 3, size.y - 2), 11);
					forEach(&unselected, 0);
					v->setSelected(true);
					insert(v);
					DialSaved = false;
					clearEvent(event);
					break;
				}
			case cm_drp_DropInputLine:
				{
					TPoint tmp;
					tmp.x = ((TPoint*)event.message.infoPtr)->x;
					tmp.y = ((TPoint*)event.message.infoPtr)->y;
					clearEvent(event);
					auto lc = makeLocal(tmp);
					auto b = getExtent();
					//-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
					//-- чтобы не вставлять то, что не увидится
					if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
					{
						//-- добавление нового TStaticText
						auto v = new TTrialInputLine(TRect(lc.x, lc.y, lc.x + 10, lc.y + 1), 255);
						forEach(&unselected, 0);
						v->setSelected(true);
						insert(v);
						DialSaved = false;
					}
					break;
				}
			case cm_ed_InsertButton:
				{
					//-- добавление нового TInputLine
					auto v = new TTrialButton(TRect(size.x - 13, size.y - 4, size.x - 2, size.y - 2), txt_btnButton, -1);
					forEach(&unselected, 0);
					v->setSelected(true);
					insert(v);
					clearEvent(event);
					break;
				}
			case cm_drp_DropButton:
				{
					TPoint tmp;
					tmp.x = ((TPoint*)event.message.infoPtr)->x;
					tmp.y = ((TPoint*)event.message.infoPtr)->y;
					clearEvent(event);

					auto lc = makeLocal(tmp);
					auto b = getExtent();
					//-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
					//-- чтобы не вставлять то, что не увидится
					if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
					{
						//-- добавление нового TStaticText
						auto v = new TTrialButton(TRect(lc.x, lc.y, lc.x + 10, lc.y + 2), txt_btnButton, -1);
						forEach(&unselected, 0);
						v->setSelected(true);
						insert(v);
						DialSaved = false;
					}
					break;
				}
			case cm_ed_InsertCheckBoxes:
				{
					//-- добавление нового TCheckBoxes
					insert(new TTrialCheckBoxes(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr))));
					clearEvent(event);
					break;
				}
			case cm_drp_DropCheckBoxes:
				{
					TPoint tmp;
					tmp.x = ((TPoint*)event.message.infoPtr)->x;
					tmp.y = ((TPoint*)event.message.infoPtr)->y;
					clearEvent(event);

					auto lc = makeLocal(tmp);
					auto b = getExtent();
					//-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
					//-- чтобы не вставлять то, что не увидится
					if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
					{
						//-- добавление нового TStaticText
						auto v = new TTrialCheckBoxes(TRect(lc.x, lc.y, lc.x + 12, lc.y + 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr)));
						forEach(&unselected, 0);
						v->setSelected(true);
						insert(v);
						DialSaved = false;
					}
					break;
				}
			case cm_ed_InsertRadioButtons:
				{
					//-- добавление нового TCheckBoxes
					insert(new TTrialRadioButtons(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr))));
					clearEvent(event);
					break;
				}
			case cm_drp_DropRadioButtons:
				{
					TPoint tmp;
					tmp.x = ((TPoint*)event.message.infoPtr)->x;
					tmp.y = ((TPoint*)event.message.infoPtr)->y;
					clearEvent(event);

					auto lc = makeLocal(tmp);
					auto b = getExtent();
					//-- если Drop происходит ВНЕ границ окна - просто игнорируем событие и все
					//-- чтобы не вставлять то, что не увидится
					if ((lc.x >= 1) && (lc.y >= 1) && (lc.x < b.b.x - 1) && (lc.y < b.b.y - 1))
					{
						//-- добавление нового TStaticText
						auto v = new TTrialRadioButtons(TRect(lc.x, lc.y, lc.x + 12, lc.y + 2), new TSItem(txt_btnCheck1, new TSItem(txt_btnCheck2, nullptr)));
						forEach(&unselected, 0);
						v->setSelected(true);
						insert(v);
						DialSaved = false;
					}
					break;
				}
			case cm_ed_InsertListBox:
				{
					//-- добавление нового TListBox
					insert(new TTrialListBox(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), 1, 0));
					clearEvent(event);
					break;
				}
			case cm_drp_DropListBox:
				{
					//-- добавление нового TListBox
					insert(new TTrialListBox(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), 1, 0));
					clearEvent(event);
					break;
				}
			case cm_ed_InsertMemo:
				{
					//-- добавление нового TListBox
					//insert(new TTrialMemo(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), 1, 0));
					clearEvent(event);
					break;
				}
			case cm_drp_DropMemo:
				{
					//-- добавление нового TListBox
					//insert(new TTrialMemo(TRect(size.x - 15, size.y - 4, size.x - 2, size.y - 2), 1, 0));
					clearEvent(event);
					break;
				}

			case cmDialogSaveToRes:
				{
					clearEvent(event);
					saveDialogToRes();
					break;
				}
			case cmDialogGenCode:
				{
					clearEvent(event);
					saveDialogToSrc();
					break;
				}
		}
	}
	//if (event.what | evMouse)
	//{
	//	//-- вызов окна редактирования свойств объекта
	//	if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
	//	{
	//		editDialogProperties();
	//		clearEvent(event);
	//	}
	//}
	//-- переопределяем действия клавиш в режиме разработки
	if (event.what == evKeyDown)
	{
		//-- обработка нажатий служебных клавиш
		if (event.keyDown.keyCode == kbCtrlEnter)
		{
			clearEvent(event);
			editDialogProperties();
			return;
		}
		if (event.keyDown.keyCode == kbCtrlS)
		{
			clearEvent(event);
			saveDialogToRes();
			return;
		}
		if (event.keyDown.keyCode == kbCtrlC)
		{
			clearEvent(event);
			saveDialogToSrc();
			return;
		}
	}

	/*

	//-- Реализованный алгоритм удаления - приводит к непонятным ошибкам, когда попытка удаления одного компонента
	//-- приводит к удалению нескольких сразу. В чем косяк пока не разобрался и времени на это нет
	//-- обработку клавиш повесил непосредственно на сами компоненты
	if (event.what == evKeyDown)
	{
		//-- обработка нажатий служебных клавиш
		if (event.keyDown.keyCode == kbCtrlDel)
		{
			//-- удаление выбранного элемента
			forEach(&deleteSelected, 0);
		}
	}*/
	TCustomDialog::handleEvent(event);
}

void TTrialDialog::saveDialogToRes()
{
	TFileDialog* fd = new TFileDialog("*.dlg", txt_dlg_SaveAsCaption, txt_dlg_SaveAsName, fdOKButton, 100);

	if (fd != 0 && owner->execView(fd) != cmCancel)
	{
		char fileName[MAXPATH];
		fd->getFileName(fileName);
		ofpstream os;
		os.open(fileName);
		os << this;
		os.close();
		DialSaved = true;
	}
	destroy(fd);
}

void TTrialDialog::saveDialogToSrc()
{
	TFileDialog* fd = new TFileDialog("*.cpp", txt_dlg_SaveCodeAsCaption, txt_dlg_SaveAsName, fdOKButton, 100);

	if (fd != 0 && owner->execView(fd) != cmCancel)
	{
		char fileName[MAXPATH];
		fd->getFileName(fileName);
		ofstream out;
		out.open(fileName);
		GenCode(&out);
		out.close();
	}
	destroy(fd);
}



bool TTrialDialog::valid(ushort command)
{
	bool rslt = TCustomDialog::valid(command);
	if (rslt && (command == cmOK))
	{
	}
	return rslt;
}

void TTrialDialog::GenCode(ofstream *res)
{
	char tmp[StringMaxLen];
	memset(tmp, 0x0, StringMaxLen);
	//-- формируем начальный код самого диалога

	/*TDialog::TDialog() :
		TDialog(TRect(7, 2, 61, 16), "Caption"),
		TWindowInit(TDialog::initFrame)
		{

		*/
	auto r = getBounds();
	*res << class_name << "::" << class_name << "() :\n ";
	*res << base_class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << title << "\"),\n";
	*res << " TWindowInit(&" << base_class_name << "::initFrame)\n{";
	//-- генерируем код
	forEach(&generateCode, res);
	//-- формируем заканчивающий код диалога
	*res << "\n selectNext(false);\n}\n";
}


void TTrialDialog::write(opstream& os)
{
	TCustomDialog::write(os);
	os.writeBytes((void*)class_name, StringMaxLen);
	os.writeBytes((void*)base_class_name, StringMaxLen);
}

void* TTrialDialog::read(ipstream& is)
{
	TCustomDialog::read(is);
	is.readBytes((void*)class_name, StringMaxLen);
	is.readBytes((void*)base_class_name, StringMaxLen);

	//    //-- небольшой момент, при чтении из потока указатель создаётся не нужной нам размерности
	//    //-- а четко по размеру прочитанной строки, что вызывает ошибки при удалении экземпляра
	//    //-- окна и очистке памяти, поэтому читаем и переносим то что нам нужно через буферные переменные
	//    memset(BaseName, 0x0, StringMaxLen);
	//    memset(TypeName, 0x0, StringMaxLen);
	//    char *_BaseName = is.readString();
	//    char *_TypeName = is.readString();
	//    strncpy(BaseName, _BaseName, strlen(_BaseName));
	//    strncpy(TypeName, _TypeName, strlen(_TypeName));
	//--------------------------------------------------------------------------
	return this;
}

TStreamable* TTrialDialog::build()
{
	return new TTrialDialog(streamableInit);
}

TStreamableClass RTrialDialog(
	TTrialDialog::name,
	TTrialDialog::build,
	__DELTA(TTrialDialog)
);

__link(RWinSizeIndicator)
__link(RWinExtMenu)
__link(RTrialDialog)
__link(RTrialDialogBackground)
#include "multilang.h"
#include "tprg.h"
#include "common.h"
#include "ttrialinputline.h"
#include "ttrialstatictext.h"
#include "ttrialbutton.h"
#include "ttrialradiobuttons.h"
#include "ttrialcheckboxes.h"
#include "ttrialmemo.h"

TPrg::TPrg() :
	TProgInit(&TPrg::initStatusLine,
			  &TPrg::initMenuBar,
			  &TPrg::initDeskTop
	)
{
	//-- панель компонентов выводим сразу
	//-- Insert - делает окно не модальным :)
	deskTop->insert(new TComponentDialog());
}

void TPrg::handleEvent(TEvent& event)
{
	if (event.what == evBroadcast)
	{
		if (event.message.command == cm_DisableCursorPaint)
		{
			message(0, evBroadcast, cm_DisableCursorPaint, 0);
			clearEvent(event);
			return;
		}
	}
	TApplication::handleEvent(event);
	if (event.what == evCommand)
	{
		switch (event.message.command)
		{
			case cmAbout:
				deskTop->execView(AboutDialog());
				clearEvent(event);
				break;
			case cmNewDialog:
				deskTop->insert(new TTrialDialog(50, 20, txt_DefaultNewDialogCaption));
				clearEvent(event);
				break;
			case cmLoadDialog:
				{
					auto fd = new TFileDialog("*.dlg", txt_dlg_LoadAsCaption, txt_dlg_SaveAsName, fdOpenButton, 100);

					if (fd != 0 && execView(fd) != cmCancel)
					{
						char fileName[MAXPATH];
						fd->getFileName(fileName);
						TTrialDialog* loaded;
						ifpstream is;
						is.open(fileName);
						is >> loaded;
						is.close();
						deskTop->insert(loaded);
					}
					destroy(fd);

					clearEvent(event);
					break;
				}
			case cmLoadJSON:
				//-- не реализовано пока что
				{
					auto fd = new TFileDialog("*.json", txt_dlg_LoadAsCaption, txt_dlg_SaveAsName, fdOpenButton, 100);

					if (fd != 0 && execView(fd) != cmCancel)
					{
						char fileName[MAXPATH];
						fd->getFileName(fileName);
						LoadFromJSON(fileName);
					}
					destroy(fd);
					clearEvent(event);
					break;
				}
			case cmDialogSaveToRes:
				//-- передаем команду непосредственно активному элементу
				message(deskTop->current, evBroadcast, cmDialogSaveToRes, NULL);
				break;
			case cmDialogSaveToJson:
				//-- передаем команду непосредственно активному элементу
				message(deskTop->current, evBroadcast, cmDialogSaveToJson, NULL);
				clearEvent(event);
				break;
			case cmColorTest:
				deskTop->insert(new TSelectColorDialog());
				clearEvent(event);
				break;
			default:

				break;
		}
	}
}

void TPrg::LoadFromJSON(const char* fname)
{
	std::string json_txt;
	std::ifstream src(fname);
	nlohmann::json json;
	try
	{
		//-- здесь и далее, если произойдет ошибка программа должна выдать сообщение, что JSON
		//-- некорректный. 

		src >> json;
		src.close();
		//-- определяем тип ресурса, который содержится в загруженном JSON
		objType typ = json["type"];
		switch (typ)
		{
			case otDialog:
				LoadDialogJSON(json);
				break;
			default:
				break;
		}
	}
	catch (...)
	{
		src.close();
		//-- парирование ошибки, если подсунуто непонятно что
		messageBox(txt_error_NotJSON, mfError | mfOKButton);
	}
}

void TPrg::LoadDialogJSON(nlohmann::json json)
{
	//-- загрузка диалога из JSON файла
	auto win = new TTrialDialog(json["size"]["x"], json["size"]["y"], json["caption"]);
	std::string tmp = json["class_name"];
	win->setClassName(tmp.c_str());
	tmp = json["base_class_name"];
	win->setBaseClassName(tmp.c_str());
	win->setCentered(json["centered"]);
	tmp = json["caption"];
	win->setCaption(tmp.c_str());
	auto obj = json["objects"];
	for (int i = 0; i < obj.size(); i++)
	{
		auto ob = obj[i];
		objType ot = ob["type"];
		switch (ot)
		{
			case otInputLine:
				{
					int ax = ob["pos"]["x"];
					int ay = ob["pos"]["y"];
					int ax1 = ob["pos"]["x"]; ax1 += ob["size"]["x"];
					int ay1 = ob["pos"]["y"]; ay1 += ob["size"]["y"];
					auto cmp = new TTrialInputLine(TRect(ax, ay, ax1, ay1), ob["max_len"]);
					tmp = ob["var_name"];
					cmp->setVarName(tmp.c_str());
					win->insert(cmp);
					break;
				}
			case otStaticText:
				{
					int ax = ob["pos"]["x"];
					int ay = ob["pos"]["y"];
					int ax1 = ob["pos"]["x"]; ax1 += ob["size"]["x"];
					int ay1 = ob["pos"]["y"]; ay1 += ob["size"]["y"];
					tmp = ob["text"];
					auto cmp = new TTrialStaticText(TRect(ax, ay, ax1, ay1), tmp.c_str());
					cmp->setUsedVarName(ob["variable"]["use_var_name"]);
					tmp = ob["variable"]["var_name"];
					cmp->setVarName(tmp.c_str());
					win->insert(cmp);
					break;
				}
			case otButton:
				{
					int ax = ob["pos"]["x"];
					int ay = ob["pos"]["y"];
					int ax1 = ob["pos"]["x"]; ax1 += ob["size"]["x"];
					int ay1 = ob["pos"]["y"]; ay1 += ob["size"]["y"];
					tmp = ob["text"];
					auto cmp = new TTrialButton(TRect(ax, ay, ax1, ay1), tmp.c_str());
					cmp->setUsedVarName(ob["variable"]["use_var_name"]);
					tmp = ob["variable"]["var_name"];
					cmp->setVarName(tmp.c_str());
					win->insert(cmp);
					break;
				}
				break;
			case otRadioButton:
				{
					int ax = ob["pos"]["x"];
					int ay = ob["pos"]["y"];
					int ax1 = ob["pos"]["x"]; ax1 += ob["size"]["x"];
					int ay1 = ob["pos"]["y"]; ay1 += ob["size"]["y"];
					auto cnt = ob["items"].size();
					tmp = ob["items"][0];
					auto its = new TSItem(TStringView(tmp.c_str()), nullptr);
					auto itsn = its;
					for (int i = 1; i < cnt; i++)
					{
						tmp = ob["items"][i];
						itsn->next = new TSItem(TStringView(tmp.c_str()), nullptr);
						itsn = itsn->next;
					}
					auto cmp = new TTrialRadioButtons(TRect(ax, ay, ax1, ay1), its);
					tmp = ob["var_name"];
					cmp->setVarName(tmp.c_str());
					win->insert(cmp);
					break;
				}
			case otCheckBox:
				{
					int ax = ob["pos"]["x"];
					int ay = ob["pos"]["y"];
					int ax1 = ob["pos"]["x"]; ax1 += ob["size"]["x"];
					int ay1 = ob["pos"]["y"]; ay1 += ob["size"]["y"];
					auto cnt = ob["items"].size();
					tmp = ob["items"][0];
					auto its = new TSItem(TStringView(tmp.c_str()), nullptr);
					auto itsn = its;
					for (int i = 1; i < cnt; i++)
					{
						tmp = ob["items"][i];
						itsn->next = new TSItem(TStringView(tmp.c_str()), nullptr);
						itsn = itsn->next;
					}
					auto cmp = new TTrialCheckBoxes(TRect(ax, ay, ax1, ay1), its);
					tmp = ob["var_name"];
					cmp->setVarName(tmp.c_str());
					win->insert(cmp);
					break;
				}
			case otMemo:
				{
					int ax = ob["pos"]["x"];
					int ay = ob["pos"]["y"];
					int ax1 = ob["pos"]["x"]; ax1 += ob["size"]["x"];
					int ay1 = ob["pos"]["y"]; ay1 += ob["size"]["y"];
					tmp = ob["text"];
					auto cmp = new TTrialMemo(TRect(ax, ay, ax1, ay1), nullptr, nullptr, nullptr, 0);
					tmp = ob["var_name"];
					cmp->setVarName(tmp.c_str());
					tmp = ob["class_name"];
					cmp->setClassName(tmp.c_str());
					win->insert(cmp);
					break;
				}
			case otListBox:
				break;
				//-- здесь это не обслуживается
			case otDialog:
			default:
				break;
		}
	}


	//-- вставляем окно
	deskTop->insert(win);
}


TMenuBar* TPrg::initMenuBar(TRect r)
{

	r.b.y = r.a.y + 1;
	//-- Формирование меню программы. 
	return new TMenuBar(r,
						//-- первым идёт так называемое - системное меню
						*new TSubMenu("~\360~", kbAltSpace) +
						*new TMenuItem(winAboutCapt, cmAbout, kbNoKey) +
						newLine() +
						*new TMenuItem(txt_cmExit, cmQuit, kbAltX, hcNoContext, "Alt-X") +
						//-- перечень реализованных алгоритмов
						*new TSubMenu(txt_mnu_Designer, kbNoKey) +
						(TMenuItem&)(
							*new TMenuItem(txt_mnu_NewDialogWindow, cmNewDialog, kbCtrlN, hcNoContext, "Ctrl-N") +
							newLine() +
							*new TMenuItem(txt_mnu_LoadFromResource, cmLoadDialog, kbF3, hcNoContext, "F3") +
							*new TMenuItem(txt_mnu_LoadFromJSON, cmLoadJSON, kbAltF3, hcNoContext, "Alt+F3") +
							newLine() +
							*new TMenuItem(txt_mnu_SaveToRes, cmDialogSaveToRes, kbCtrlS, hcNoContext, "Ctrl+S") +
							*new TMenuItem(txt_mnu_SaveToJson, cmDialogSaveToJson, kbCtrlJ, hcNoContext, "Ctrl+J")

							// +newLine()+
						//* new TMenuItem(txt_mnu_ComponentsPanel, cm_test_ToolWin, kbCtrlF12, hcNoContext, "Ctrl-F12")
							) +
						*new TSubMenu(txt_mnu_AlgoritmTest, kbNoKey) +
						(TMenuItem&)(
							*new TMenuItem(txt_mnu_ColorSelect, cmColorTest, kbNoKey)
							)
	);

}

/// <summary>
/// Формирование линии статуса приложения
/// </summary>
/// <param name="r"></param>
/// <returns></returns>
TStatusLine* TPrg::initStatusLine(TRect r)
{
	r.a.y = r.b.y - 1;
	return new TStatusLine(r,
						   *new TStatusDef(0, 0xFFFF) +
						   *new TStatusItem(txt_cmStatusExit, kbAltX, cmQuit) +
						   *new TStatusItem(0, kbF10, cmMenu)
	);
}

//------------------------------------------------------------------------------
//-- регион с определением команд

/// <summary>
/// Окно О программе...
/// </summary>
/// <returns></returns>
TDialog* TPrg::AboutDialog()
{
	TCustomDialog* dlg = new TCustomDialog(49, 11, winAboutCapt);
	if (!dlg) return 0;
	dlg->insert(new TStaticText(TRect(3, 2, 47, 3), winAboutText1));
	dlg->insert(new TStaticText(TRect(3, 3, 47, 4), "\003Основано на:"));
	dlg->insert(new TStaticText(TRect(3, 4, 47, 5), "\003Turbo Vision by maglibot"));
	dlg->insert(new TStaticText(TRect(3, 5, 47, 6), "\003JSON C++ by nlohmann"));
	dlg->insert(new TStaticText(TRect(3, 6, 47, 7), "\003(C) Иван Рог"));
	dlg->insert(new TButton(TRect(20, 8, 30, 10), txt_btnOk, cmOK, bfDefault));
	dlg->selectNext(False);
	return dlg;
}



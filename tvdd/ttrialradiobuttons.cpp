#include "ttrialradiobuttons.h"
#include "multilang.h"

TTrialRadioButtons::TTrialRadioButtons(const TRect& bounds, TSItem* aStrings) :
    TWrapRadioButtons(bounds, aStrings)
{

    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;

    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TRadioButtons, strlen(txt_TRadioButtons));
}

void TTrialRadioButtons::setState(ushort aState, Boolean enable)
{
    TWrapRadioButtons::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}
nlohmann::json TTrialRadioButtons::genJSON()
{
    nlohmann::json job;
    job[str_type] = objType::otRadioButton;
    auto items = getItems();
    for (int i = 0; i < items->getCount(); i++)
        job[str_items].push_back((char*)items->at(i));
    job[str_var_name] = getVarName();
    auto sz = getBounds();
    //-- начальная позиция
    job[str_pos][str_x] = sz.a.x;
    job[str_pos][str_y] = sz.a.y;
    //-- размеры
    job[str_size][str_x] = sz.b.x - sz.a.x;
    job[str_size][str_y] = sz.b.y - sz.a.y;
    return job;
}

void TTrialRadioButtons::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        message(owner, evBroadcast, (ushort)TDDCommand::cm_DisableCursorPaint, 0);

        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, (ushort)TDDCommand::cmOption_RadioButtons, this);
            clearEvent(event);
        }
        if (event.mouse.buttons == mbRightButton)
            if (event.what == evMouseUp)
            {
                //-- создание контекстного меню диалога
                TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
                                                     new TMenu(
                                                         *new TMenuItem(txt_PropertyRadioButtons, (ushort)TDDCommand::cmOption_RadioButtons, -1, hcNoContext) +
                                                         newLine() +
                                                         *new TMenuItem(txt_mnu_cmDelete, (ushort)TDDCommand::cm_ed_DestroyRadioButtons, kbCtrlDel, hcNoContext)
                                                         + newLine() +
                                                         *new TMenuItem(txt_mnu_Copy, (ushort)TDDCommand::cm_ed_Copy, kbNoKey)
                                                     ), nullptr);

                TPoint tmp;
                tmp.x = event.mouse.where.x;
                tmp.y = event.mouse.where.y;
                clearEvent(event);

                //-- смещаем левую верхнюю точку меню в точку клика мышкой на экране
                auto b = contextMenu->getBounds();
                auto dx = b.b.x - b.a.x;
                auto dy = b.b.y - b.a.y;
                b.a.x = tmp.x;
                b.a.y = tmp.y - 1;
                b.b.x = b.a.x + dx;
                b.b.y = b.a.y + dy;
                contextMenu->setBounds(b);
                //---------------------------------------------------------------------
                auto res = this->owner->owner->execView(contextMenu);
                destroy(contextMenu);
                switch (res)
                {
                    case 0:
                        //-- нет команды
                        break;
                    case (ushort)TDDCommand::cm_ed_DestroyRadioButtons:
                        destroy(this);
                        return;
                        break;
                    case (ushort)TDDCommand::cm_ed_Copy:
                        //-- формируем описание объекта в JSON-строку и запоминаем её в буфере
                        copy_buffer.clear();
                        copy_buffer = genJSON();
                        return;
                        break;
                    default:
                        message(owner, evBroadcast, res, this);
                        break;
                }
            }

        if (event.what == evMouseDown)
        {
            owner->forEach(&unselected, 0);
            setState(sfSelected, true);
            DragObject(this, event);
            clearEvent(event);
        }
    }
    //-- переопределяем действия клавиш в режиме разработки
    if (event.what == evKeyDown)
    {
        //-- обработка нажатий служебных клавиш
        //-- взять текущий объект в буфер обмена
        if (event.keyDown.keyCode == kbCtrlIns)
        {
            clearEvent(event);
            //-- формируем описание объекта в JSON-строку и запоминаем её в буфере
            copy_buffer.clear();
            copy_buffer = genJSON();
            return;
        }
    }

    TWrapRadioButtons::handleEvent(event);
}

void TTrialRadioButtons::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapRadioButtons::sizeLimits(min, max);
    min.x = 5;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}


void TTrialRadioButtons::genCode(void* val)
{
    ofstream* res = (ofstream*)val;

    //-- генерируем код компонента
    auto r = getBounds();
    *res << "\n " << var_name << " = new TRadioButtons(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \n";
    auto itm = getItems();
    auto cnt = itm->getCount();
    for (int i = 0; i < (cnt - 1); i++)
    {
        *res << "   new TSItem(\"" << (char*)itm->at(i) << "\",\n";
    }
    *res << "   new TSItem(\"" << (char*)itm->at(cnt - 1) << "\", 0)";

    for (int i = 0; i < (cnt - 1); i++)
    {
        *res << ")";
    }
    *res << ");";
    *res << "\n insert(" << var_name << ");";
}

char* TTrialRadioButtons::getVarName()
{
    return var_name;
}


void TTrialRadioButtons::setClassName(const char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialRadioButtons::getClassName()
{
    return class_name;
}

void TTrialRadioButtons::setVarName(const char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}


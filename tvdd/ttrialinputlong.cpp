#include "ttrialinputlong.h"
#include "multilang.h"
#include "common.h"

TTrialInputLong::TTrialInputLong(const TRect& bounds, uint aMaxLen, TValidator* aValid) :
    TWrapInputLine(bounds, aMaxLen, aValid)
{
    eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TInputLong, strlen(txt_TInputLong));
    minvalue = LONG_MIN;
    maxvalue = LONG_MAX;
    defvalue = 0;
}

void TTrialInputLong::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        message(owner, evBroadcast, cm_DisableCursorPaint, 0);

        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_InputLong, this);
            clearEvent(event);
        }
        if (event.mouse.buttons == mbRightButton)
            if (event.what == evMouseUp)
            {
                //-- создание контекстного меню диалога
                TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
                                                     new TMenu(
                                                         *new TMenuItem(txt_PropertyInputLong, cmOption_InputLong, -1, hcNoContext) +
                                                         newLine() +
                                                         *new TMenuItem(txt_mnu_cmDelete, cm_ed_DestroyInputLong, kbCtrlDel, hcNoContext) +
                                                         newLine() +
                                                         *new TMenuItem(txt_mnu_Copy, cm_ed_Copy, kbNoKey)
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
                    case cm_ed_DestroyInputLine:
                        destroy(this);
                        return;
                        break;
                    case cm_ed_Copy:
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
        //-- Реакция на клик - выбор текущего объекта
        if (event.what == evMouseDown)
        {
            owner->forEach(&unselected, 0);
            setSelected(true);
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

    TWrapInputLine::handleEvent(event);
}

void TTrialInputLong::setState(ushort aState, Boolean enable)
{
    TWrapInputLine::setState(aState, enable);
    if (aState == sfSelected)
    {
        if (!enable)
            setSelected(enable);
    }
}

void TTrialInputLong::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapInputLine::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    //-- строка ввода занимает только одну строчку!
    max.y = 1;
}
//
//bool TTrialInputLong::isSelected()
//{
//	return Selected;
//}
//
//void TTrialInputLong::setSelected(bool val)
//{
//	if (Selected != val)
//	{
//		Selected = val;
//		drawView();
//	}
//}

void TTrialInputLong::genCode(void* val)
{
    ofstream* res = (ofstream*)val;
    auto r = getBounds();

    //-- генерируем код компонента
    *res << "\n " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), " << minvalue << ", "<< maxvalue << ", " << defvalue << ");";
    *res << "\n insert(" << var_name << ");";

}

char* TTrialInputLong::getVarName()
{
    return var_name;
}

uint TTrialInputLong::getVarLen()
{
    return maxLen;
}
void TTrialInputLong::setClassName(const char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialInputLong::getClassName()
{
    return class_name;
}

void TTrialInputLong::setVarName(const char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}

nlohmann::json TTrialInputLong::genJSON()
{
    nlohmann::json job;
    job[str_type] = otInputLong;
    job[str_max_len] = getVarLen();
    job[str_var_name] = getVarName();
    job[str_class_name] = getClassName();
    auto sz = getBounds();
    //-- начальная позиция
    job[str_pos][str_x] = sz.a.x;
    job[str_pos][str_y] = sz.a.y;
    //-- размеры
    job[str_size][str_x] = sz.b.x - sz.a.x;
    job[str_size][str_y] = sz.b.y - sz.a.y;
    //-- ограничения значения
    job[str_values][str_values_min] = minvalue;
    job[str_values][str_values_max] = maxvalue;
    job[str_values][str_values_def] = defvalue;
    return job;
}


void TTrialInputLong::setVarLen(uint val)
{
    maxLen = val;
}

void TTrialInputLong::setMaxValue(long val)
{
    maxvalue = val;
}
void TTrialInputLong::setMinValue(long val)
{
    minvalue = val;
}
void TTrialInputLong::setDefValue(long val)
{
    defvalue = val;
}

long TTrialInputLong::getMaxValue()
{
    return maxvalue;
}
long TTrialInputLong::getMinValue()
{
    return minvalue;
}
long TTrialInputLong::getDefValue()
{
    return defvalue;
}


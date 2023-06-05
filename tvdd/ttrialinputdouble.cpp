#include "ttrialinputdouble.h"
#include "multilang.h"
#include "common.h"

TTrialInputDouble::TTrialInputDouble(const TRect& bounds, uint aMaxLen, TValidator* aValid) :
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
    strncpy(class_name, txt_TInputDouble, strlen(txt_TInputDouble));
    minvalue = -FLT_MAX;
    maxvalue = FLT_MAX;
    defvalue = 0;
    precision = 8;
}

void TTrialInputDouble::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        message(owner, evBroadcast, (ushort)TDDCommand::cm_DisableCursorPaint, 0);

        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, (ushort)TDDCommand::cmOption_InputDouble, this);
            clearEvent(event);
        }
        if (event.mouse.buttons == mbRightButton)
            if (event.what == evMouseUp)
            {
                //-- создание контекстного меню диалога
                TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
                                                     new TMenu(
                                                         *new TMenuItem(txt_PropertyInputDouble, (ushort)TDDCommand::cmOption_InputDouble, -1, hcNoContext) +
                                                         newLine() +
                                                         *new TMenuItem(txt_mnu_cmDelete, (ushort)TDDCommand::cm_ed_DestroyInputDouble, kbCtrlDel, hcNoContext) +
                                                         newLine() +
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
                    case (ushort)TDDCommand::cm_ed_DestroyInputLine:
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

void TTrialInputDouble::setState(ushort aState, Boolean enable)
{
    TWrapInputLine::setState(aState, enable);
    if (aState == sfSelected)
    {
        if (!enable)
            setSelected(enable);
    }
}

void TTrialInputDouble::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapInputLine::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    //-- строка ввода занимает только одну строчку!
    max.y = 1;
}

void TTrialInputDouble::genCode(void* val)
{
    ofstream* res = (ofstream*)val;
    auto r = getBounds();

    //-- генерируем код компонента
//    std::string minv = convert_to
    *res << "\n " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), " << minvalue << ", "<< maxvalue << ", " << defvalue << ", " << precision << ");";
    *res << "\n insert(" << var_name << ");";

}

char* TTrialInputDouble::getVarName()
{
    return var_name;
}

uint TTrialInputDouble::getVarLen()
{
    return maxLen;
}
void TTrialInputDouble::setClassName(const char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialInputDouble::getClassName()
{
    return class_name;
}

void TTrialInputDouble::setVarName(const char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}

nlohmann::json TTrialInputDouble::genJSON()
{
    nlohmann::json job;
    job[str_type] = objType::otInputDouble;
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
    job[str_values][str_values_prec] = precision;
    return job;
}


void TTrialInputDouble::setVarLen(uint val)
{
    maxLen = val;
}

void TTrialInputDouble::setMaxValue(long double val)
{
    maxvalue = val;
}
void TTrialInputDouble::setMinValue(long double val)
{
    minvalue = val;
}
void TTrialInputDouble::setDefValue(long double val)
{
    defvalue = val;
}

void TTrialInputDouble::setPrecision(int val)
{
    precision = val;
}

long double TTrialInputDouble::getMaxValue()
{
    return maxvalue;
}
long double TTrialInputDouble::getMinValue()
{
    return minvalue;
}
long double TTrialInputDouble::getDefValue()
{
    return defvalue;
}

int TTrialInputDouble::getPrecision()
{
    return precision;
}

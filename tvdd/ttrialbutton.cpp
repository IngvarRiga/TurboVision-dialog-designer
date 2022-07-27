#include "ttrialbutton.h"
#include "multilang.h"
#include "common.h"

TTrialButton::TTrialButton(const TRect& bounds,
                           TStringView aTitle,
                           ushort aCommand,
                           ushort aFlags) :
    TWrapButton(bounds, aTitle, aCommand, aFlags)
{
    eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    //-- заданное имя переменной используется при генерации кода
    usedVarName = false; //-- по умолчанию -выключено!
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TButton, strlen(txt_TButton));

}

nlohmann::json TTrialButton::genJSON()
{
    nlohmann::json job;
    job[str_type] = otButton;
    job[str_text] = getCaption();
    job[str_variable][str_use_var_name] = getUsedVarName();
    job[str_variable][str_var_name] = getVarName();
    auto sz = getBounds();
    //-- начальная позиция
    job[str_pos][str_x] = sz.a.x;
    job[str_pos][str_y] = sz.a.y;
    //-- размеры
    job[str_size][str_x] = sz.b.x - sz.a.x;
    job[str_size][str_y] = sz.b.y - sz.a.y;
    return job;
}


void TTrialButton::setState(ushort aState, Boolean enable)
{
    TWrapButton::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

void TTrialButton::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        message(owner, evBroadcast, cm_DisableCursorPaint, 0);

        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_Button, this);
            clearEvent(event);
        }
        if (event.mouse.buttons == mbRightButton)
            if (event.what == evMouseUp)
            {
                TRect b1;
                std::string s;
                char* cpt;
                int cntu = 0, cntc = 0, g = 0;
                char tmpc[StringMaxLen];
                memset(tmpc, 0x0, StringMaxLen);

                //-- создание контекстного меню диалога
                TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
                                                     new TMenu(
                                                         *new TMenuItem(txt_PropertyButton, cmOption_Button, -1, hcNoContext) +
                                                         *new TMenuItem(txt_PropertyAlignSize, cm_AlignSize, -1, hcNoContext) +
                                                         newLine() +
                                                         *new TMenuItem(txt_mnu_cmDelete, cm_ed_DestroyButton, kbCtrlDel, hcNoContext)
                                                         + newLine() +
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
                    case cm_ed_DestroyButton:
                        destroy(this);
                        return;
                        break;
                    case cm_ed_Copy:
                        //-- формируем описание объекта в JSON-строку и запоминаем её в буфере
                        copy_buffer.clear();
                        copy_buffer = genJSON();
                        return;
                        break;
                    case cm_AlignSize:
                        b1 = getBounds();
                        cpt = getCaption();
                        g = strlen(cpt);
                        for (int i = 0; i < g; i++)
                            if ((short)cpt[i] < 0)
                                cntu++;
                            else
                                cntc++;
                        //-- определяем количество строк
                        b1.b.x = b1.a.x + cntu / 2 + cntc + 4;
                        setBounds(b1);
                        drawView();
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

    TWrapButton::handleEvent(event);
}

void TTrialButton::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapButton::sizeLimits(min, max);
    min.x = 5; //-- минимальная ширина = 5 символов - для одного символа на самой кнопке
    min.y = 2; //-- высота ограничена константой
    max.x -= 2;
    //-- строка ввода занимает только одну строчку!
    max.y = 2;
}

char* TTrialButton::getVarName()
{
    return var_name;
}

char* TTrialButton::getClassName()
{
    return class_name;
}

bool TTrialButton::getUsedVarName()
{
    return usedVarName;
}

void TTrialButton::setVarName(const char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialButton::setClassName(const char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialButton::setUsedVarName(bool val)
{
    usedVarName = val;
}

void TTrialButton::genCode(void* val)
{
    ofstream* res = (ofstream*)val;

    //-- генерируем код компонента
    auto r = getBounds();
    if (usedVarName)
    {
        *res << "\n " << var_name << " = new TButton(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << getCaption() << "\", -1, bfDefault)";
        *res << "\n insert(" << var_name << ");";
    }
    else
    {
        *res << "\n insert(new TButton(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << getCaption() << "\", -1, bfDefault));";
    }
}



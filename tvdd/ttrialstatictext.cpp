#include "ttrialstatictext.h"
#include "multilang.h"


const char* const TTrialStaticText::name = "TTrialStaticText";

TTrialStaticText::TTrialStaticText(const TRect& bounds, TStringView aText) :
    TWrapStaticText(bounds, aText)
{
    eventMask |= 0xFF; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess | ofPostProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    //-- заданное имя переменной используется при генерации кода
    usedVarName = false; //-- по умолчанию -выключено!
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TStaticText, strlen(txt_TStaticText));
}

void TTrialStaticText::setState(ushort aState, Boolean enable)
{
    TView::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

nlohmann::json TTrialStaticText::genJSON()
{
    nlohmann::json job;
    job[str_type] = otStaticText;
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

void TTrialStaticText::handleEvent(TEvent& event)
{

    if (event.what | evMouse)
    {
        message(owner, evBroadcast, cm_DisableCursorPaint, 0);

        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
        {
            clearEvent(event);
            //-- обязательно отсылаем ссылку на редактируемый компонент
            message(owner, evBroadcast, cmOption_StaticText, this);
        }

        if (event.mouse.buttons == mbRightButton)
            if (event.what == evMouseUp)
            {
                std::string s;
                std::vector<std::string> elem;
                TRect b1;
                int maxY = 0, maxX = 0, cnt = 0, cntu = 0, cntc = 0;
                //-- создание контекстного меню диалога
                TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
                                                     new TMenu(
                                                         *new TMenuItem(txt_PropertyStaticText, cmOption_StaticText, -1, hcNoContext) +
                                                         *new TMenuItem(txt_PropertyAlignSize, cm_AlignSize, -1, hcNoContext) +
                                                         newLine() +
                                                         *new TMenuItem(txt_mnu_cmDelete, cm_ed_DestroyStaticText, kbCtrlDel, hcNoContext)
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
                    case cm_ed_DestroyStaticText:
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
                        s = std::string(getCaption());
                        //-- определяем количество строк
                        elem = split(s, '\n');
                        maxY = elem.size() > 0 ? elem.size() : 1;
                        if (elem.size() > 0)
                            for (int i = 0; i < maxY; i++)
                            {
                                cntu = 0;
                                cntc = 0;
                                cnt = elem[i].length();
                                for (int j = 0; j < cnt; j++)
                                    if ((short)elem[i][j] < 0)
                                        cntu++;
                                    else
                                        cntc++;
                                if ((cntu / 2 + cntc) > maxX) maxX = (cntu / 2 + cntc);
                                //if (elem[i].length() > maxX) maxX = elem[i].length();
                            }
                        b1.b.x = b1.a.x + maxX;
                        b1.b.y = b1.a.y + maxY;
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

    TWrapStaticText::handleEvent(event);
}
std::vector<std::string> TTrialStaticText::split(const std::string& s, char delim)
{
    std::vector<std::string> elem;
    std::stringstream ss;
    ss.str(s);
    std::string it;
    while (std::getline(ss, it, delim))
    {
        elem.push_back(it);
    }
    return elem;
}



void TTrialStaticText::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapStaticText::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}

char* TTrialStaticText::getVarName()
{
    return var_name;
}

char* TTrialStaticText::getClassName()
{
    return class_name;
}

bool TTrialStaticText::getUsedVarName()
{
    return usedVarName;
}

void TTrialStaticText::setVarName(const char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialStaticText::setClassName(const char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

void TTrialStaticText::setUsedVarName(bool val)
{
    usedVarName = val;
}

void TTrialStaticText::genCode(void* val)
{
    ofstream* res = (ofstream*)val;

    //-- генерируем код компонента
    auto r = getBounds();
    if (usedVarName)
    {
        *res << "\n " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << text << "\");";
        *res << "\n insert(" << var_name << ");";
    }
    else
    {
        *res << "\n insert(new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), \"" << text << "\"));";
    }
}

TStreamable* TTrialStaticText::build()
{
    return new TTrialStaticText(streamableInit);
}

void TTrialStaticText::write(opstream& os)
{

    TWrapStaticText::write(os);
    os.writeBytes(&usedVarName, sizeof(usedVarName));
    os.writeBytes((void*)var_name, StringMaxLen);
    os.writeBytes((void*)class_name, StringMaxLen);
    os << eventMask << options << dragMode;
}

void* TTrialStaticText::read(ipstream& is)
{
    TWrapStaticText::read(is);
    is.readBytes(&usedVarName, sizeof(usedVarName));
    is.readBytes((void*)var_name, StringMaxLen);
    is.readBytes((void*)class_name, StringMaxLen);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialStaticText(
    TTrialStaticText::name,
    TTrialStaticText::build,
    __DELTA(TTrialStaticText)
);

__link(RWrapStaticText)
__link(RTrialStaticText)



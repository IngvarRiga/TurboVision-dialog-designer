#include "ttrialstatictext.h"
#include "common.h"


const char * const TTrialStaticText::name = "TTrialStaticText";

TTrialStaticText::TTrialStaticText(const TRect& bounds, TStringView aText) :
TWrapStaticText(bounds, aText)
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;
    //-- заданное имя переменной используется при генерации кода
    usedVarName = false; //-- по умолчанию -выключено!
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TStaticText, strlen(txt_TStaticText));
}

void TTrialStaticText::draw()
{
    //-- полностью переопределяем процедуру отрисовки, поскольку в дизайнере нам нужны некоторые спецэффекты
    //TStaticText::draw();

    TColorAttr color;
    Boolean center;
    int i, j, l, p, y;
    TDrawBuffer b;
    char s[256];
    memset(s, 0x0, 256);
    auto f = state;
    if (isSelected())
        color = 0x4f;
    else
        color = getColor(1);
    getText(s);
    l = strlen(s);
    p = 0;
    y = 0;
    center = False;
    while (y < size.y)
    {
        b.moveChar(0, ' ', color, size.x);
        if (p < l)
        {
            if (s[p] == 3)
            {
                center = True;
                ++p;
            }
            i = p;
            int last = i + TText::scroll(TStringView(&s[i], l - i), size.x, False);
            do
            {
                j = p;
                while ((p < l) && (s[p] == ' '))
                    ++p;
                while ((p < l) && (s[p] != ' ') && (s[p] != '\n'))
                    p += TText::next(TStringView(&s[p], l - p));
            } while ((p < l) && (p < last) && (s[p] != '\n'));
            if (p > last)
            {
                if (j > i)
                    p = j;
                else
                    p = last;
            }
            int width = strwidth(TStringView(&s[i], p - i));
            if (center == True)
                j = (size.x - width) / 2;
            else
                j = 0;
            b.moveStr(j, TStringView(&s[i], l - i), color, (ushort) width);
            while ((p < l) && (s[p] == ' '))
                p++;
            if ((p < l) && (s[p] == '\n'))
            {
                center = False;
                p++;
            }
        }
        writeLine(0, y++, size.x, 1, b);
    }

}

void TTrialStaticText::setState(ushort aState, Boolean enable)
{
    TView::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

void TTrialStaticText::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            //-- обязательно отсылаем ссылку на редактируемый компонент
            message(owner, evBroadcast, cmOption_StaticText, this);
            clearEvent(event);
        }
        if (event.what == evMouseDown)
        {
            owner->forEach(&unselected, 0);
            setState(sfSelected, true);
            select();
            DragObject(this, event);
            clearEvent(event);
        }
    }

    TWrapStaticText::handleEvent(event);
}

void TTrialStaticText::sizeLimits(TPoint& min, TPoint& max)
{
    TWrapStaticText::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}

bool TTrialStaticText::isSelected()
{
    return Selected;
}

void TTrialStaticText::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}

void TTrialStaticText::genCode(char *val)
{
    //-- генерируем код компонента
    char tmp[StringMaxLen];
    memset(tmp, 0x0, StringMaxLen);
    if (usedVarName)
    {
        //-- пользователь захотел отдельный объект
        auto nl = "\n auto ";
        auto t = " = new ";
        auto rect = "(TRect(";
        auto zap = ",";
        auto endRect = "), \"";
        auto endcode = "\");";
        auto endGen = "\n insert(";
        auto closeBr = ");";

        strncat(val, nl, strlen(nl));
        strncat(val, var_name, strlen(var_name));
        strncat(val, t, strlen(t));
        strncat(val, class_name, strlen(class_name));
        strncat(val, rect, strlen(rect));


        strncat(val, t, strlen(t));
        auto r = getBounds();
        itoa(r.a.x, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        strncat(val, zap, strlen(zap));
        memset(tmp, 0x0, StringMaxLen);

        itoa(r.a.y, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        strncat(val, zap, strlen(zap));
        memset(tmp, 0x0, StringMaxLen);

        itoa(r.b.x, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        strncat(val, zap, strlen(zap));
        memset(tmp, 0x0, StringMaxLen);

        itoa(r.b.y, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        memset(tmp, 0x0, StringMaxLen);

        strncat(val, endRect, strlen(endRect));
        getText(tmp);
        strncat(val, tmp, strlen(tmp));
        memset(tmp, 0x0, StringMaxLen);
        strncat(val, endcode, strlen(endcode));

        strncat(val, endGen, strlen(endGen));
        strncat(val, var_name, strlen(var_name));
        strncat(val, closeBr, strlen(closeBr));

    } else
    {
        //-- обходимся без переменных, сразу вставка
        auto t = "\n insert(new ";
        auto rect = "(TRect(";
        auto zap = ",";
        auto endRect = "), \"";
        auto endcode = "\"));";

        strncat(val, t, strlen(t));
        strncat(val, class_name, strlen(class_name));
        strncat(val, rect, strlen(rect));

        auto r = getBounds();
        itoa(r.a.x, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        strncat(val, zap, strlen(zap));
        memset(tmp, 0x0, StringMaxLen);

        itoa(r.a.y, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        strncat(val, zap, strlen(zap));
        memset(tmp, 0x0, StringMaxLen);

        itoa(r.b.x, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        strncat(val, zap, strlen(zap));
        memset(tmp, 0x0, StringMaxLen);

        itoa(r.b.y, tmp, 10);
        strncat(val, tmp, strlen(tmp));
        memset(tmp, 0x0, StringMaxLen);

        strncat(val, endRect, strlen(endRect));
        getText(tmp);
        strncat(val, tmp, strlen(tmp));
        memset(tmp, 0x0, StringMaxLen);
        strncat(val, endcode, strlen(endcode));
    }
}

TStreamable *TTrialStaticText::build()
{
    return new TTrialStaticText(streamableInit);
}

void TTrialStaticText::write(opstream& os)
{

    TWrapStaticText::write(os);
    os.writeBytes(&usedVarName, sizeof (usedVarName));
    os.writeBytes((void *) var_name, StringMaxLen);
    os.writeBytes((void *) class_name, StringMaxLen);
    os << eventMask << options << dragMode;
}

void *TTrialStaticText::read(ipstream& is)
{
    TWrapStaticText::read(is);
    is.readBytes(&usedVarName, sizeof (usedVarName));
    is.readBytes((void *) var_name, StringMaxLen);
    is.readBytes((void *) class_name, StringMaxLen);
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



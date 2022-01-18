#include "wstatictext.h"

#define cpStaticText "\x06"

const char * const TWrapStaticText::name = "TWrapStaticText";

TWrapStaticText::TWrapStaticText(const TRect& bounds, TStringView aText) noexcept :
TView(bounds)
{
    growMode |= gfFixed;
    memset(text, 0x0, StringMaxLen);
    strncpy(text, aText.data(), StringMaxLen);
    eventClick = false;
}

TWrapStaticText::TWrapStaticText(const TRect& bounds, TStringView aText, bool click) noexcept :
TView(bounds)
{
    growMode |= gfFixed;
    memset(text, 0x0, StringMaxLen);
    strncpy(text, aText.data(), StringMaxLen);
    eventClick = click;
}

void TWrapStaticText::draw()
{
    TColorAttr color;
    Boolean center;
    int i, j, l, p, y;
    TDrawBuffer b;
    char s[256];

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

TPalette& TWrapStaticText::getPalette() const
{
    static TPalette palette(cpStaticText, sizeof ( cpStaticText) - 1);
    return palette;
}

void TWrapStaticText::getText(char *s)
{
    if (text == 0)
        *s = EOS;
    else
    {
        strncpy(s, text, 255);
        s[255] = EOS;
    }
}

void TWrapStaticText::setCaption(char *val)
{
    memset(text, 0x0, StringMaxLen);
    strncpy(text, val, StringMaxLen);
    drawView();
}

char* TWrapStaticText::getCaption()
{
    return text;
}

//-- ... используемый при обычной отрисовке текст

void TWrapStaticText::setWColor(ushort val)
{
}

ushort TWrapStaticText::getWColor()
{
    return 0x0;
}

void TWrapStaticText::handleEvent(TEvent& event)
{
    if (eventClick)
    {
        if (event.what | evMouse)
        {
            //-- Реакция на клик - сообщение о создании перетаскиваемого объекта
            if ((event.mouse.buttons == mbLeftButton) &&(event.what == evMouseDown))
            {
                //-- берем координаты клика мышкой в глобальных координатах
                auto pt = event.mouse.where;
                //-- обязательно отсылаем ссылку на редактируемый компонент
                message(owner, evBroadcast, cm_cmp_CreateStaticText, &pt);
                clearEvent(event);
            }
        }
    }
    if (eventDragged)
    {
        if (event.what | evMouse)
        {
            if (event.what == mbLeftButton)
            {
                //event.mouse.buttons = mbLeftButton;
                auto rec = getBounds();
                event.mouse.where.x = rec.a.x;
                event.mouse.where.y = rec.a.y+1;
                TPoint MinSz, MaxSz;
                ushort d;
                //-- устанавливаем минимальные границы размера в размер хозяина объекта
                //-- так, чтобы изменение размеров и перемещение не выводило объект
                //-- за границы предка (окна в общем случае)
                auto lims = owner->getExtent();
                lims.grow(-1, -1);
                sizeLimits(MinSz, MaxSz);
                dragView(event, dragMode | dmDragMove, lims, MinSz, MaxSz);
                clearEvent(event);
            }
        }

    }
}


#if !defined(NO_STREAMABLE)

void TWrapStaticText::write(opstream& os)
{
    TView::write(os);
    os.writeBytes((void*) text, StringMaxLen);
}

void *TWrapStaticText::read(ipstream& is)
{
    TView::read(is);
    is.readBytes((void*) text, StringMaxLen);
    return this;
}

TStreamable *TWrapStaticText::build()
{
    return new TWrapStaticText(streamableInit);
}

TWrapStaticText::TWrapStaticText(StreamableInit) noexcept : TView(streamableInit)
{
}

TStreamableClass RWrapStaticText(
        TWrapStaticText::name,
        TWrapStaticText::build,
        __DELTA(TWrapStaticText)
        );

__link(RView)
__link(RWrapStaticText)
#endif

#define Uses_TRect
#define Uses_TGroup
#define Uses_TEvent
#define Uses_ipstream
#define Uses_opstream
#define Uses_ofpstream

#include <tvision/tv.h>

#include "twinsizeindicator.h"
#include "common.h"

const char * const TWinSizeIndicator::name = "TWinSizeIndicator";

TWinSizeIndicator::TWinSizeIndicator(const TRect &rect) :
TIndicator(rect)
{
    posInfo = true;
    sizeInfo = true;
    memset(drawtext, 0x0, StringMaxLen);
    memset(sh, 0x0, StringMaxLen);
    memset(sw, 0x0, StringMaxLen);
    memset(px, 0x0, StringMaxLen);
    memset(py, 0x0, StringMaxLen);
}

TWinSizeIndicator::~TWinSizeIndicator()
{

}

bool TWinSizeIndicator::getPosInfo()
{
    return posInfo;
}

bool TWinSizeIndicator::getSizeInfo()
{
    return sizeInfo;
}

//-- отображать позицию левого верхнего угла

void TWinSizeIndicator::setPosInfo(bool val)
{
    posInfo = val;
    drawView();
}

//-- отображать размеры

void TWinSizeIndicator::setSizeInfo(bool val)
{
    sizeInfo = val;
    drawView();
}

void TWinSizeIndicator::draw()
{
    int delta = 0;
    TColorAttr color;
    TDrawBuffer b;
    if ((state & sfDragging) == 0)
        color = getColor(2);
    else
        color = getColor(1);
    //-- очищаем буфер вывода
    memset(drawtext, 0x0, StringMaxLen);
    //-- получаем высоту и ширину окна
    TRect rp = owner->getBounds();
    //-- формируем строку индикатора
    if (posInfo)
    {
        memset(px, 0x0, StringMaxLen);
        memset(py, 0x0, StringMaxLen);
        _itoa(rp.a.x, px, 10); //-- левая позиция
        _itoa(rp.a.y, py, 10); //-- верхняя позиция

        strcat(drawtext, "[←:");
        strcat(drawtext, px);
        strcat(drawtext, " ↑:");
        strcat(drawtext, py);
        strcat(drawtext, "]");
        delta += 4;
    }
    if (sizeInfo)
    {
        if (posInfo)
            strcat(drawtext, " ");
        int h = rp.b.y - rp.a.y;
        int w = rp.b.x - rp.a.x;
        memset(sh, 0x0, StringMaxLen);
        memset(sw, 0x0, StringMaxLen);
        _itoa(h, sh, 10); //-- высота
        _itoa(w, sw, 10); //-- ширина
        strcat(drawtext, "[↔:");
        strcat(drawtext, sw);
        strcat(drawtext, " ↕:");
        strcat(drawtext, sh);
        strcat(drawtext, "]");
        delta += 4;
    }
    if (!posInfo && !sizeInfo)
    {
        strcat(drawtext, "[☼]");//"[□]"); 
        delta = 2;
    }
    //-- delta-> - дельта из-за использования нетрадиционных символов
    //-- но длина определяется неправильно, поскольку псевдосимволы в строке
    //-- представлены каждый - тремя
    int len = strlen(drawtext) - delta;
    //-- смещаем индикатор в правый нижний угол окна
    int left = rp.b.x - rp.a.x - len - 3;
    TRect r = getBounds();
    setBounds(TRect(left, r.a.y, left + len, r.b.y));

    b.moveStr(0, drawtext, color);
    writeBuf(0, 0, size.x, 2, b);
    owner->drawView();
}

void TWinSizeIndicator::handleEvent(TEvent& event)
{
    if (event.what == evMouseDown)
    {
        posInfo = sizeInfo = true;
        drawView();
        clearEvent(event);
    }
    TView::handleEvent(event);
}

void TWinSizeIndicator::write(opstream& os)
{
    TIndicator::write(os);
    os.writeBytes(&posInfo, sizeof (posInfo));
    os.writeBytes(&sizeInfo, sizeof (sizeInfo));
}

void *TWinSizeIndicator::read(ipstream& is)
{
    TIndicator::read(is);
    is.readBytes(&posInfo, sizeof (posInfo));
    is.readBytes(&sizeInfo, sizeof (sizeInfo));
    //-- внутренние переменные не инициализируются при потоковом чтении
    //-- что самое главное их и сохранять в потоке не имеет смысла, поскольку они 
    //-- являются расходным материалом формируемым в момент отрисовки окна...
    memset(drawtext, 0x0, StringMaxLen);
    memset(sh, 0x0, StringMaxLen);
    memset(sw, 0x0, StringMaxLen);
    memset(px, 0x0, StringMaxLen);
    memset(py, 0x0, StringMaxLen);
    return this;
}

TStreamable *TWinSizeIndicator::build()
{
    return new TWinSizeIndicator(streamableInit);
}

TStreamableClass RWinSizeIndicator(
        TWinSizeIndicator::name,
        TWinSizeIndicator::build,
        __DELTA(TWinSizeIndicator)
        );

__link(RIndicator)
__link(RWinSizeIndicator)



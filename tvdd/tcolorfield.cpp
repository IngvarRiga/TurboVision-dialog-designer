#include "tcolorfield.h"
#include "common.h"

TColorField::TColorField(int deltax, int deltay) :
TView(TRect(deltax, deltay, deltax + 36, deltay + 20))
{
    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    DrawChar = 0x58; //-- > 'X'
    selectedColor = 0x00;
    //setState(sfShadow, true);
}

void TColorField::draw()
{
    char luc = 0xda;
    char ruc = 0xbf;
    char ldc = 0xc0;
    char rdc = 0xd9;
    char hl = 0xc4;
    char vl = 0xb3;
    char lx = 0xc3;
    char rx = 0xb4;
    char ux = 0xc2;
    char dx = 0xc1;
    char xx = 0xc5;
    //-- оптимизированная отрисовка
    TDrawBuffer b[256]; //-- размер буфера отрисовки по вертикальному размеру
    uchar cl = 0x00; //-- цвет отрисовки
    char v[] = "0123456789ABCDEF";
    uchar BorderColor = 0x8F; //-- дефолтный цвет границ 
    //-- формируем декорации ---------------------------------------------------
    b[0].moveChar(0, luc, BorderColor, 1);
    b[0].moveChar(size.x - 1, ruc, BorderColor, 1);
    for (int i = 1; i < size.x - 1; i++)
    {
        b[0].moveChar(i, hl, BorderColor, 1);
        b[size.y - 1].moveChar(i, hl, BorderColor, 1);
    }
    b[size.y - 1].moveChar(0, ldc, BorderColor, 1);
    b[size.y - 1].moveChar(size.x - 1, rdc, BorderColor, 1);
    for (int i = 1; i < size.y - 1; i++)
    {
        b[i].moveChar(0, vl, BorderColor, 1);
        b[i].moveChar(2, vl, BorderColor, 1);
        b[i].moveChar(size.x - 1, vl, BorderColor, 1);
    }
    //-- маркировки и отсечки ------------------------------------------------
    b[0].moveChar(2, ux, BorderColor, 1);
    b[1].moveCStr(1, "   0 1 2 3 4 5 6 7 8 9 A B C D E F", BorderColor);
    b[1].moveChar(2, vl, BorderColor, 1);
    b[2].moveChar(0, lx, BorderColor, 1);
    for (int i = 1; i < size.x - 1; i++)
        b[2].moveChar(i, hl, BorderColor, 1);
    b[2].moveChar(size.x - 1, rx, BorderColor, 1);
    b[2].moveChar(2, xx, BorderColor, 1);
    for (int i = 0; i < 16; i++)
        b[i + 3].moveChar(1, v[i], BorderColor, 1);
    b[size.y - 1].moveChar(2, dx, BorderColor, 1);
    //-- непосредственно цветовое поле -----------------------------------------
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
            b[j + 3].moveChar(i * 2 + 3, DrawChar, cl++, 2);
    //-- выводим весь сформированный буфер одним циклом ------------------------
    for (int i = 0; i < size.y; i++)
        writeLine(0, i, size.x, 1, b[i]);
}

void TColorField::setDrawChar(const char val)
{
    DrawChar = val;
    drawView();
}

void TColorField::handleEvent(TEvent & event)
{
    if ((event.what == evMouseDown) && (event.mouse.buttons == mbLeftButton))
    {
        //-- переводим в локальные координаты объекта
        auto lc = makeLocal(event.mouse.where);
        int x = lc.x;
        int y = lc.y;
        if (
                (x >= 3) && (x <= size.x - 2) &&
                (y >= 3) && (y <= size.y - 2))
        {
            //-- по x и по y дельта 3
            //-- (x-3)/2 - back color
            //-- y-3 - font color
            
            selectedColor = (ushort)(y-3)|((ushort)((x-3)/2) <<4);
            //-- рассылаем команды
            message(owner, evBroadcast, cm_ColorFieldClicked, nullptr);
        }
    }
    TView::handleEvent(event);
}

TStreamable * TColorField::build()
{
    return new TColorField(streamableInit);
}

void TColorField::write(opstream & os)
{

    TView::write(os);
    os << eventMask << options;
}

void *TColorField::read(ipstream & is)
{
    TView::read(is);
    is >> eventMask >> options;
    return this;
}


TStreamableClass RColorField(TColorField::name,
        TColorField::build,
        __DELTA(TColorField)
        );

__link(RStaticText)
__link(RColorField)


#include "tcustomwindow.h"

TCustomWindow::TCustomWindow(const int width, const int height, const char* aTitle, short aNumber) :
    TWindow(TRect(0, 0, width, height), aTitle, aNumber),
    TWindowInit(&TWindow::initFrame)
{
    //-- окно центрируется на экране
    options |= ofCentered;
    auto r = getClipRect();      // получить область прорисовки
    r.grow(-1, -1);   // чтобы "уместить" подобъект в рамку окна
    //intr = new TInterior(r);
    //insert(intr);     // вставить подобъект в окно

    TScrollBar* vScrollBar =
        standardScrollBar(sbVertical | sbHandleKeyboard);
    TScrollBar* hScrollBar =
        standardScrollBar(sbHorizontal | sbHandleKeyboard);
    intr = new TInterior(r, hScrollBar, vScrollBar);

    insert(intr);

}


TInterior::TInterior(const TRect& bounds,
                     TScrollBar* aHScrollBar,
                     TScrollBar* aVScrollBar) :
    TScroller(bounds, aHScrollBar, aVScrollBar)
{
    growMode = gfGrowHiX | gfGrowHiY;
    options = options | ofFramed;
    maxLineLength = 255;
}

void TInterior::draw()
{
    ushort color = getColor(0x0301);
    auto sz = text.size();
    for (int i = 0; i < size.y; i++)
    {
        TDrawBuffer b;
        b.moveChar(0, ' ', color, size.x);
        // заполнить буфер строки пробелами
        auto j = delta.y + i;
        // delta - это смещение строк элемента прокрутки
        if (sz > j)
        {
            auto src = text.at(j).c_str();
            auto len = strlen(src);
            //-- определяем реальную длину строки с учетом UTF
            int st = 0;
            int ut = 0;
            for (int k = 0; k < len; k++)
                src[k] < 0 ? ut++ : st++;
            int sl = ut / 2 + st;
            //-------------------------------------------------
            std::string s;
            if (delta.x > sl)
                s = EOS;
            else
            {
                //-- ищем начало вырезаемой строки
                int beg = 0;
                int dlt = delta.x;
                for (int k = 0; k < dlt; k++)
                {
                    beg++;
                    byte ch = src[k];
                    if ((ch == 0xd0) || (ch == 0xd1))
                    {
                        k++;
                        beg++;
                        dlt++;
                    }
                }
                //-- ищем конец вырезаемой строки
                int end = 0;
                int cnt = 0;
                for (int k = beg; k < len; k++)
                {
                    if (src[k] > 0) end++;
                    else
                        end += 2;
                    cnt++;
                    if (cnt == size.x) break;
                }
                s = text.at(j).substr(beg, end);
                //   s[size.x] = EOS;
            }
            b.moveStr(0, s, color);
            writeLine(0, i, len, 1, b);
        }
        writeLine(0, i, size.x, 1, b);
    }
}

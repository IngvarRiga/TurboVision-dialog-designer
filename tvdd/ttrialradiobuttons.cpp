#include "ttrialradiobuttons.h"
#include "common.h"

const char * const TTrialRadioButtons::name = "TTrialRadioButtons";

TTrialRadioButtons::TTrialRadioButtons(const TRect& bounds, TSItem *aStrings) :
TRadioButtons(bounds, aStrings)
{

    eventMask |= 0xf; //-- установлен флаг получения ВСЕХ сообщений
    options |= ofPreProcess;
    //-- ограничиваем перемещение внутри окна его границами
    dragMode |= dmLimitAll;
    Selected = false;
}

void TTrialRadioButtons::draw()
{
    //-- переопределяем процедуру отрисовки
    TRadioButtons::draw();

    //    const char marker[]= " \x7";
    //    const char icon[]= " ( ) ";
    //    TDrawBuffer b;
    //    TAttrPair color;
    //    int i, j, cur;
    //
    //    TAttrPair cNorm = getColor(0x0301);
    //    TAttrPair cSel = getColor(0x0402);
    //    TAttrPair cDis = getColor(0x0505);
    //    for (i = 0; i <= size.y; i++)
    //    {
    //        b.moveChar(0, ' ', cNorm, size.x);
    //        for (j = 0; j <= (strings->getCount() - 1) / size.y + 1; j++)
    //        {
    //            cur = j * size.y + i;
    //            if (cur < strings->getCount())
    //            {
    //                int col = column(cur);
    //
    //                if (((col + strlen((const char*) strings->at(cur)) + 5)
    //                        < b.length()) && (col < size.x))
    //                {
    //                    if (!buttonState(cur))
    //                        color = cDis;
    //                    else if ((cur == sel) && (state & sfSelected) != 0)
    //                        color = cSel;
    //                    else
    //                        color = cNorm;
    //                    b.moveChar(col, ' ', color, size.x - col);
    //                    b.moveCStr(col, icon, color);
    //
    //                    b.putChar(col + 2, marker[multiMark(cur)]);
    //                    b.moveCStr(col + 5, (char *) (strings->at(cur)), color);
    //                    if (showMarkers && ((state & sfSelected) != 0) && cur == sel)
    //                    {
    //                        b.putChar(col, specialChars[0]);
    //                        b.putChar(column(cur + size.y) - 1, specialChars[1]);
    //                    }
    //
    //                }
    //            }
    //        }
    //        writeBuf(0, i, size.x, 1, b);
    //    }
    //    setCursor(column(sel) + 2, row(sel));

}

void TTrialRadioButtons::setState(ushort aState, Boolean enable)
{
    TView::setState(aState, enable);
    if (aState == sfSelected)
    {
        setSelected(enable);
    }
}

void TTrialRadioButtons::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        //-- вызов окна редактирования свойств объекта
        if ((event.mouse.buttons == mbLeftButton) &&(event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_RadioButtons, nullptr);
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

    TRadioButtons::handleEvent(event);
}

void TTrialRadioButtons::sizeLimits(TPoint& min, TPoint& max)
{
    TRadioButtons::sizeLimits(min, max);
    min.x = 5;
    min.y = 1;
    max.x -= 2;
    max.y -= 2;
}

bool TTrialRadioButtons::isSelected()
{
    return Selected;
}

void TTrialRadioButtons::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}

void TTrialRadioButtons::genCode(char *val)
{
    //-- генерируем код компонента
    //        auto t="\n insert(new TStaticText(TRect(";
    //        strcat(s,t,strlen(t));
    //        auto r = to->getBounds();
}

TStreamable *TTrialRadioButtons::build()
{
    return new TTrialRadioButtons(streamableInit);
}

void TTrialRadioButtons::write(opstream& os)
{

    TRadioButtons::write(os);
    os << eventMask << options << dragMode;
}

void *TTrialRadioButtons::read(ipstream& is)
{
    TRadioButtons::read(is);
    is >> eventMask >> options >> dragMode;
    return this;
}


TStreamableClass RTrialRadioButtons(
        TTrialRadioButtons::name,
        TTrialRadioButtons::build,
        __DELTA(TTrialRadioButtons)
        );

__link(RRadioButtons)
__link(RTrialRadioButtons)
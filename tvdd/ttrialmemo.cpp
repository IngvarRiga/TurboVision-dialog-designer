#include "ttrialmemo.h"
#include "multilang.h"

TTrialMemo::TTrialMemo(const TRect& bounds,
                       TScrollBar* aHScrollBar,
                       TScrollBar* aVScrollBar,
                       TIndicator* aIndicator,
                       ushort aBufSize) :
    TMemo(bounds, aHScrollBar, aVScrollBar, aIndicator, aBufSize)
{
    eventMask |= 0xFF; //-- ���������� ���� ��������� ���� ���������
    options |= ofPreProcess;
    //-- ������������ ����������� ������ ���� ��� ���������
    dragMode |= dmLimitAll;
    //Selected = false;
    memset(var_name, 0x0, StringMaxLen);
    memset(class_name, 0x0, StringMaxLen);
    strncpy(var_name, txt_control, strlen(txt_control));
    strncpy(class_name, txt_TMemo, strlen(txt_TMemo));
    Selected = false;
}

nlohmann::json TTrialMemo::genJSON()
{
    nlohmann::json job;
    job[str_type] = otMemo;
    job[str_var_name] = getVarName();
    job[str_class_name] = getVarName();
    auto sz = getBounds();
    //-- ��������� �������
    job[str_pos][str_x] = sz.a.x;
    job[str_pos][str_y] = sz.a.y;
    //-- �������
    job[str_size][str_x] = sz.b.x - sz.a.x;
    job[str_size][str_y] = sz.b.y - sz.a.y;
    return job;
}

void TTrialMemo::handleEvent(TEvent& event)
{
    if (event.what | evMouse)
    {
        message(owner, evBroadcast, cm_DisableCursorPaint, 0);

        //-- ����� ���� �������������� ������� �������
        if ((event.mouse.buttons == mbLeftButton) && (event.mouse.eventFlags == meDoubleClick))
        {
            message(owner, evBroadcast, cmOption_Button, this);
            clearEvent(event);
        }
        if (event.mouse.buttons == mbRightButton)
            if (event.what == evMouseUp)
            {
                //-- �������� ������������ ���� �������
                TMenuBox* contextMenu = new TMenuBox(TRect(0, 0, 0, 0),
                                                     new TMenu(
                                                         *new TMenuItem(txt_PropertyMemo, cmOption_Memo, -1, hcNoContext) +
                                                         *new TMenuItem(0, 0, 0, hcNoContext, 0, 0) + //-- ��� ���� newLine(), ��������� ��� �������� � ���������� �������� TMemo
                                                         *new TMenuItem(txt_mnu_cmDelete, cm_ed_DestroyMemo, kbCtrlDel, hcNoContext) +
                                                         *new TMenuItem(0, 0, 0, hcNoContext, 0, 0) + //-- ��� ���� newLine(), ��������� ��� �������� � ���������� �������� TMemo
                                                         *new TMenuItem(txt_mnu_Copy, cm_ed_Copy, kbNoKey)
                                                     ), nullptr);

                TPoint tmp;
                tmp.x = event.mouse.where.x;
                tmp.y = event.mouse.where.y;
                clearEvent(event);

                //-- ������� ����� ������� ����� ���� � ����� ����� ������ �� ������
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
                        //-- ��� �������
                        break;
                    case cm_ed_DestroyMemo:
                        destroy(this);
                        return;
                        break;
                    case cm_ed_Copy:
                        //-- ��������� �������� ������� � JSON-������ � ���������� � � ������
                        copy_buffer.clear();
                        copy_buffer = genJSON();
                        return;
                        break;
                    default:
                        message(owner, evBroadcast, res, this);
                        break;
                }
            }

        //-- ������� �� ���� - ����� �������� �������
        if (event.what == evMouseDown)
        {
            owner->forEach(&unselected, 0);
            setSelected(true);
            DragObject(this, event);
            clearEvent(event);
        }
    }
    //-- �������������� �������� ������ � ������ ����������
    if (event.what == evKeyDown)
    {
        //-- ��������� ������� ��������� ������
        //-- ����� ������� ������ � ����� ������
        if (event.keyDown.keyCode == kbCtrlIns)
        {
            clearEvent(event);
            //-- ��������� �������� ������� � JSON-������ � ���������� � � ������
            copy_buffer.clear();
            copy_buffer = genJSON();
            return;
        }
    }

    if (Selected)
    {
        //-- �������������� �������� ������ � ������ ����������
        if (event.what == evKeyDown)
        {
            //-- ��������� ������� ��������� ������
            if (event.keyDown.keyCode == kbCtrlDel)
            {
                clearEvent(event);
                destroy(this);
                return;
            }
        }
    }

    TMemo::handleEvent(event);
}

void TTrialMemo::setState(ushort aState, Boolean enable)
{
    TMemo::setState(aState, enable);
    if (aState == sfSelected)
    {
        if (!enable)
            setSelected(enable);
    }
}

bool TTrialMemo::isSelected()
{
    return Selected;
}

void TTrialMemo::setSelected(bool val)
{
    if (Selected != val)
    {
        Selected = val;
        drawView();
    }
}

void TTrialMemo::sizeLimits(TPoint& min, TPoint& max)
{
    TMemo::sizeLimits(min, max);
    min.x = 1;
    min.y = 1;
    max.x -= 2;
    //-- ������ ����� �������� ������ ���� �������!
    max.y -= 2;
}


void TTrialMemo::genCode(void* val)
{
    ofstream* res = (ofstream*)val;
    auto r = getBounds();

    //-- ���������� ��� ����������
    *res << "\n " << var_name << " = new " << class_name << "(TRect(" << r.a.x << "," << r.a.y << "," << r.b.x << "," << r.b.y << "), nullptr, nullptr, nullptr, 255 );";
    *res << "\n insert(" << var_name << ");";

}


char* TTrialMemo::getVarName()
{
    return var_name;
}

void TTrialMemo::setClassName(const char* val)
{
    memset(class_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(class_name, val, len > StringMaxLen ? StringMaxLen : len);
}

char* TTrialMemo::getClassName()
{
    return class_name;
}

void TTrialMemo::setVarName(const char* val)
{
    memset(var_name, 0x0, StringMaxLen);
    auto len = strlen(val);
    if (len > 0)
        memcpy(var_name, val, len > StringMaxLen ? StringMaxLen : len);
}



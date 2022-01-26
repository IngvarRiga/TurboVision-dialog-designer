#include "common.h"
#include "ttrialstatictext.h"
#include "ttrialinputline.h"
#include "ttrialbutton.h"
#include "ttrialcheckboxes.h"
#include "ttrialradiobuttons.h"
#include "ttriallistbox.h"
#include "ttrialmemo.h"

void DragObject(TView *obj, TEvent event)
{
    TPoint MinSz, MaxSz;
    ushort d;
    //-- устанавливаем минимальные границы размера в размер хозяина объекта
    //-- так, чтобы изменение размеров и перемещение не выводило объект
    //-- за границы предка (окна в общем случае)
    auto lims = obj->owner->getExtent();
    lims.grow(-1, -1);
    obj->sizeLimits(MinSz, MaxSz);

    switch (event.mouse.buttons)
    {
            //-- левой клавишей мыши мы перемещаем объект
        case mbLeftButton:
            d = dmDragMove;
            break;
            //-- правой клавишей мыши - изменяем его размер
        case mbRightButton:
            d = dmDragGrow;
            break;
    }
    obj->dragView(event, obj->dragMode | d, lims, MinSz, MaxSz);
}

void unselected(TView *obj, void *)
{
    obj->setState(sfSelected, false);
}

void generateCode(TView *obj, void *res)
{
    //char s[CodeMaxLen];
   //memset(s, 0x0, CodeMaxLen);
    auto nam = obj->name;
    if (dynamic_cast<TTrialStaticText*> (obj))
    {
        TTrialStaticText *to = dynamic_cast<TTrialStaticText*> (obj);
        to->genCode(res);
        //strncat((char *) res, s, strlen(s));
        return;
    }
    if (dynamic_cast<TTrialButton*> (obj))
    {
        TTrialButton *to = dynamic_cast<TTrialButton*> (obj);
        to->genCode(res);
       // strncat((char *) res, s, strlen(s));
        return;
    }
    if (dynamic_cast<TTrialInputLine*> (obj))
    {
        TTrialInputLine *to = dynamic_cast<TTrialInputLine*> (obj);
        to->genCode(res);
        //strncat((char *) res, s, strlen(s));
        return;
    }
    if (dynamic_cast<TTrialCheckBoxes*> (obj))
    {
        TTrialCheckBoxes *to = dynamic_cast<TTrialCheckBoxes*> (obj);
        //to->genCode(s);
       // strncat((char *) res, s, strlen(s));
        return;
    }
    if (dynamic_cast<TTrialListBox*> (obj))
    {
        TTrialListBox *to = dynamic_cast<TTrialListBox*> (obj);
        //to->genCode(s);
        //strncat((char *) res, s, strlen(s));
        return;
    }
    if (dynamic_cast<TTrialRadioButtons*> (obj))
    {
        TTrialRadioButtons *to = dynamic_cast<TTrialRadioButtons*> (obj);
        //to->genCode(s);
        //strncat((char *) res, s, strlen(s));
        return;
    }
    //if (dynamic_cast<TTrialMemo*> (obj))
    //{
    //    TTrialRadioButtons* to = dynamic_cast<TTrialRadioButtons*> (obj);
    //    //to->genCode(s);
    //    //strncat((char *) res, s, strlen(s));
    //    return;
    //}
}

/*
void deleteSelected(TView *obj, void *val)
{
    //-- Удалению мы можем подвергать только то, что вставили сами
    if (dynamic_cast<TTrialStaticText*> (obj))
    {
        TTrialStaticText *to = dynamic_cast<TTrialStaticText*> (obj);
        if (to->isSelected())
            obj->owner->destroy(to);
        return;
    }
    if (dynamic_cast<TTrialButton*> (obj))
    {
        TTrialButton *to = dynamic_cast<TTrialButton*> (obj);
        if (to->isSelected())
            obj->owner->destroy(to);
        return;
    }
    if (dynamic_cast<TTrialInputLine*> (obj))
    {
        TTrialInputLine *to = dynamic_cast<TTrialInputLine*> (obj);
        if (to->isSelected())
            obj->owner->destroy(to);
        return;
    }
    if (dynamic_cast<TTrialCheckBoxes*> (obj))
    {
        TTrialCheckBoxes *to = dynamic_cast<TTrialCheckBoxes*> (obj);
        if (to->isSelected())
            obj->owner->destroy(to);
        return;
    }
    if (dynamic_cast<TTrialListBox*> (obj))
    {
        TTrialListBox *to = dynamic_cast<TTrialListBox*> (obj);
        if (to->isSelected())
            obj->owner->destroy(to);
        return;
    }
    if (dynamic_cast<TTrialRadioButtons*> (obj))
    {
        TTrialRadioButtons *to = dynamic_cast<TTrialRadioButtons*> (obj);
        if (to->isSelected())
            obj->owner->destroy(to);
        return;
    }

}
*/
#include "tcustomdialog.h"
const char * const TCustomDialog::name = "TCustomDialog";

TCustomDialog::TCustomDialog(const TRect& bounds, TStringView aTitle, bool sizeable, bool centered, bool restrictSize) :
TDialog(bounds, aTitle),
TWindowInit(&TDialog::initFrame)
{
    frestrictSize = restrictSize;
    //-- все диалоги по умолчанию центрируются 
    if (centered)
        options |= ofCentered;
    if (sizeable)
        flags |= wfGrow;
}

TCustomDialog::TCustomDialog(const int width, const int height, TStringView aTitle, bool sizeable, bool restrictSize) :
TDialog(TRect(0, 0, width, height), aTitle),
TWindowInit(&TDialog::initFrame)
{
    frestrictSize = restrictSize;
    //-- диалог центрируется автоматически
    options |= ofCentered;
    //-- Возможность изменения размеров вкл/выкл
    if (sizeable)
        flags |= wfGrow;
}

bool TCustomDialog::valid(ushort command)
{
    bool rslt = TDialog::valid(command);
    if (rslt && (command == cmOK))
    {
    }
    return rslt;
}

void TCustomDialog::setData(void *val)
{
    TDialog::setData(val);
}

void TCustomDialog::getData(void *val)
{
    TDialog::getData(val);
}

void TCustomDialog::handleEvent(TEvent& event)
{
    TDialog::handleEvent(event);
}

void TCustomDialog::write(opstream& os)
{
    TDialog::write(os);
}

void *TCustomDialog::read(ipstream& is)
{
    TDialog::read(is);
    return this;
}

TStreamable *TCustomDialog::build()
{
    return new TCustomDialog(streamableInit);
}

TStreamableClass RCustomDialog(TCustomDialog::name,
        TCustomDialog::build,
        __DELTA(TCustomDialog)
        );

__link(RDialog)
__link(RCustomDialog)


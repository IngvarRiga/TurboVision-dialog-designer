#ifndef TSELECTCOLORDIALOG_H
#define TSELECTCOLORDIALOG_H
#define Uses_TButton
#define Uses_TInputLine
#define Uses_TStaticText
#include <tvision/tv.h>

#include "tcolorfield.h"
#include "tcustomdialog.h"

class TSelectColorDialog : public TCustomDialog
{
  public:
    TSelectColorDialog();

    virtual ~TSelectColorDialog()
    {
    }
    virtual void handleEvent(TEvent& event);

  private:
    TColorField *cf;
    TInputLine *val;
};

#endif /* TSELECTCOLORDIALOG_H */


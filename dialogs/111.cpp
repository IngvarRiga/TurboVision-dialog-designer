TNewDialog::TNewDialog() :
 TDialog(TRect(35,19,85,39), "Новое диалоговое окно"),
 TWindowInit(&TDialog::initFrame)
{

 control = new TListBox(TRect(11,9,21,12), 1, nullptr );
 insert(control);
 control = new TMemo(TRect(7,4,17,7), nullptr, nullptr, nullptr, 255 );
 insert(control);

 selectNext(false);
}

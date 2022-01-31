#сборка редактора 
cmake_minimum_required(VERSION 3.5)

project(tvdd VERSION 1.0 LANGUAGES C CXX)

add_executable(tvdd common.cpp
main.cpp
tbuttonproperties.cpp
tcheckboxesproperties.cpp
tcolorfield.cpp
tcomponentdialog.cpp
tcustomdialog.cpp
tdialogproperties.cpp
tinputlineproperties.cpp
tlistboxproperties.cpp
tmemoproperties.cpp
tprg.cpp
tradiobuttonproperties.cpp
trialdialog.cpp
tselectcolordialog.cpp
tstatictextproperties.cpp
ttrialbutton.cpp
ttrialcheckboxes.cpp
ttrialdialogbackground.cpp
ttrialinputline.cpp
ttriallistbox.cpp
ttrialmemo.cpp
ttrialradiobuttons.cpp
ttrialstatictext.cpp
twinextmenu.cpp
twinsizeindicator.cpp
wbutton.cpp
wcheckboxes.cpp
wcluster.cpp
winputline.cpp
wlistbox.cpp
wmemo.cpp
wradiobuttons.cpp
wstatictext.cpp)

add_subdirectory(include)
target_link_libraries(tvdd tvision.lib)
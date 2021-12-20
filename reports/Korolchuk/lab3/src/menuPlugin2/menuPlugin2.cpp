#include "menuPlugin2.h"

menuPlugin2::menuPlugin2()
{
}

menuPlugin2::~menuPlugin2()
{
}

QString menuPlugin2::getPluginStyle()
{
    return "QMenu::item {font-family: Arial; font-size: 10pt; color: #404040; border: 2px solid red; background-color: rgb(100,100,100);}";
}

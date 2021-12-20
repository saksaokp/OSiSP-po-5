#include "menuPlugin.h"

menuPlugin::menuPlugin()
{
}

menuPlugin::~menuPlugin()
{
}

QString menuPlugin::getPluginStyle()
{
    return "QMenu::item {font-family: Arial; font-size: 13pt; color: #808080; border: 1px solid gray; background-color: rgb(234,234,234);}";
}

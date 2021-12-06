#ifndef FONTPLUGININTERFACE_H
#define FONTPLUGININTERFACE_H

#include "pluginInterface_global.h"
#include <QFont>

class FontPluginInterface
{
public:
    virtual QFont getFont() = 0;
};

Q_DECLARE_INTERFACE(FontPluginInterface, "Sokoban.FontPluginInterface");

#endif // FONTPLUGININTERFACE_H

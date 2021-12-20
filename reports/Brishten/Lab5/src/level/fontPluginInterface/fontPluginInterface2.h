#ifndef LEVELPLUGININTERFACE_H
#define LEVELPLUGININTERFACE_H

#include "pluginInterface_global2.h"
#include <QFont>

class LevelPluginInterface
{
public:
    virtual int newLevel() = 0;
};

Q_DECLARE_INTERFACE(LevelPluginInterface, "Pacman.LevelPluginInterface");

#endif // FONTPLUGININTERFACE_H

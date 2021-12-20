#ifndef FONTPLUGIN_H
#define FONTPLUGIN_H
#include <QFont>
#include <fontPluginInterface2.h>

class FontPlugin : public QObject, public LevelPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(LevelPluginInterface)
    Q_PLUGIN_METADATA(IID "Pacman.LevelPluginInterface" FILE "fontPlugin.json")

public:
    virtual int newLevel();
};

#endif // FONTPLUGIN_H

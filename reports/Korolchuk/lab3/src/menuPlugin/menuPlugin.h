#ifndef MENUPLUGIN_H
#define MENUPLUGIN_H

#include <pluginInterface.h>

class menuPlugin : public pluginInterface
{
    Q_OBJECT
    Q_INTERFACES(pluginInterface)
    Q_PLUGIN_METADATA(IID "com.mysoft.Application.pluginInterface" FILE "menuPlugin.json")

public:
    explicit menuPlugin();
    ~menuPlugin();
    QString getPluginStyle();
};

#endif // MENUPLUGIN_H

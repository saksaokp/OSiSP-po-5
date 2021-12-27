#ifndef MENUPLUGIN_H
#define MENUPLUGIN_H

#include <pluginInterface.h>

class menuPlugin2 : public pluginInterface
{
    Q_OBJECT
    Q_INTERFACES(pluginInterface)
    Q_PLUGIN_METADATA(IID "com.mysoft.Application.pluginInterface" FILE "menuPlugin2.json")

public:
    explicit menuPlugin2();
    ~menuPlugin2();
    QString getPluginStyle();
};

#endif // MENUPLUGIN_H

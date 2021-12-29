#ifndef MENUPLUGIN_H
#define MENUPLUGIN_H

#include <pluginInterface.h>

class menuPlugin3 : public pluginInterface
{
    Q_OBJECT
    Q_INTERFACES(pluginInterface)
    Q_PLUGIN_METADATA(IID "com.mysoft.Application.pluginInterface" FILE "menuPlugin3.json")

public:
    explicit menuPlugin3();
    ~menuPlugin3();
    QString getPluginStyle();
};

#endif // MENUPLUGIN_H

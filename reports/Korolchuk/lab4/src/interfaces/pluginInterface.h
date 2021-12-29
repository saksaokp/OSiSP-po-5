#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>

class pluginInterface : public QObject
{
public:
        virtual ~pluginInterface() = default;
        virtual QString getPluginStyle() = 0;
};

Q_DECLARE_INTERFACE(pluginInterface, "com.mysoft.Application.pluginInterface")

#endif

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QString>
#include <QFont>

class Interface
{
public:
    virtual ~Interface(){}
    virtual QString pluginName() = 0;//плагин должен возвращать свое имя
    virtual QFont changeView() = 0;//плагин выполняет действия над объектами в структуре Styles
};

Q_DECLARE_INTERFACE(Interface, "Snake.Interface");

#endif // INTERFACE_H

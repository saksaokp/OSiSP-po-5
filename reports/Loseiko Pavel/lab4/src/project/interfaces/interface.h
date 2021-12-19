#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QString>
#include <QFont>

class Interface
{
public:
    virtual QFont changeView() = 0;//плагин выполняет действия над объектами в структуре Styles
};

Q_DECLARE_INTERFACE(Interface, "Maze.Interface");

#endif // INTERFACE_H

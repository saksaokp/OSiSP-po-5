#include "interfas.h"
#include <QDebug>

interfas::interfas(QObject *parent) : QObject(parent)
{
    qDebug() << name() << "created";
}

interfas::~interfas()
{
    qDebug() << name() << "destroy";
}

QString interfas::name()
{
    return "themes_interfases 1";
}

QPalette interfas::changeInterfase()
{
    qDebug() << name() << "print";
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Background, QColor(20, 20, 150));
    return darkPalette;
}

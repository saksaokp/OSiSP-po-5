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
    return "themes_interfases 3";
}

QPalette interfas::changeInterfase()
{
    qDebug() << name() << "print";
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Background, QColor(167, 80, 30));
    return darkPalette;
}

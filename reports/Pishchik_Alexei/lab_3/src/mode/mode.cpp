#include "mode.h"
#include <QDebug>

Mode::Mode(QObject *parent) : QObject(parent)
{
    qDebug() << name() << "created";
}

Mode::~Mode()
{
    qDebug() << name() << "destroy";
}

QString Mode::name()
{
    return "mode 1";
}

QFont Mode::changeView()
{
    qDebug() << name() << "print";
    QFont newFont("Courier", 6, QFont::Bold, true);
    return newFont;
}

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
    QFont palette("Comic Sans MS", 10, QFont::Bold, true);
    return palette;
}

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
    return "mode 3";
}

QFont Mode::changeView()
{
    QFont palette("Courier", 12, QFont::Bold, true);
    return palette;
}

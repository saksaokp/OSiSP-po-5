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
    return "mode 2";
}

QFont Mode::changeView()
{
    QFont palette("Times New Roman", 10, QFont::Bold, true);
    return palette;
}

#ifndef HELPER_H
#define HELPER_H

#include "helper_global.h"
#include <QDebug>
#include <QGraphicsItem>

class HELPER_EXPORT Helper
{
public:
    Helper();
    void SetPoints(QVector<QPoint> points);
    //void removepoint(QPoint p);
    QVector<QPoint> points;
};

#endif // HELPER_H

#ifndef BALL_H
#define BALL_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QLibrary>
#include <QDebug>


typedef void (*lib_func)();

class Ball : public QGraphicsItem
{
public:
    Ball();  
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void drawballs(QPainter *painter);
    void setpoints(QVector<QPoint> points);
    void changeGeometry() { prepareGeometryChange(); }

    int ballx,bally;
    int ballw,ballh;
    QPixmap ballpix;
    QRectF rec;
    QVector<QPoint> points;
    lib_func f;
};

#endif // BALL_H

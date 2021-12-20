#ifndef PACMAN_H
#define PACMAN_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
class Pacman : public QGraphicsItem
{

public:
    Pacman();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance();
    void setpacx(int);
    void setpacy(int);
    void setDirection(int dir);
    void changeGeometry() { prepareGeometryChange(); }


    QPixmap left1,left2,left3,left4;
    QPixmap up1,up2,up3,up4;
    QPixmap down1,down2,down3,down4;
    QPixmap right1,right2,right3,right4;

    int pacx,pacy;
    int direction;
    int animestate;
};

#endif // PACMAN_H

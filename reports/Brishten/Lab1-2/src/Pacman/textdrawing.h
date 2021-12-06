#ifndef TEXTDRAWING_H
#define TEXTDRAWING_H
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
class Textdrawing : public QGraphicsItem
{
public:
    Textdrawing();
     QRectF boundingRect() const;
     void SetOver(bool over);
      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
      bool over,playing;
      int x,y,w,h,score;
};

#endif // TEXTDRAWING_H

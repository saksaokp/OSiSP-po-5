#include "textdrawing.h"

Textdrawing::Textdrawing()
{
    over=false;
    w=350;
    h=50;
    x=450/2-w/2;
    y=480/2-h/2;
    score=0;
    playing=false;
}

QRectF Textdrawing::boundingRect() const
{
    return QRect(x, y, w, h);
}

void Textdrawing::SetOver(bool over)
{
    this->over=over;
}

void Textdrawing::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::blue);
    painter->setPen(pen);
    QFont font=painter->font() ;

    QBrush brush(Qt::blue);
    painter->setBrush(brush);
    if(!playing){
        font.setPointSize ( 18 );
         painter->setFont(font);
        if(over){

             painter->drawText( x+90,y-70, "GAME OVER." );
             painter->drawText( x+20,y+120, "PRESS ENTER TO PLAY." );
            painter->drawText(boundingRect(),Qt::AlignCenter, "SCORE : "+QString::number(score) );

        }else{
            painter->drawText(boundingRect(),Qt::AlignCenter, "PRESS SPACE TO START");
        }
    }else{
        font.setPointSize (13);
        painter->setFont(font);
         painter->drawText( 50,15, "SCORE : "+QString::number(score));
    }

}

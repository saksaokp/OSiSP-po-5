#include "helper.h"
/*void Helper::removepoint(QPoint p)
{

}*/

void generatePointPixmap()
{
    QRect bounds = QRect(0, 0, 3, 3);

    QPainter painter;

    ballpix = QPixmap(bounds.size());
    ballpix.fill(Qt::transparent);
    painter.begin(&ballpix);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(0, 0, 3, 3);

}

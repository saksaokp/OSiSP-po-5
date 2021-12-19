#include <QPainter>
#include <time.h>
#include <QTimer>
#include <QString>
#include <QtWidgets>
#include <QMessageBox>
#include "snake.h"
#include "ui_snake.h"

void MainWindow::GenerateFood()
{
    foodPoint.setX(rand()%AREA_COL);
    foodPoint.setY(rand()%AREA_ROW);

    if(snake.contains(foodPoint) || wall.contains(foodPoint))
        GenerateFood();
}

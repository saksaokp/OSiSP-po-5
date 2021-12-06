#include <QPainter>
#include <time.h>
#include <QTimer>
#include <QString>
#include <QtWidgets>
#include <QMessageBox>
#include "snake.h"
#include "ui_snake.h"


typedef bool (*Generate_Snake)(int i);
void MainWindow::InitGame()
{
    snake.clear();
    GenerateSnake();
    dir=RIGHT;
    srand(time(0));
    GenerateFood();
    score=0;
    isPause=false;
    gameTimer=new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(SnakeUpdate()));
    gameTimer->start(TIME_INTERVAL);
}

void MainWindow::GenerateSnake()
{
    QLibrary *helperLib = new QLibrary("helper");
    if (!helperLib->load())
        qDebug() << helperLib->errorString();
    if (helperLib->load())
        qDebug() << "library loaded";

    Generate_Snake generateSnake_ = (Generate_Snake)helperLib->resolve("GenerateSnake");
    for (int i=AREA_COL;i>=0;i--) {
            if(generateSnake_(i)){
                snake.push_back(QPoint(i, 0));
            }
    }
    delete helperLib;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);


    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::blue);
    painter.drawRect(MARGIN,MARGIN,AREA_COL*BLOCK_SIZE,AREA_ROW*BLOCK_SIZE);

    painter.setBrush(Qt::blue);
    painter.setPen(Qt::black);
    for(int i=0;i<wall.size();i++)
        painter.drawRect(MARGIN+wall[i].x()*BLOCK_SIZE,MARGIN+wall[i].y()*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);


    painter.setBrush(Qt::red);
    painter.setPen(Qt::green);
    for(int i=0;i<snake.size();i++)
        painter.drawRect(MARGIN+snake[i].x()*BLOCK_SIZE,MARGIN+snake[i].y()*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);


    painter.setBrush(Qt::green);

    painter.drawEllipse(MARGIN+foodPoint.x()*BLOCK_SIZE,MARGIN+foodPoint.y()*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);


    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    painter.drawText(MARGIN*3+AREA_COL*BLOCK_SIZE,MARGIN+2*BLOCK_SIZE,"score: "+QString::number(score));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        if(dir!=DOWN)
            dir=UP;
        break;
    case Qt::Key_Down:
        if(dir!=UP)
            dir=DOWN;
        break;
    case Qt::Key_Left:
        if(dir!=RIGHT)
            dir=LEFT;
        break;
    case Qt::Key_Right:
        if(dir!=LEFT)
            dir=RIGHT;
        break;
    case Qt::Key_P:
        PauseResumeGame();
        break;
    case Qt::Key_Escape:
        PauseResumeGame();
        break;
    default:
        break;
    }
}

bool MainWindow::IsGameOver()
{
    int x=snake.front().x();
    int y=snake.front().y();
    if(x<0||x>AREA_COL-1||y<0||y>AREA_ROW-1)
        return true;

    for(int i=1;i<snake.size();i++)
        if(snake[i]==snake.front())
            return true;
    for(int i=0;i<wall.size();i++)
        if(wall[i]==snake.front())
            return true;
    return false;
}

void MainWindow::SnakeUpdate()
{
    switch(dir)
    {
    case UP:
        snake.push_front(QPoint(snake.front().x(),snake.front().y()-1));
        break;
    case DOWN:
        snake.push_front(QPoint(snake.front().x(),snake.front().y()+1));
        break;
    case LEFT:
        snake.push_front(QPoint(snake.front().x()-1,snake.front().y()));
        break;
    case RIGHT:
        snake.push_front(QPoint(snake.front().x()+1,snake.front().y()));
        break;
    default:
        break;
    }
    if(snake.contains(foodPoint))
    {
        score+=1;
        GenerateFood();
        gameTimer->start(TIME_INTERVAL - score);
    }
    else
        snake.pop_back();
    if(IsGameOver())
    {
        GameOver();
        return;
    }
    update();
}

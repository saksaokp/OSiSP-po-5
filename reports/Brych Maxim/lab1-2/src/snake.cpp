#include <QPainter>
#include <time.h>
#include <QTimer>
#include <QString>
#include <QtWidgets>
#include <QMessageBox>
#include "snake.h"
#include "ui_snake.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(QSize(MARGIN*7+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));
    SetPlugins();
    InitMenu();
}

void MainWindow::GameOver()
{
    gameTimer->stop();
    QMessageBox::information(this,"Failed","Game over!");
     InitMenu();

}

void MainWindow::PauseResumeGame()
{
    if(!isPause)
    {
        isPause=!isPause;
        gameTimer->stop();
        InitPause();
    }
    else
    {
        isPause=!isPause;
        gameTimer->start(TIME_INTERVAL);
    }
}

void MainWindow::InitPause()
{
    QMessageBox::StandardButton pause;
      pause = QMessageBox::question(this, "Pause", "Продолжить?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (pause == QMessageBox::Yes) {
        PauseResumeGame();
      } else {
        InitMenu();
      }
}



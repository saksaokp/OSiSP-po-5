#include "maze.h"
#include "ui_maze.h"

Maze::Maze(QWidget *parent): QMainWindow(parent), ui(new Ui::Maze)
{
    ui->setupUi(this);

    setFixedSize(QSize(MARGIN*2+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));

    this->setWindowTitle("Maze");

    ui->btn_start->setText("Играть");

    QMenu* menu = new QMenu("О программе");
    ui->menubar->addMenu(menu);
    menu->addAction("about.dll", this,SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);

}

void Maze::InitMenu() {

    ui->setupUi(this);
    setFixedSize(QSize(MARGIN*2+(AREA_COL+1)*BLOCK_SIZE,MARGIN*2+AREA_ROW*BLOCK_SIZE));
    connect(ui->btn_start, SIGNAL(clicked()), this, SLOT(on_btn_start_clicked()));
    connect(ui->btn_exit, SIGNAL(clicked()), this, SLOT(on_btn_exit_clicked()));

    this->setWindowTitle("Maze");

    ui->btn_start->setText("Играть");

    QMenu* menu = new QMenu("О программе");
    ui->menubar->addMenu(menu);
    menu->addAction("about.dll", this,SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);

}

void Maze::PauseResumeGame()
{
    if(!isPause)
    {
        isPause=!isPause;
        InitPause();
    }
    else isPause=!isPause;
}

void Maze::InitPause()
{
    QMessageBox::StandardButton pause;
      pause = QMessageBox::question(this, "Pause", "Продолжить?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (pause == QMessageBox::Yes) {
        PauseResumeGame();
      }
      else {
          flag_game = false;
          InitMenu();

      }
}

void Maze::on_btn_start_clicked()
{
    ui->centralwidget->setVisible(false);
    flag_game = true;
    InitGame();
}

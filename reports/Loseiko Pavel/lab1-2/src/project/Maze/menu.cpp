#include "maze.h"
#include "ui_maze.h"

void Maze::on_btn_exit_clicked()
{
    exit(0);
}

void Maze::aboutQt()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About programm");
    msgBox.setText("Эту программу сделал Лозейко Павел");
    msgBox.exec();
}

Maze::~Maze(){
    delete ui;
}

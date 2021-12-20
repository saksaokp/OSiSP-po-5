#include "menu.h"

menu::menu(QWidget *parent) : QMainWindow(parent)
{
    QMenu *file;
    file = menuBar()->addMenu("&File");
}

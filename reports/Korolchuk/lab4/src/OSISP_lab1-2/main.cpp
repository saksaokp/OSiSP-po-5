#include "arkanoid.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Arkanoid w;

    w.setWindowTitle("Arkanoid");
    w.setFixedSize(300, 400);

    w.show();
    return a.exec();
}

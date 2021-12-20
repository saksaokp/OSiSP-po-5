#include <QApplication>
#include "window.h"
#include "menu.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window w;
    w.show();
    return a.exec();
}

#include "snake.h"
#include <QApplication>
#include <QStyle>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            a.screenAt(w.pos())->availableGeometry()
        )
    );
    w.show();

    return a.exec();
}

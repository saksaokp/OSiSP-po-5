#include "widget.h"
#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Game *game = new Game();

    w.setScene(game);

    QObject::connect(game, SIGNAL(score(int)), &w, SLOT(score(int)));
    QObject::connect(game, SIGNAL(fUpdate()), &w, SLOT(fUpdate()));


    game->startGame();

    return a.exec();
}

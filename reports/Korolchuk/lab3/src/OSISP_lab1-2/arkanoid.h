#ifndef ARKANOID_H
#define ARKANOID_H

#include <QWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QDialog>
#include <QLibrary>
#include "ball.h"
#include "helper_class.h"
#include "paddle.h"
#include "about.h"
#include "pluginInterface.h"
#include <QPluginLoader>
#include <QDir>

class Arkanoid : public QMainWindow
{
    Q_OBJECT

public:
    Arkanoid(QWidget *parent = nullptr);
    ~Arkanoid();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void drawObjects(QPainter *);
    void finishGame(QPainter *, QString);
    void moveObjects();

    void startGame();
    void pauseGame();
    void stopGame();
    void winGame();
    void checkCollision();
    void resetLocation();

private slots:
    void resetGame();
    void aboutProg();
    void plugin1_func();
    void plugin2_func();
    void plugin3_func();

private:
    static const int SPEED = 3;
    int timerId;
    static const int BRICKS_COUNT = 30;
    Ball *ball;
    Paddle *paddle;
    Brick *bricks[BRICKS_COUNT];
    bool gameLost;
    bool gameWon;
    bool gameStarted;
    bool gamePaused;
    bool timerStarted;
    int score;
    int fails;
    pluginInterface *pluginObject1;
    pluginInterface *pluginObject2;
    pluginInterface *pluginObject3;
};
#endif // ARKANOID_H

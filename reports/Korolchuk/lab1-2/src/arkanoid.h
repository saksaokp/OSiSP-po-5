#ifndef ARKANOID_H
#define ARKANOID_H

#include <QWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QDialog>
#include "ball.h"
#include "brick.h"
#include "paddle.h"

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

private:
    QDialog *aboutGame;
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
    int score;
    int fails;
};
#endif // ARKANOID_H

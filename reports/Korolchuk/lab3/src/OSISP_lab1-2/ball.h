#ifndef BALL_H
#define BALL_H

#include <QWidget>

class Ball
{
public:
    Ball();

    int get_xDir();
    int get_yDir();
    void set_xDir(int);
    void set_yDir(int);
    void returnToDefault();
    QRect getRect();
    void move();

private:
    int xDir;
    int yDir;
    QRect ball;
    static const int BALL_WIDTH = 6;
    static const int BALL_HEIGHT = 6;
    static const int X_START_POINT = 147;
    static const int Y_START_POINT = 344;
};

#endif // BALL_H

#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>

class Paddle
{
public:
    Paddle();

    int get_xDir();
    void set_xDir(int);
    void returnToDefault();
    QRect getRect();
    void move();

private:
    int xDir;
    static const int PADDLE_WIDTH = 40;
    static const int PADDLE_HEIGHT = 10;
    static const int X_START_POINT = 130;
    static const int Y_START_POINT = 350;
    QRect paddle;
};

#endif // PADDLE_H

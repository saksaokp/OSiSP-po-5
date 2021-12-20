#include "ball.h"

Ball::Ball()
{
    xDir = 0;
    yDir = -1;
    ball = QRect(X_START_POINT, Y_START_POINT, BALL_WIDTH, BALL_HEIGHT);
}

int Ball::get_xDir()
{
    return xDir;
}

int Ball::get_yDir()
{
    return yDir;
}

void Ball::set_xDir(int value)
{
    xDir = value;
}

void Ball::set_yDir(int value)
{
    yDir = value;
}

void Ball::returnToDefault()
{
    ball.moveTo(X_START_POINT, Y_START_POINT);
    xDir = 0;
    yDir = 1;
}

QRect Ball::getRect()
{
    return ball;
}

void Ball::move()
{
    ball.translate(xDir, yDir);

    if (ball.left() == 0) {
        xDir = 1;
    }

    if (ball.right() == 300) {
        xDir = -1;
    }

    if (ball.top() == 0) {
        yDir = 1;
    }
}

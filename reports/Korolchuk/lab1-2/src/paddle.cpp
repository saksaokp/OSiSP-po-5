#include "paddle.h"

Paddle::Paddle()
{
    xDir = 0;
    paddle = QRect(X_START_POINT, Y_START_POINT, PADDLE_WIDTH, PADDLE_HEIGHT);
}

int Paddle::get_xDir()
{
    return xDir;
}

void Paddle::set_xDir(int value)
{
    xDir = value;
}

void Paddle::returnToDefault()
{
    paddle.moveTo(X_START_POINT, Y_START_POINT);
    xDir = 0;
}

QRect Paddle::getRect()
{
    return paddle;
}

void Paddle::move()
{
    paddle.translate(xDir, 0);
}

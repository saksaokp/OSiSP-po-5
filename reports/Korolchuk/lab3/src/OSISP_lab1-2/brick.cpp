#include "brick.h"

Brick::Brick(int x, int y)
{
    brick = QRect(x, y, BRICK_WIDTH, BRICK_HEIGHT);
    broken = false;
}

QRect Brick::getRect()
{
    return brick;
}

bool Brick::isBroken()
{
    return broken;
}

void Brick::setBroken(bool value)
{
    broken = value;
}

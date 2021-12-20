#ifndef BRICK_H
#define BRICK_H

#include <QWidget>

class Brick
{
public:
    Brick(int, int);

    QRect getRect();
    bool isBroken();
    void setBroken(bool);

private:
    QRect brick;
    static const int BRICK_WIDTH = 50;
    static const int BRICK_HEIGHT = 10;
    bool broken;
};

#endif // BRICK_H

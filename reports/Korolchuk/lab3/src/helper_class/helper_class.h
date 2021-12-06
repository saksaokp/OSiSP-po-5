#ifndef HELPER_CLASS_H
#define HELPER_CLASS_H

#include "helper_class_global.h"
#include <QRect>

class HELPER_CLASS_EXPORT Helper_class
{
public:
    Helper_class();
};

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

#endif // HELPER_CLASS_H

#ifndef HELPER_CLASS_H
#define HELPER_CLASS_H

#include "helper_class_global.h"
#include <QRect>

class HELPER_CLASS_EXPORT Helper_class
{
public:
    Helper_class(int, int);

    QRect getRect();
    bool isBroken();
    void setBroken(bool);

    static const int BRICKS_COUNT = 30;
    static const int levelsCount = 2;

    static void chooseLevel(Helper_class *bricks[Helper_class::BRICKS_COUNT], int lvl);

private:
    QRect brick;
    static const int BRICK_WIDTH = 50;
    static const int BRICK_HEIGHT = 10;
    bool broken;
};

#endif // HELPER_CLASS_H

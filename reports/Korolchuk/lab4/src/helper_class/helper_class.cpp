#include "helper_class.h"

Helper_class::Helper_class(int x, int y)
{
    brick = QRect(x, y, BRICK_WIDTH, BRICK_HEIGHT);
    broken = false;
}

QRect Helper_class::getRect()
{
    return brick;
}

bool Helper_class::isBroken()
{
    return broken;
}

void Helper_class::setBroken(bool value)
{
    broken = value;
}

void Helper_class::chooseLevel(Helper_class *bricks[Helper_class::BRICKS_COUNT], int lvl) {
    if (lvl == 1) {
        int k = 0;

        for (int i=3; i<8; i++) {
            for (int j=0; j<6; j++) {
              bricks[k] = new Helper_class(j*50, i*10);
              k++;
            }
        }
    }
    else if (lvl == 2) {
        int k = 0;

        for (int i=3; i<13; i++) {
            if (i % 2 == 1) {
                for (int j=0; j<5; j++) {
                    if (j % 2 == 0) {
                        bricks[k] = new Helper_class(j*50, i*10);
                        k++;
                    }
                }
            }
            else {
                for (int j=1; j<6; j++) {
                    if (j % 2 == 1) {
                        bricks[k] = new Helper_class(j*50, i*10);
                        k++;
                    }
                }
            }
        }
    }
}

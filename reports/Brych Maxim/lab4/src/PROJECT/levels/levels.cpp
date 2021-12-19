#include "levels.h"

bool GenerateWall(int i, int j)
{
    bool temp = false;
    if((i <11 || i > 17) && j == 15) {
                temp = true;
            }
    return temp;
}

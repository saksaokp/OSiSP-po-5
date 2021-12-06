#include "helper.h"
#include <QMessageBox>

bool GenerateWall(int level, int i, int j)
{
    bool temp = false;
    switch (level) {
    case 1:

        break;
    case 2:
        if((i <11 || i > 17) && j == 15) {
            temp = true;
        }
        break;
    default:
        break;
    }
    return temp;

}
bool GenerateSnake(int i)
{
    bool temp = false;
    if(i >= 0 && i < 3)
        temp = true;
    return temp;
}
int countLevel()
{
    return level;
}

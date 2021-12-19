#ifndef HELPER_H
#define HELPER_H

#include "helper_global.h"
#include <QPaintEvent>

extern "C" HELPER_EXPORT bool GenerateWall(int level, int i, int j);
extern "C" HELPER_EXPORT bool GenerateSnake(int i);
extern "C" HELPER_EXPORT int countLevel();
int level = 2;

#endif // HELPER_H

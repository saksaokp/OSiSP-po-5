#ifndef HELPER_H
#define HELPER_H

#include "helper_global.h"
#include <QString>

extern "C" HELPER_EXPORT QString set_window_name();
extern "C" HELPER_EXPORT QString set_name_About();
extern "C" HELPER_EXPORT bool GenerateSnake(int i);

#endif // HELPER_H

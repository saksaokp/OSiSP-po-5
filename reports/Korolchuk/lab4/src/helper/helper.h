#ifndef HELPER_H
#define HELPER_H

#include "helper_global.h"

extern "C" HELPER_EXPORT void resetParams(bool &gameLost, bool &gameWon, bool &gameStarted,
                                          bool &gamePaused, int &score, int &fails);
extern "C" HELPER_EXPORT void setParamsForStop(bool& timerStarted, bool& gameLost, bool& gameStarted);
extern "C" HELPER_EXPORT void setParamsForWin(bool& timerStarted, bool& gameWon, bool& gameStarted);

#endif // HELPER_H

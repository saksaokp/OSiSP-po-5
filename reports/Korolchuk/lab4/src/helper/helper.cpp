#include "helper.h"
#include <QDialog>
#include <QLabel>

void resetParams(bool &gameLost, bool &gameWon, bool &gameStarted, bool &gamePaused, int &score, int &fails) {
    gameLost = false;
    gameWon = false;
    gameStarted = true;
    gamePaused = false;
    score = 0;
    fails = 0;
}

void setParamsForStop(bool& timerStarted, bool& gameLost, bool& gameStarted) {
    timerStarted = false;
    gameLost = true;
    gameStarted = false;
}

void setParamsForWin(bool& timerStarted, bool& gameWon, bool& gameStarted) {
    timerStarted = false;
    gameWon = true;
    gameStarted = false;
}

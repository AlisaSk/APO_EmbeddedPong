#ifndef LED_H
#define LED_H

#include <stdbool.h>

bool ledInit();
void ledLineClean();
void ledWin(int winnerNum);
void ledStartPage(int milisec);

#endif
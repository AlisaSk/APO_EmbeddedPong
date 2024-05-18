#include "racket.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include <stdbool.h> 

#define WIDTH 480
#define HEIGHT 320



void initRacket(Racket* racket, int number) {
    racket->x = number == 1 ? 50 : WIDTH - 50;
    racket->y = HEIGHT / 2;
    racket->w = 20;
    racket->h = 100;
    racket->color = 0xffff;
}


bool moveRacket (Racket* racket, int number) {
  int y1 = racket->y + number;
  if (y1 >= 0 && y1 <= HEIGHT - racket->h) {
    drawRacket(racket, 0x0000);
    racket->y =  y1;
    return true;
  }
  return false;
}



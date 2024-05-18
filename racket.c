#include "racket.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "headers.h"

/* This file contains all of the functions for rackets*/



void initRacket(Racket* racket, int number) {
    racket->x = number == 1 ? 50 : WIDTH - 50;
    racket->y = HEIGHT / 3;
    racket->w = 20;
    racket->h = 100;
    racket->color = number == 1 ? PLAYER_1_COLOR: PLAYER_2_COLOR;
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

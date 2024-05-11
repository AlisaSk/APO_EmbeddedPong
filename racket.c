#include "racket.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#define WIDTH 480
#define HEIGHT 320

void initRacket(Racket* racket, int number) {
    racket->x = number == 1 ? 50 : WIDTH - 50;
    racket->y = HEIGHT / 2;
    racket->w = 20;
    racket->h = 100;
    racket->color = 0xffff;
}

void drawRacket(Racket* racket) {
  int x = racket->x;
  int y = racket->y;
  int w = racket->w;
  int h = racket->h;
  for (int x1 = x; x1 < w + x; x1 ++) {
    for (int y1 = y; y1 < y + h; y1++) {
      draw_pixel(x1, y1, racket->color);
    }
  }
}
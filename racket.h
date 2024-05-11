#ifndef RACKET_H
#define RACKET_H

typedef struct Racket {
  int x,y;
  int w,h;
  unsigned short color;
} Racket;
 
void initRacket(Racket* racket, int number);
void drawRacket(Racket* racket);

#endif
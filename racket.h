#ifndef RACKET_H
#define RACKET_H

#include <stdbool.h> 

typedef struct Racket {
  int x,y;
  int w,h;
  unsigned short color;
} Racket;
 
void initRacket(Racket* racket, int number);
bool moveRacket (Racket* racket, int number);

#endif
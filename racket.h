#ifndef RACKET_H
#define RACKET_H

<<<<<<< HEAD
#include <stdbool.h> 
=======
#include <stdbool.h>
>>>>>>> dev

typedef struct Racket {
  int x,y;
  int w,h;
  unsigned short color;
} Racket;
 
void initRacket(Racket* racket, int number);
bool moveRacket (Racket* racket, int number);

#endif
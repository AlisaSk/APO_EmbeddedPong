#ifndef BALL_H
#define BALL_H

#include "racket.h"
#include <stdbool.h>

typedef struct Ball {
  int x, y; /* position on the screen */
  int w,h; // ball width and height
  int dx, dy; /* movement vector */
} Ball;

void initBall(Ball* ball);
bool moveBall(Ball* ball, Racket* rackets);
//void drawBall(Ball* ball, unsigned short color);
bool checkCollisionX( Racket* rocket, Ball* ball, int rocketNumber);
bool checkCollisionY( Racket* rocket, Ball* ball, int rocketNumber);

#endif
#include "ball.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "headers.h"



extern int score1;
extern int score2;

void initBall(Ball* ball, int botSpeed) {
  ball->w = 20;
  ball->h = 20;
  ball->x = WIDTH / 2;
  ball->y = HEIGHT / 2;
   
  if (botSpeed == 0) {
     /* Intializes random number generator for multiplayer*/
    time_t t;
    srand((unsigned) time(&t));
    int minSpeed = 4;
    ball->dx = rand() % 2 + minSpeed;
    ball->dy = rand() % 2 + minSpeed;
   } else {
    switch(botSpeed) {
      case 3:
        ball->dx = -8;
        ball->dy = 8;
        break;
      case 2:
        ball->dx = 6;
        ball->dy = -6;
        break;
      default:
        ball->dx = -4;
        ball->dy = 4;
        break;
    }
   }
   
   
   
}

bool moveBall(Ball* ball, Racket* rackets) {
    drawBall(ball, 0x0000);
    int new_x = ball->x + ball->dx;
    int new_y = ball->y + ball->dy;
    
    bool isValidX = !checkCollisionX(&rackets[0], ball, 1) && !checkCollisionX(&rackets[1], ball, 2);
    bool isValidY = (new_y >= 0 && new_y < HEIGHT - ball->h) && !checkCollisionY(&rackets[0], ball, 1) && !checkCollisionY(&rackets[1], ball, 2);


    if (!isValidX) {
        ball->dx *= -1;
        new_x = ball->x + ball->dx;
    }

    if (new_x <= 0 + ball->w + 25) {
      score2++;
      return false;
    } else if (new_x >= WIDTH - ball->w - 25){
      score1++;
      return false;
    }

    if (!isValidY) {
        ball->dy *= -1;
        new_y = ball->y + ball->dy;
    }

    ball->x = new_x;
    ball->y = new_y;
    return true;
}


bool checkCollisionX( Racket* rocket, Ball* ball, int rocketNumber) {
    // Calculate the sides of the rectangle
    int rocketLeft = rocket->x;
    int rocketRight = rocket->x + rocket->w;
    int rocketTop = rocket->y;
    int rocketBottom = rocket->y + rocket->h;

    // Calculate the sides of the square ball
    int ballLeft = ball->x;
    int ballRight = ball->x + ball->w;
    int ballTop = ball->y;
    int ballBottom = ball->y + ball->h;

    bool ret = false;
    switch (rocketNumber) {
      case 1:
        if (ballLeft <= rocketRight && rocketBottom >= ballTop && rocketTop <= ballBottom) {
          ret = true;
        }
        break;
      case 2:
        if (ballRight >= rocketLeft && rocketBottom >= ballTop && rocketTop <= ballBottom) {
          ret = true;
        }
        break; 
    }
    return ret;

}

bool checkCollisionY( Racket* rocket, Ball* ball, int rocketNumber) {
      // Calculate the sides of the rectangle
    int rocketLeft = rocket->x;
    int rocketRight = rocket->x + rocket->w;
    int rocketTop = rocket->y;
    int rocketBottom = rocket->y + rocket->h;

    // Calculate the sides of the square ball
    int ballLeft = ball->x;
    int ballRight = ball->x + ball->w;
    int ballTop = ball->y;
    int ballBottom = ball->y + ball->h;

    bool ret = false;
    switch (rocketNumber) {
      case 1:
        if ((ballBottom >= rocketTop && ballLeft <= rocketRight && ballTop < rocketTop) || ( ballTop <= rocketBottom && ballLeft <= rocketRight && ballBottom > rocketBottom)) {
          ret = true;
        }
        break;
      case 2:
        if ((ballBottom >= rocketTop && ballRight >= rocketLeft && ballTop < rocketTop) || ( ballTop <= rocketBottom && ballRight >= rocketLeft && ballBottom > rocketBottom)) {
          ret = true;
        }
        break; 
    }
    return ret;
}
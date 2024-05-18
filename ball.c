#include "ball.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#define WIDTH 480
#define HEIGHT 320



void initBall(Ball* ball) {
    ball->w = 20;
    ball->h = 20;
    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->dx = 5;
    ball->dy = 5;
   
}

bool moveBall(Ball* ball, Racket* rackets, int *score1, int *score2) {
    drawBall(ball, 0x0000);
    int new_x = ball->x + ball->dx;
    int new_y = ball->y + ball->dy;
    
    // bool isValidX = new_x >= 0 && new_x < WIDTH - ball->w;
    bool isValidX = !checkCollisionX(&rackets[0], ball, 1) && !checkCollisionX(&rackets[1], ball, 2);
    bool isValidY = (new_y >= 0 && new_y < HEIGHT - ball->h) && !checkCollisionY(&rackets[0], ball, 1) && !checkCollisionY(&rackets[1], ball, 2);


    if (!isValidX) {
        ball->dx *= -1;
        new_x = ball->x + ball->dx;
    }

    if (new_x <= 0 + ball->w) {
      (*score1)++;
      return false;
    } else if (new_x >= WIDTH - ball->w){
      (*score2)++;
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
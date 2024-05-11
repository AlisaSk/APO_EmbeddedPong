/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON
 
  change_me.c      - main file
 
  include your name there and license for distribution.
 
  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.
 
 *******************************************************************/
 
#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
 
// #include "../module1/header1.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#define WIDTH 480
#define HEIGHT 320
 
#include "font_types.h"
 
unsigned short *fb;

typedef struct Ball {
  int x, y; /* position on the screen */
  int w,h; // ball width and height
  int dx, dy; /* movement vector */
} Ball;

typedef struct Racket {
  int x,y;
  int w,h;
  unsigned short color;
} Racket;
 
void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}
 
void draw_char(int x, int y, font_descriptor_t* fdes, char ch) {
}
 
int char_width(font_descriptor_t* fdes, int ch) {
  int width = 0;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    ch -= fdes->firstchar;
    if (!fdes->width) {
      width = fdes->maxwidth;
    } else {
      width = fdes->width[ch];
    }
  }
  return width;
}

void change_pixels();
void initBall(Ball* ball);
void moveBall(Ball* ball);
void drawBall(Ball* ball, unsigned short color);
bool checkCollision( Racket* rocket, Ball* ball, int rocketNumber);

Racket rackets[2];
 
int main(int argc, char *argv[]) {
  unsigned char *mem_base;
  unsigned char *parlcd_mem_base;
  uint32_t val_line=5;
  int i,j,k;
  int ptr;
  unsigned int c;
  fb  = (unsigned short *)malloc(320*480*2);
 
  printf("Hello world\n");
 
  sleep(1);
  /*
   * Setup memory mapping which provides access to the peripheral
   * registers region of RGB LEDs, knobs and line of yellow LEDs.
   */
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  /* If mapping fails exit with error code */
  if (mem_base == NULL)
    exit(1);
 // ******** led lights
  struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
  for (i=0; i<30; i++) {
     *(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = val_line;
     val_line<<=1;
     printf("LED val 0x%x\n", val_line);
     clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
  // *************//
 
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
 
  if (parlcd_mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);

  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
      fb[ptr] = 0;
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
  }
  
  initRacket(&rackets[0], 1);
  initRacket(&rackets[1], 2);
  drawRacket(&rackets[0]);
  drawRacket(&rackets[1]);

  Ball new_ball;
  initBall(&new_ball);
  printf("new ball w - %d\n", new_ball.w);
  drawBall(&new_ball, 0xe9dd);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
  }
  while (1) {
    moveBall(&new_ball);
    drawBall(&new_ball, 0xe9dd);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
  }
 

  // change_pixels();

  for (ptr = 0; ptr < 480*320 ; ptr++) {
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
 
  clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
 
  int x = 10;
  char str[]="Goodbye world";
  char *ch=str;
  font_descriptor_t* fdes = &font_winFreeSystem14x16;
 
  printf("Goodbye world\n");
 
  return 0;
}

void change_pixels() {
  // for (int x = 0; x < 480; x++) {
  //    for (int y = 0; y < 320; y++) {
  //     if (x % 40 == 0 || y % 40 == 0) {
  //       draw_pixel(x, y, 0xef5d);
  //     }
  //   }
  // }  

  for (int x = 100; x < 150; x++) {
    for (int y = 100; y < 150; y++) {
      draw_pixel(x, y, 0xef02);
    }
  }                                                      

}

void initBall(Ball* ball) {
    ball->w = 20;
    ball->h = 20;
    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->dx = 5;
    ball->dy = 5;
   
}

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

void moveBall(Ball* ball) {
    drawBall(ball, 0x0000);
    int new_x = ball->x + ball->dx;
    int new_y = ball->y + ball->dy;
    // bool isValidX = new_x >= 0 && new_x < WIDTH - ball->w;
    bool isValidX = !checkCollision(&rackets[0], ball, 1) && !checkCollision(&rackets[1], ball, 2);
    bool isValidY = new_y >= 0 && new_y < HEIGHT - ball->h;


    if (!isValidX) {
        ball->dx *= -1;
        new_x = ball->x + ball->dx;
    }

    if (!isValidY) {
        ball->dy *= -1;
        new_y = ball->y + ball->dy;
    }

    ball->x = new_x;
    ball->y = new_y;
}

void drawBall (Ball* ball, unsigned short color) {
  int x = ball->x;
  int y = ball->y;
  int w = ball->w;
  int h = ball->h;
  for (int x1 = x; x1 < w + x; x1 ++) {
    for (int y1 = y; y1 < y + h; y1++) {
      draw_pixel(x1, y1, color);
    }
  }
}

bool checkCollision( Racket* rocket, Ball* ball, int rocketNumber) {
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
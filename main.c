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

#include "ball.h"
#include "racket.h"
#include "led.h"
#include "knobs.h"

#define WIDTH 480
#define HEIGHT 320
 
#include "font_types.h"
 
unsigned short *fb;



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

Racket rackets[2];
 
int main(int argc, char *argv[]) {
  unsigned char *parlcd_mem_base;
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
  ledInit();
  ledLineLightUp();
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

  initKnobs();
  KnobsData kd = getKnobsValue();
  uint8_t kr = kd.redKnob;
  uint8_t kg = kd.greenKnob;
  draw_pixel_big(kr, kg, 0x07f4);

  drawBall(&new_ball, 0xe9dd);
  for (ptr = 0; ptr < 480*320 ; ptr++) {
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
  }
  while (1) {
    moveBall(&new_ball, rackets);
    drawBall(&new_ball, 0xe9dd);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }

    
    KnobsData kd = getKnobsValue();
    uint8_t krn = kd.redKnob;
    uint8_t kgn = kd.greenKnob;
    draw_pixel_big(kr, kg, 0x0841);
    draw_pixel_big(krn, kgn, 0x07f4);
    printf("red %d green %d \n", krn, kgn);
    kr = krn;
    kg = kgn;
  }
 


  for (ptr = 0; ptr < 480*320 ; ptr++) {
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
 
  char str[]="Goodbye world";
  char *ch=str;
  font_descriptor_t* fdes = &font_winFreeSystem14x16;
 
  printf("Goodbye world\n");
 
  return 0;
}




void draw_pixel_big(int x, int y, unsigned short color) {
  int i,j;
  for (i=0; i<20; i++) {
    for (j=0; j<20; j++) {
      draw_pixel(x+i, y+j, color);
    }
  }
}


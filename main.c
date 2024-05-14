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
#include "menu.h"
#include "start.h"

#define WIDTH 480
#define HEIGHT 320
 
#include "font_types.h"
 
unsigned short *fb;
unsigned char *parlcd_mem_base;
int player1Score = 0;
int player2Score = 0;


void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}
 


Racket rackets[2];
 
int main(int argc, char *argv[]) {
  
  int ptr;
  unsigned int c;
  fb  = (unsigned short *)malloc(320*480*2);
  int roundCount = 1;
 
  printf("Hello world!!!!\n");
 
  sleep(1);
  /*
   * Setup memory mapping which provides access to the peripheral
   * registers region of RGB LEDs, knobs and line of yellow LEDs.
   */


  ledInit();
  // ledLineLightUp();
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
 
  if (parlcd_mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

<<<<<<< HEAD
  startPage( parlcd_mem_base);
=======
  startPage(parlcd_mem_base);

  int mode = startMenu( parlcd_mem_base);
>>>>>>> dev

  
  for (ptr = 0; ptr < 480*320 ; ptr++) {
      fb[ptr] = 0;
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
  }
  
  if (mode == 2) {
    while (roundCount != 4) {
      for (ptr = 0; ptr < 480*320 ; ptr++) {
          fb[ptr] = 0;
          parlcd_write_data(parlcd_mem_base, fb[ptr]);
      }
      initRacket(&rackets[0], 1);
      initRacket(&rackets[1], 2);
      drawRacket(&rackets[0], 0xffff);
      drawRacket(&rackets[1], 0xffff);

      Ball new_ball;
      initBall(&new_ball);
      drawBall(&new_ball, 0xe9dd);

      initKnobs();
      KnobsData kd = getKnobsValue();
      uint8_t kr = kd.redKnob;
      uint8_t kg = kd.greenKnob;
      uint8_t kb = kd.blueKnob;

      for (ptr = 0; ptr < 480*320 ; ptr++) {
          parlcd_write_data(parlcd_mem_base, fb[ptr]);
      }
      while (moveBall(&new_ball, rackets)) {
        
        drawBall(&new_ball, 0xe9dd);


        KnobsData nkd = getKnobsValue();
        uint8_t krn = nkd.redKnob;
        uint8_t kgn = nkd.greenKnob;
        uint8_t kbn = nkd.blueKnob;
        if (krn > kr) {
          moveRacket(&rackets[0], 10);
          drawRacket(&rackets[0], 0xffff);
        }
        else if (krn < kr) {
          moveRacket(&rackets[0], -10);
          drawRacket(&rackets[0], 0xffff);
        }
        if (kbn > kb) {
          moveRacket(&rackets[1], 10);
          drawRacket(&rackets[1], 0xffff);
        }
        else if (kbn < kb) {
          moveRacket(&rackets[1], -10);
          drawRacket(&rackets[1], 0xffff);
        }


        kr = krn;
        kg = kgn;
        kb = kbn;

        for (ptr = 0; ptr < 480*320 ; ptr++) {
          parlcd_write_data(parlcd_mem_base, fb[ptr]);
        }

        
      }
      roundCount++;
    }
  }
  else {
      for (ptr = 0; ptr < 480*320 ; ptr++) {
      fb[ptr] = 0x07ff;
      parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
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


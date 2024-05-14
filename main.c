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
#include "painter.h"
#include "botmenu.h"

#define WIDTH 480
#define HEIGHT 320
 
#include "font_types.h"
 
unsigned short *fb;
unsigned char *parlcd_mem_base;
int player1Score = 0;
int player2Score = 0;


Racket rackets[2];
 
int main(int argc, char *argv[]) {
  
  int ptr;
  unsigned int c;
  fb  = (unsigned short *)malloc(320*480*2);
  int roundCount = 1;
  int botMainSpeed = 6;
  int botSpeed;
 
  printf("Hello world!!!!\n");
 
  sleep(1);
  ledInit();
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
 
  if (parlcd_mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  startPage();
  
  int mode = startMenu();

  if (mode == 1) {
    unsigned int ms_count = 0;
    clock_t start_time = clock();
    while (ms_count < 500) {
        ms_count = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
    }
    int diff = startBotMenu();
    botSpeed = diff * botMainSpeed;
  }

  

  
  drawBackground(0x0000);
  
  
  while (roundCount != 4) {
    drawBackground(0x0000);
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
    int counter = 0;
    renderLCD();
    while (moveBall(&new_ball, rackets)) {
      
      drawBall(&new_ball, 0xe9dd);


      KnobsData nkd = getKnobsValue();
      uint8_t krn = nkd.redKnob;
      if (krn > kr) {
        moveRacket(&rackets[0], 10);
        drawRacket(&rackets[0], 0xffff);
      }
      else if (krn < kr) {
        moveRacket(&rackets[0], -10);
        drawRacket(&rackets[0], 0xffff);
      }

      
      if (moveRacket(&rackets[1], botSpeed)) {
        drawRacket(&rackets[1], 0xffff);
      }
      else {
        drawRacket(&rackets[1], 0xffff);
        botSpeed *= -1;
      }

      




      kr = krn;

      renderLCD();
      counter++;
      
    }
    roundCount++;
  }
  

  
 


  // renderLCD();
 
  char str[]="Goodbye world";
  char *ch=str;
  font_descriptor_t* fdes = &font_winFreeSystem14x16;
 
  printf("Goodbye world\n");
 
  return 0;
}

// void showScores() {

// }
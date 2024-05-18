#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
 

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
#include "pong.h"

#define WIDTH 480
#define HEIGHT 320
 
#include "font_types.h"
 
unsigned short *fb;
unsigned char *parlcd_mem_base;
int score1 = 0;
int score2 = 0;
int scoreold1 = 0;
int scoreold2 = 0;


Racket rackets[2];

void showScores();
 
int main(int argc, char *argv[]) {
  

  fb  = (unsigned short *)malloc(320*480*2);
  int roundCount = 1;
  int botMainSpeed = 5;
  int botSpeed;
 
 
  sleep(1);
  ledInit();
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
 
  if (parlcd_mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  startPage();
  
  int mode = startMenu();

  
  drawBackground(0x0000);
  
  if (mode == 2) {
    while (score1 != 5 && score2 != 5) {
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
      uint8_t kg = kd.greenKnob;
      uint8_t kb = kd.blueKnob;

      renderLCD();
      while (moveBall(&new_ball, rackets, &score1, &score2)) {
        
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

        renderLCD();

        
      }
      showScores();
      roundCount++;
      if (score1 > scoreold1) {
        scoreold1++;
      } else {
        scoreold2++;
      }
    }
    int diff = startBotMenu();
    botSpeed = diff * botMainSpeed;
    playGameBot(botSpeed);
  }

  
  
 
  printf("Goodbye pong\n");
 
  return 0;
}

void showScores() {
  drawScores(score1, score2);
  int winner = score1 >scoreold1 ? 1: 2;
  ledWin(winner);
}

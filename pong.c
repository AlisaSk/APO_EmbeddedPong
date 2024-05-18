#include "ball.h"
#include "racket.h"
#include "led.h"
#include "knobs.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include "end.h"

extern int score1;
extern int score2;
extern int scoreold1;
extern int scoreold2; 
extern Racket rackets[2];
#define WIDTH 480
#define HEIGHT 320


void playGameBot(int botMode) {
    int botSpeed = botMode * 5;
    drawBackground(0x0000);
    Ball new_ball;
    initBall(&new_ball, botMode);
  
    while (score1 != 5 && score2 != 5) {
        drawBackground(0x0000);
        initRacket(&rackets[0], 1);
        initRacket(&rackets[1], 2);
        drawRacket(&rackets[0], 0xffff);
        drawRacket(&rackets[1], 0xffff);

        initBall(&new_ball, botMode);
        
        drawBall(&new_ball, 0xe9dd);

        initKnobs();
        KnobsData kd = getKnobsValue();
        uint8_t kr = kd.redKnob;
        renderLCD();
        while (moveBall(&new_ball, rackets)) {
        
            drawBall(&new_ball, 0xe9dd);
            drawRacket(&rackets[0], 0xffff);

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
        
        
        }
      showScores();
      
      if (score1 > scoreold1) {
        scoreold1++;
      } else {
        scoreold2++;
      }
        
    }
}

void playMultiplayer() {
    Ball new_ball;
    initBall(&new_ball, 0);
    while (score1 != 5 && score2 != 5) {
      drawBackground(0x0000);
      initRacket(&rackets[0], 1);
      initRacket(&rackets[1], 2);
      drawRacket(&rackets[0], 0xffff);
      drawRacket(&rackets[1], 0xffff);

      new_ball.x = WIDTH / 2;
      new_ball.y = HEIGHT / 2;

      
      drawBall(&new_ball, 0xe9dd);

      initKnobs();
      KnobsData kd = getKnobsValue();
      uint8_t kr = kd.redKnob;
      uint8_t kg = kd.greenKnob;
      uint8_t kb = kd.blueKnob;

      renderLCD();
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

        renderLCD();

        
      }
      showScores();
      if (score1 > scoreold1) {
        scoreold1++;
      } else {
        scoreold2++;
      }
    }
}


void showScores() {
  drawScores(score1, score2);
  int winner = score1 >scoreold1 ? 1: 2;
  ledWin(winner);
}
#include "ball.h"
#include "racket.h"
#include "led.h"
#include "knobs.h"
#include "end.h"
#include "painter.h"
#include "headers.h"

extern int score1;
extern int score2;
extern int scoreold1;
extern int scoreold2; 
extern Racket rackets[2];

void playGameBot(int botMode) {
    int botSpeed = botMode * 5;
    drawBackground(BLACK);
    Ball newBall;
    initBall(&newBall, botMode);
  
    while (score1 != 5 && score2 != 5) {
        drawBackground(BLACK);
        initRacket(&rackets[0], 1);
        initRacket(&rackets[1], 2);
        drawRacket(&rackets[0], rackets[0].color);
        drawRacket(&rackets[1], rackets[1].color);

        initBall(&newBall, botMode);
        
        drawBall(&newBall, PURPLE);

        initKnobs();
        KnobsData kd = getKnobsValue();
        uint8_t kr = kd.redKnob;
        renderLCD();
        while (moveBall(&newBall, rackets)) {
        
            drawBall(&newBall, PURPLE);
            drawRacket(&rackets[0], rackets[0].color);

            KnobsData nkd = getKnobsValue();
            uint8_t krn = nkd.redKnob;
            if (krn > kr) {
                moveRacket(&rackets[0], 10);
                drawRacket(&rackets[0], rackets[0].color);
            }
            else if (krn < kr) {
                moveRacket(&rackets[0], -10);
                drawRacket(&rackets[0], rackets[0].color);
            }

            
            if (moveRacket(&rackets[1], botSpeed)) {
                drawRacket(&rackets[1], rackets[1].color);
            }
            else {
                drawRacket(&rackets[1], rackets[1].color);
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
    showEnd();
}

void playMultiplayer() {
    Ball newBall;
    initBall(&newBall, 0);
    while (score1 != 5 && score2 != 5) {
      drawBackground(BLACK);
      initRacket(&rackets[0], 1);
      initRacket(&rackets[1], 2);
      drawRacket(&rackets[0], rackets[0].color);
      drawRacket(&rackets[1], rackets[1].color);

      newBall.x = WIDTH / 2;
      newBall.y = HEIGHT / 2;

      
      drawBall(&newBall, PURPLE);

      initKnobs();
      KnobsData kd = getKnobsValue();
      uint8_t kr = kd.redKnob;
      uint8_t kg = kd.greenKnob;
      uint8_t kb = kd.blueKnob;

      renderLCD();
      while (moveBall(&newBall, rackets)) {
        
        drawBall(&newBall, PURPLE);


        KnobsData nkd = getKnobsValue();
        uint8_t krn = nkd.redKnob;
        uint8_t kgn = nkd.greenKnob;
        uint8_t kbn = nkd.blueKnob;
        if (krn > kr) {
          moveRacket(&rackets[0], 10);
          drawRacket(&rackets[0], rackets[0].color);
        }
        else if (krn < kr) {
          moveRacket(&rackets[0], -10);
          drawRacket(&rackets[0], rackets[0].color);
        }
        if (kbn > kb) {
          moveRacket(&rackets[1], 10);
          drawRacket(&rackets[1], rackets[1].color);
        }
        else if (kbn < kb) {
          moveRacket(&rackets[1], -10);
          drawRacket(&rackets[1], rackets[1].color);
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
    showEnd();
}


void showScores() {
  drawScores(score1, score2);
  int winner = score1 > scoreold1 ? 1: 2;
  ledWin(winner);
}
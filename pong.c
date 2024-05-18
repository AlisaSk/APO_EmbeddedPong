#include "pong.h"
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

int player1Score = 0;
int player2Score = 0;
Racket rackets[2];


void playGameBot(int botSpeed) {
    int roundCount = 1;

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
}
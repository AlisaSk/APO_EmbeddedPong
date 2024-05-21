#include "end.h"
#include "painter.h"
#include "knobs.h"
#include "menu.h"
#include "led.h"
#include "headers.h"

extern int score1;
extern int score2;
extern int scoreold1;
extern int scoreold2;

/* This file contains all of the functions to display end page and total score*/

void showEnd() {
    printf("End\n");
    drawBackground(BLACK);
    char endMessage[15];
    char scores[10];
    int winner = score1 > score2 ? 1 : 2;
    sprintf(endMessage, "PLAYER %d W IN", winner);
    sprintf(scores, "%d:%d", score1, score2);

    // adding end page texts
    draw_word(160, 30, "END", 40, PURPLE, 4);
    draw_word(160, 100, scores, 45, GREEN, 4);
    draw_word(40, 170, endMessage, 30, PURPLE, 3);
    draw_word(20, 265, "PRESS ANY BUTTON TO START", 18, WHITE, 2);
    renderLCD();

    initKnobs();
    KnobsData kd = getKnobsValue();
    uint8_t rb = kd.redButton;
    uint8_t gb = kd.greenButton;
    uint8_t bb = kd.blueButton;

    int switcher = -1;
    int counterLeds = 0;

    // waiting for the button pressed
    while (!rb && !gb && !bb) {
        switch (switcher) {
            case -1:
                draw_word(20, 265, "PRESS ANY BUTTON TO START", 18, 0xffff, 2);
                break;
            default:
                draw_word(20, 265, "PRESS ANY BUTTON TO START", 18, 0x0000, 2);
                break;
        }
        switcher *= -1;

        renderLCD();

        kd = getKnobsValue();
        rb = kd.redButton;
        gb = kd.greenButton;
        bb = kd.blueButton;

        unsigned int msCount = 0;
        clock_t startTime = clock();
        while (msCount < 190) {
            msCount = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
        }

        if (counterLeds == 10) {
            ledEndPage(10);
            counterLeds = 0;
        } else { 
            counterLeds++;
        }
    }
    printf("Restart\n");
    score1 = 0;
    score2 = 0;
    scoreold1 = 0;
    scoreold2 = 0;
    startMenu();
}
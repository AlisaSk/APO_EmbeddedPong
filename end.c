#include "end.h"
#include "painter.h"
#include "knobs.h"
#include "menu.h"
#include <stdio.h>

extern int score1;
extern int score2;

void showEnd() {
    printf("End\n");
    drawBackground(0x0000);
    char endMessage[15];
    char scores[10];
    int winner = score1 > score2 ? 1 : 2;
    sprintf(endMessage, "PLAYER %d W IN", winner);
    sprintf(scores, "%d:%d", score1, score2);

    draw_word(160, 30, "END", 40, 0x90f6, 4);
    draw_word(160, 100, scores, 45, 0x5fa3, 4);
    draw_word(40, 170, endMessage, 30, 0x90f6, 3);
    draw_word(20, 265, "PRESS ANY BUTTON TO START", 18, 0xffff, 2);
    renderLCD();

    initKnobs();
    KnobsData kd = getKnobsValue();
    uint8_t rb = kd.redButton;
    uint8_t gb = kd.greenButton;
    uint8_t bb = kd.blueButton;

    while (!rb && !gb && !bb) {
        kd = getKnobsValue();
        rb = kd.redButton;
        gb = kd.greenButton;
        bb = kd.blueButton;
    }
    printf("Restart\n");
    score1 = 0;
    score2 = 0;
    startMenu();
}
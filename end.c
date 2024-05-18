#include "end.h"
#include "painter.h"
#include "knobs.h"
#include "menu.h"
#include "headers.h"

extern int score1;
extern int score2;

void showEnd() {
    printf("End\n");
    drawBackground(BLACK);
    char endMessage[15];
    char scores[10];
    int winner = score1 > score2 ? 1 : 2;
    sprintf(endMessage, "PLAYER %d W IN", winner);
    sprintf(scores, "%d:%d", score1, score2);

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
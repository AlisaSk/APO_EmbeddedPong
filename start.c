#include "start.h"
#include "font_types.h"
#include "led.h"
#include "painter.h"
#include "menu.h"
#include "headers.h"

/* This file contains all of the functions to animate start page*/

void startPage( ) {
    int ptr;

    printf("Start\n");

    sleep(1);


    drawBackground(0x0000);

    if (!initKnobs()) {
        fprintf(stderr, "ERROR_KNOBS!\n");
        exit(-1);
    };
    KnobsData kd = getKnobsValue();
    uint8_t rb = kd.redButton;
    uint8_t gb = kd.greenButton;
    uint8_t bb = kd.blueButton;

    unsigned short color1 = PURPLE;
    unsigned short color2 = BLACK;
    drawRectangle(color1, color2);
    kd = getKnobsValue();
    rb = kd.redButton;
    gb = kd.greenButton;
    bb = kd.blueButton;

    draw_word(125, 65, "START", 50, WHITE, 4);
    draw_word(145, 130, "PONG", 50, WHITE, 4);
    renderLCD();
    ledStartPage(15);

    int switcher = -1;
    int counterLeds = 0;
    while (!rb && !gb && !bb) {
        drawRectangle(color1, color2);
        switch (switcher) {
            case -1:
                draw_word(20, 265, "PRESS ANY BUTTON TO START", 18, WHITE, 2);
                break;
            default:
                draw_word(20, 265, "PRESS ANY BUTTON TO START", 18, BLACK, 2);
                break;
        }
        switcher *= -1;
    
        renderLCD();
        unsigned short colorTemp = color1;
        color1 = color2;
        color2 = colorTemp;

        kd = getKnobsValue();
        rb = kd.redButton;
        gb = kd.greenButton;
        bb = kd.blueButton;

        

        unsigned int ms_count = 0;
        clock_t start_time = clock();
        while (ms_count < 190) {
            ms_count = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
        }
        
        if (counterLeds == 10) {
            ledStartPage(10);
            counterLeds = 0;
        } else { 
            counterLeds++;
        }

    }
    
    printf("Goodbye start\n");
    startMenu();
}




#include "led.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include <time.h>
#include <stdint.h>
#include <stdio.h>

static unsigned char *ledMemBase;

bool ledInit(){
    bool ret = true;
    ledMemBase = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (!ledMemBase) {
        fprintf(stderr, "ERROR_LED!\n");
        ret = false;
    } else {
        ledLineClean();
    }
    return ret;

}

void ledLineClean() {
    *(volatile uint32_t *)(ledMemBase + SPILED_REG_LED_LINE_o) = 0;
}

void ledRGBClean () {
    *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_RGB2_o) = 0;
    *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_RGB1_o) = 0;
}

void colorLedRGB (unsigned short color1, unsigned short color2) {
    *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_RGB1_o) = color1;
    *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_RGB2_o) = color2;
}

void ledWin(int winnerNum) {
    uint32_t val_line = 5;
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 40 * 1000 * 1000};
    for (int i=0; i<30; i++) {
        switch(winnerNum) {
            case 1:
                colorLedRGB(0x00FF00, 0);
                break;
            default:
                colorLedRGB(0, 0x00FF);
                break;
        }
        *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_LINE_o) = val_line;
        val_line<<=1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
        ledRGBClean();
    }
    for (int i=0; i<30; i++) {
        switch(winnerNum) {
            case 1:
                colorLedRGB(0x00FF00, 0);
                break;
            default:
                colorLedRGB(0, 0x00FF);
                break;
        }
        *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_LINE_o) = val_line;
        val_line>>=1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
        ledRGBClean();
    }
    ledLineClean();
    ledRGBClean();
}


void ledStartPage(int milisec) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = milisec * 1000 * 1000}; // 20 milliseconds
    uint32_t val_line = 10;
    for (int i=0; i<30; i++) {
        *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_LINE_o) = val_line;
        colorLedRGB (0x00FF00, 0x00FF);
        val_line<<=1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
        ledRGBClean();
    }
    for (int i=0; i<30; i++) {
        colorLedRGB (0x00FF, 0xf81d);
        *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_LINE_o) = val_line;
        val_line>>=1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
        ledRGBClean();
    }
    ledLineClean();
    ledRGBClean();
}

void ledEndPage() {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 10 * 1000 * 1000}; // 20 milliseconds
    uint32_t val_line = 10;
    for (int i=0; i<30; i++) {
        *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_LINE_o) = val_line;
        val_line<<=1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
        ledRGBClean();
    }
    for (int i=0; i<30; i++) {
        *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_LINE_o) = val_line;
        val_line>>=1;
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
        ledRGBClean();
    }
    ledRGBClean();
}
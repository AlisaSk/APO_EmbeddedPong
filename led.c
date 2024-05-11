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
        fprintf(stderr, "ERROR: Physical LED address could not be mapped!\n");
        ret = false;
    } else {
        ledLineClean();
    }
    return ret;

}

void ledLineClean() {
    *(volatile uint32_t *)(ledMemBase + SPILED_REG_LED_LINE_o) = 0;
}

void ledLineLightUp() {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
    uint32_t val_line = 5;
    for (int i=0; i<30; i++) {
        *(volatile uint32_t*)(ledMemBase + SPILED_REG_LED_LINE_o) = val_line;
        val_line<<=1;
        printf("LED val 0x%x\n", val_line);
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
    ledLineClean();
}

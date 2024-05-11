
#ifndef MENU_H
#define MENU_H


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "led.h"
#include "knobs.h"
#include <stdbool.h>
#include <time.h>


void startMenu(unsigned char *parlcd_mem_base);

void drawRectangle(unsigned short color1, unsigned short color2);

void draw_pixel_big(int x, int y, unsigned short color);

#endif

#ifndef START_H
#define START_H


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


void startPage();

void drawRectangle(unsigned short color1, unsigned short color2);


#endif

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


void startMenu(unsigned short *fb, unsigned char *parlcd_mem_base);

#endif
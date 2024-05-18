#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
 

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "ball.h"
#include "racket.h"
#include "led.h"
#include "knobs.h"
#include "menu.h"
#include "start.h"
#include "painter.h"
#include "botmenu.h"
#include "pong.h"

#define WIDTH 480
#define HEIGHT 320
 
#include "font_types.h"
 
unsigned short *fb;
unsigned char *parlcd_mem_base;

 
int main(int argc, char *argv[]) {
  

  fb  = (unsigned short *)malloc(320*480*2);
  int roundCount = 1;
  int botMainSpeed = 5;
  int botSpeed;
 
 
  sleep(1);
  ledInit();
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
 
  if (parlcd_mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  startPage();
  
  int mode = startMenu();

  if (mode == 1) {
    unsigned int ms_count = 0;
    clock_t start_time = clock();
    while (ms_count < 500) {
        ms_count = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
    }
    int diff = startBotMenu();
    botSpeed = diff * botMainSpeed;
    playGameBot(botSpeed);
  }

  
  
 
  printf("Goodbye pong\n");
 
  return 0;
}

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
int score1 = 0;
int score2 = 0;
int scoreold1 = 0;
int scoreold2 = 0;

Racket rackets[2];

void showScores();
 
int main(int argc, char *argv[]) {
  

  fb  = (unsigned short *)malloc(320*480*2);
  sleep(1);
  ledInit();
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
 
  if (parlcd_mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  startPage();
  
  printf("Goodbye pong\n");
 
  return 0;
}


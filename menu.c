#include "menu.h"
#include "font_types.h"
#include "knobs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include <time.h>
#include <string.h>


static unsigned short* menuBuffer;
static font_descriptor_t* fdes = &font_winFreeSystem14x16;
static int scale = 4;

int startMenu(unsigned char* parlcd_mem_base) {
  
  menuBuffer = (unsigned short*) malloc(320*480*2);
  int gameMode = 1;
  for (int ptr = 0; ptr < 480*320 ; ptr++) {
        menuBuffer[ptr] = 0;
        parlcd_write_data(parlcd_mem_base, menuBuffer[ptr]);
    }
  draw_word(120, 30, "MENU", 50, 0x90f6);
  draw_word(115, 120, "1 pLayer", 30, 0xfe80);
  draw_word(115, 200, "2 pLayers", 30, 0xfe80);

  initKnobs();
  KnobsData kd = getKnobsValue();
  uint8_t kr = kd.redKnob;
  uint8_t kg = kd.greenKnob;
  uint8_t kb = kd.blueKnob;
  uint8_t bg = kd.greenButton;
  uint8_t br = kd.redButton;
  uint8_t bb = kd.blueButton;


  while (!bg && !br && !bb) {
    
    KnobsData nkd = getKnobsValue();

    uint8_t krn = nkd.redKnob;
    uint8_t kgn = nkd.greenKnob;
    uint8_t kbn = nkd.blueKnob;


    if (krn != kr || kbn != kb || kgn != kg) {
      gameMode = gameMode == 1 ? 2 : 1;
      
    }
    
    if (gameMode == 1) {
      highlightCurrentChoice(110, 110, 250, 85, 0x07df);
      highlightCurrentChoice(110, 190, 280, 85, 0x0000);
    }
    else if (gameMode == 2) {
      highlightCurrentChoice(110, 110, 250, 85, 0x0000);
      highlightCurrentChoice(110, 190, 280, 85, 0x07df);
    }
   
    for (int ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, menuBuffer[ptr]);
    }

    kr = krn;
    kg = kgn;
    kb = kbn;

    uint8_t bg = nkd.greenButton;
    uint8_t br = nkd.redButton;
    uint8_t bb = nkd.blueButton;
    if (bg || br || bb) {
      break;
    }

    unsigned int ms_count = 0;
    clock_t start_time = clock();
    while (ms_count < 100) {
        ms_count = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
    }

  }
  printf("Goodbye menu!\n");
  return gameMode;
} 

void draw_pixel_menu(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    menuBuffer[x+480*y] = color;
  }
}

int char_width(int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}
 
void draw_char(int x, int y, char ch, unsigned short color) {
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(x+scale*j, y+scale*i, color);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}
 
void draw_pixel_big(int x, int y, unsigned short color) {
  int i,j;
  for (i = 0; i < scale; i++) {
    for (j = 0; j < scale; j++) {
      draw_pixel_menu(x+i, y+j, color);
    }
  }
}

void draw_word(int x, int y, char* word, int offset,  unsigned short color) {
  int x1 = x;
  for (int ch = 0; ch < strlen(word); ch++) {
      draw_char(x1, y, (char) word[ch], color);
      x1 += offset;
  }
}

void highlightCurrentChoice(int x, int y, int w, int h, unsigned short color ) {
  for (int x1 = x; x1 < x + w; x1++) {
    for (int y1 = y; y1 < y + h; y1++) {
      if (menuBuffer[x1+480*y1] != 0xfe80) {
        draw_pixel_menu(x1, y1, color);
      }
    }
  }
}

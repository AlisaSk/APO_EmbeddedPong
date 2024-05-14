#include "botmenu.h"
#include "font_types.h"
#include "knobs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"

#include <time.h>
#include <string.h>

static unsigned short* menuBuffer;
static font_descriptor_t* fdes = &font_winFreeSystem14x16;

int startBotMenu(unsigned char* parlcd_mem_base) {
  menuBuffer = (unsigned short*) malloc(320*480*2);
  int difficulty = 1;
  for (int ptr = 0; ptr < 480*320 ; ptr++) {
        menuBuffer[ptr] = 0;
        parlcd_write_data(parlcd_mem_base, menuBuffer[ptr]);
    }

  draw_word(50, 30, "CHOOSE DIFFICULTY", 50, 0x90f6, 2);

  for (int ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, menuBuffer[ptr]);
    }

  return difficulty;
}





void draw_pixel_botmenu(int x, int y, unsigned short color) {
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
 
void draw_char(int x, int y, char ch, unsigned short color, int scale) {
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
          draw_pixel_big(x+scale*j, y+scale*i, color, scale);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}
 
void draw_pixel_big(int x, int y, unsigned short color, int scale) {
  int i,j;
  for (i = 0; i < scale; i++) {
    for (j = 0; j < scale; j++) {
      draw_pixel_botmenu(x+i, y+j, color);
    }
  }
}

void draw_word(int x, int y, char* word, int offset,  unsigned short color, int scale) {
  int x1 = x;
  for (int ch = 0; ch < strlen(word); ch++) {
      draw_char(x1, y, (char) word[ch], color, scale);
      x1 += offset;
  }
}

void highlightCurrentChoice(int x, int y, int w, int h, unsigned short color ) {
  for (int x1 = x; x1 < x + w; x1++) {
    for (int y1 = y; y1 < y + h; y1++) {
      if (menuBuffer[x1+480*y1] != 0xfe80) {
        draw_pixel_botmenu(x1, y1, color);
      }
    }
  }
}
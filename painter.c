#include "painter.h"
#include "font_types.h"

extern unsigned short *fb;
extern unsigned char *parlcd_mem_base;
font_descriptor_t* fdes = &font_winFreeSystem14x16;


void draw_word(int x, int y, char* word, int offset,  unsigned short color, int scale) {
  int x1 = x;
  for (int ch = 0; ch < strlen(word); ch++) {
      draw_char(x1, y, (char) word[ch], color, scale);
      x1 += offset;
  }
}

void draw_pixel_big(int x, int y, unsigned short color, int scale) {
  int i,j;
  for (i = 0; i < scale; i++) {
    for (j = 0; j < scale; j++) {
      if (x>=0 && x<480 && y>=0 && y<320) {
        draw_pixel(x+i, y+j, color);
      }
    }
  }
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
          draw_pixel_big(x+scale*j, y+scale*i, color, scale); // scale -- 4
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
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


void highlightCurrentChoice(int x, int y, int w, int h, unsigned short color) {
  for (int x1 = x; x1 < x + w; x1++) {
    for (int y1 = y; y1 < y + h; y1++) {
      if (fb[x1+480*y1] != 0xfe80) {
        draw_pixel(x1, y1, color);
      }
    }
  }
}


void drawRacket(Racket* racket, unsigned short color) {
  int x = racket->x;
  int y = racket->y;
  int w = racket->w;
  int h = racket->h;
  for (int x1 = x; x1 < w + x; x1 ++) {
    for (int y1 = y; y1 < y + h; y1++) {
      draw_pixel(x1, y1, color);
    }
  }
}

void drawBall (Ball* ball, unsigned short color) {
  int x = ball->x;
  int y = ball->y;
  int w = ball->w;
  int h = ball->h;
  for (int x1 = x; x1 < w + x; x1 ++) {
    for (int y1 = y; y1 < y + h; y1++) {
      draw_pixel(x1, y1, color);
    }
  }
}

void drawBackground(unsigned short color) {
    for (int ptr = 0; ptr < 480*320 ; ptr++) {
        fb[ptr] = color;
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
}

void renderLCD() {
    for (int ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }
}
 

void drawRectangle(unsigned short color1, unsigned short color2) {
    int xEdgeSpacing = 80;
    int yEdgeSpacing = 30;

    int recWidth = 320;
    int recHeight = 200;

    int colorSwitcher = -1;

    int side = 20;

    for (int x = xEdgeSpacing; x < xEdgeSpacing + recWidth; x += side) {
        for (int y = yEdgeSpacing; y < yEdgeSpacing + recHeight; y += side) {
            if (x == xEdgeSpacing || x == xEdgeSpacing + recWidth - side || y == yEdgeSpacing || y == yEdgeSpacing + recHeight - side) {
                colorSwitcher *= -1;
                unsigned short color;
                switch (colorSwitcher) {
                    case -1: 
                    color = color1;
                    break;
                default:

                    color = color2;
                    break;
                }
                for (int i=0; i<side; i++) {
                    for (int j=0; j<side; j++) {
                        fb[x+i+480*(y+j)] = color;
                    }
                }
                
            }
        }
        colorSwitcher *= -1;
    }
}
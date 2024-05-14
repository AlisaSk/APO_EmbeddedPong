#include "start.h"
#include "font_types.h"
#include "led.h"

#define WIDTH 480
#define HEIGHT 320

unsigned short *b;
static font_descriptor_t* fdesStart = &font_winFreeSystem14x16;


void startPage( unsigned char *parlcd_mem_base) {
    int ptr;
    b  = (unsigned short *)malloc(320*480*2);

    printf("Hello world\n");

    sleep(1);

    /*
    * Setup memory mapping which provides access to the peripheral
    * registers region of RGB LEDs, knobs and line of yellow LEDs.
    */


    for (ptr = 0; ptr < 480*320 ; ptr++) {
        b[ptr] = 0x0000;
        parlcd_write_data(parlcd_mem_base, b[ptr]);
    }

    initKnobs();
    KnobsData kd = getKnobsValue();
    uint8_t rb = kd.redButton;
    uint8_t gb = kd.greenButton;
    uint8_t bb = kd.blueButton;

    unsigned short color1 = 0xb15f;
    unsigned short color2 = 0x0000;
    drawRectangle(color1, color2);
    kd = getKnobsValue();
    rb = kd.redButton;
    gb = kd.greenButton;
    bb = kd.blueButton;

    draw_word_start(125, 65, "START", 50, 0xffff, 4);
    draw_word_start(145, 130, "PONG", 50, 0xffff, 4);
    for (ptr = 0; ptr < 480*320 ; ptr++) {
        parlcd_write_data(parlcd_mem_base, b[ptr]);
    }
    ledStartPage(15);

    int switcher = -1;
    int counterLeds = 0;
    while (!rb && !gb && !bb) {
        drawRectangle(color1, color2);
        switch (switcher) {
            case -1:
                draw_word_start(20, 265, "PRESS ANY BUTTON TO START", 18, 0xffff, 2);
                break;
            default:
                draw_word_start(20, 265, "PRESS ANY BUTTON TO START", 18, 0x0000, 2);
                break;
        }
        switcher *= -1;
    
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, b[ptr]);
        }
        unsigned short colorTemp = color1;
        color1 = color2;
        color2 = colorTemp;

        kd = getKnobsValue();
        rb = kd.redButton;
        gb = kd.greenButton;
        bb = kd.blueButton;

        // if (rb || gb || bb) {
        //     break;
        // }

        unsigned int ms_count = 0;
        clock_t start_time = clock();
        while (ms_count < 150) {
            ms_count = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
        }
        
        if (counterLeds == 10) {
            ledStartPage(10);
            counterLeds = 0;
        } else { 
            counterLeds++;
        }

    }
    

    printf("Goodbye start\n");
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
                        b[x+i+480*(y+j)] = color;
                    }
                }
                
            }
        }
        colorSwitcher *= -1;
    }
}

int char_width_start(int ch) {
  int width;
  if (!fdesStart->width) {
    width = fdesStart->maxwidth;
  } else {
    width = fdesStart->width[ch-fdesStart->firstchar];
  }
  return width;
}
 
void draw_char_start(int x, int y, char ch, unsigned short color, int scale) {
  int w = char_width_start(ch);
  const font_bits_t *ptr;
  if ((ch >= fdesStart->firstchar) && (ch-fdesStart->firstchar < fdesStart->size)) {
    if (fdesStart->offset) {
      ptr = &fdesStart->bits[fdesStart->offset[ch-fdesStart->firstchar]];
    } else {
      int bw = (fdesStart->maxwidth+15)/16;
      ptr = &fdesStart->bits[(ch-fdesStart->firstchar)*bw*fdesStart->height];
    }
    int i, j;
    for (i=0; i<fdesStart->height; i++) {

      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big_start(x+scale*j, y+scale*i, color, scale); // scale -- 4
        }
        val<<=1;
      }
      ptr++;
    }
  }
}
 
void draw_pixel_big_start(int x, int y, unsigned short color, int scale) {
  int i,j;
  for (i = 0; i < scale; i++) {
    for (j = 0; j < scale; j++) {
      if (x>=0 && x<480 && y>=0 && y<320) {
        b[x+i+480*(y+j)] = color;
        }
    }
  }
}

void draw_word_start(int x, int y, char* word, int offset,  unsigned short color, int scale) {
  int x1 = x;
  for (int ch = 0; ch < strlen(word); ch++) {
      draw_char_start(x1, y, (char) word[ch], color, scale);
      x1 += offset;
  }
}
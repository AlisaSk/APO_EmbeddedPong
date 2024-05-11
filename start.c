#include "start.h"
#include "font_types.h"

#define WIDTH 480
#define HEIGHT 320

unsigned short *b;


void startMenu( unsigned char *parlcd_mem_base) {
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
    // for (ptr = 0; ptr < 480*320 ; ptr++) {
    //   parlcd_write_data(parlcd_mem_base, b[ptr]);
    // }

    while (!rb && !gb && !bb) {
        kd = getKnobsValue();
        rb = kd.redButton;
        gb = kd.greenButton;
        bb = kd.blueButton;
        drawRectangle(color1, color2);
        for (ptr = 0; ptr < 480*320 ; ptr++) {
            parlcd_write_data(parlcd_mem_base, b[ptr]);
        }
        unsigned short colorTemp = color1;
        color1 = color2;
        color2 = colorTemp;
        unsigned int ms_count = 0;
        clock_t start_time = clock();

        while (ms_count < 300) {
            // Do nothing, just keep looping until desired time has elapsed
            ms_count = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;
        }
    }
    

    
    

    printf("Goodbye menu\n");
}


void draw_pixel_big(int x, int y, unsigned short color) {
  int i,j;
  for (i=0; i<20; i++) {
    for (j=0; j<20; j++) {
       b[x+i+480*(y+j)] = color;
    }
  }
}

void drawRectangle(unsigned short color1, unsigned short color2) {
    int xEdgeSpacing = 80;
    int yEdgeSpacing = 30;

    int recWidth = 320;
    int recHeight = 260;

    int colorSwitcher = -1;

    int side = 20;

    for (int x = xEdgeSpacing; x < xEdgeSpacing + recWidth; x += side) {
        
        for (int y = yEdgeSpacing; y < yEdgeSpacing + recHeight; y += side) {
            if (x == xEdgeSpacing || x == xEdgeSpacing + recWidth - side || y == yEdgeSpacing || y == yEdgeSpacing + recHeight - side) {
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
                colorSwitcher *= -1;
            }
        }
        colorSwitcher *= -1;
    }
}




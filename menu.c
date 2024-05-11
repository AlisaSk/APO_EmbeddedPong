#include "menu.h"
#include "font_types.h"

void startMenu(unsigned short *fb, unsigned char *parlcd_mem_base) {
    int ptr;
    fb  = (unsigned short *)malloc(320*480*2);

    printf("Hello world\n");

    sleep(1);

    /*
    * Setup memory mapping which provides access to the peripheral
    * registers region of RGB LEDs, knobs and line of yellow LEDs.
    */


    for (ptr = 0; ptr < 480*320 ; ptr++) {
        fb[ptr] = 0x7fb8;
        parlcd_write_data(parlcd_mem_base, fb[ptr]);
    }

    initKnobs();
    KnobsData kd = getKnobsValue();
    uint8_t rb = kd.redButton;
    uint8_t gb = kd.greenButton;
    uint8_t bb = kd.blueButton;

    while (!rb && !gb && !bb) {
        kd = getKnobsValue();
        rb = kd.redButton;
        gb = kd.greenButton;
        bb = kd.blueButton;
        printf("press  button\n");
    }


    printf("Goodbye menu\n");
}

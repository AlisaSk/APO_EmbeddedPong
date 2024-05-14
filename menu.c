#include "menu.h"
#include "font_types.h"
#include "knobs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "painter.h"
#include <time.h>
#include <string.h>



int startMenu() {
  
  int gameMode = 1;
  drawBackground(0x0000);

  draw_word(140, 30, "MENU", 50, 0x90f6, 4);
  draw_word(115, 120, "1 pLayer", 30, 0xfe80, 4);
  draw_word(115, 200, "2 pLayers", 30, 0xfe80, 4);

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
   
    renderLCD();

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


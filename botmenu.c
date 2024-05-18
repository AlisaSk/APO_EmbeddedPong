#include "botmenu.h"
#include "font_types.h"
#include "knobs.h"
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "painter.h"

#include <time.h>
#include <string.h>

/* This file contains all of the functions to load bot menu to choose difficulty*/

void startBotMenu() {
  printf("Bot menu\n");
  int difficulty = 1;
  unsigned short textColor = 0xfe80;
  drawBackground(0x0000);

  // adding difficulty page text
  draw_word(17, 30, "CHOOSE GAME MODE", 29, 0x007f, 3);
  draw_word(170, 100, "EASY", 29, textColor, 3);
  draw_word(170, 170, "NORMAL", 29, textColor, 3);
  draw_word(170, 250, "HARD", 29, textColor, 3);
  highlightCurrentChoice(165, 90, 130, 65, 0x07df, textColor);
  renderLCD();
  unsigned int msCount = 0;
  clock_t startTime = clock();
  while (msCount < 200) {
    msCount = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
  }
  

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

    // moving between the game mods
    if (krn != kr || kbn != kb || kgn != kg) {
      difficulty = difficulty == 3 ? 1 : difficulty + 1;
      
    }
    
    //coloring and highliting text
    if (difficulty == 1) {
      highlightCurrentChoice(165, 90, 130, 65, 0x07df, textColor);
      highlightCurrentChoice(165, 160, 210, 65, 0x0000, textColor);
      highlightCurrentChoice(165, 240, 140, 65, 0x0000, textColor);
    }
    else if (difficulty == 2) {
      highlightCurrentChoice(165, 90, 130, 65, 0x0000, textColor);
      highlightCurrentChoice(165, 160, 210, 65, 0x07df, textColor);
      highlightCurrentChoice(165, 240, 140, 65, 0x0000, textColor);
    }
    else if (difficulty == 3) {
      highlightCurrentChoice(165, 90, 130, 65, 0x0000, textColor);
      highlightCurrentChoice(165, 160, 210, 65, 0x0000, textColor);
      highlightCurrentChoice(165, 240, 140, 65, 0x07df, textColor);
    }
   
    renderLCD();

    // update knob position
    kr = krn;
    kg = kgn;
    kb = kbn;

    uint8_t bg = nkd.greenButton;
    uint8_t br = nkd.redButton;
    uint8_t bb = nkd.blueButton;
    if (bg || br || bb) {
      break;
    }

    unsigned int msCount = 0;
    clock_t startTime = clock();
    while (msCount < 200) {
        msCount = (clock() - startTime) * 1000 / CLOCKS_PER_SEC;
    }

  }

  printf("Goodbye bot menu!\n");
  playGameBot(difficulty);
}

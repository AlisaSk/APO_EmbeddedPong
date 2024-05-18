#ifndef KNOBS_H
#define KNOBS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


typedef struct {
    uint8_t redKnob;
    uint8_t greenKnob;
    uint8_t blueKnob;
    bool redButton;
    bool greenButton;
    bool blueButton;
} KnobsData;

static unsigned char *memBase;

bool initKnobs();

KnobsData getKnobsValue();


#endif

#include "mzapo_regs.h"

#include "knobs.h"
 
static KnobsData *lastKnobsData;


bool initKnobs() {
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (mem_base == NULL) {
        fprintf(stderr, "ERROR_KNOBS: Memory allocation failed\n");
        return false;
    }

    KnobsData initialKnobsData = getKnobsValue();

    lastKnobsData = malloc(sizeof(KnobsData));  // Allocate memory for storing the previous knob data
    if (lastKnobsData == NULL) {
        fprintf(stderr, "ERROR_KNOBS: Memory allocation failed\n");
        return false;
    }
    *lastKnobsData = initialKnobsData; 
    
    return true;
}

KnobsData getKnobsValue() {
    int32_t rgbKnobsValue = *(volatile uint32_t *)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    KnobsData ret = {
        .redKnob = (rgbKnobsValue >> 16) & 0xFF,  
        .greenKnob = (rgbKnobsValue >> 8) & 0xFF,   
        .blueKnob = (rgbKnobsValue >> 0) & 0xFF,   
        .redButton = (rgbKnobsValue >> 26) & 1,     
        .greenButton = (rgbKnobsValue >> 25) & 1,  
        .blueButton = (rgbKnobsValue >> 24) & 1    
    };
    return ret;
}

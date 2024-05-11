#include <stdint.h>
#include "mzapo_regs.h"
#include <stdbool.h>


uint32_t get_knobs_value(unsigned char *mem_base) {
  

}

bool knobsInit {
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (mem_base == NULL) {
        fprintf(stderr, "ERROR: Physical address could not be mapped!\n");
        ret = false;
    }
    // setting the starting values of knobs
    knobs_data kd = knobs_value();
    rk = kd.rk;
    gk = kd.gk;
    bk = kd.bk;
    return ret;
}

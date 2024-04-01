#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"


int get_bit(uint16_t reg, uint16_t ind) {
    //get the ind-th bit of reg
    uint16_t mask = 1;
    mask = mask << ind;
    return (reg & mask) >> ind;
}

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    uint16_t newBit = get_bit(*reg, 0) ^ get_bit(*reg, 2) ^ get_bit(*reg, 3) ^ get_bit(*reg, 5);
    *reg = *reg >> 1;
    newBit = newBit << 15;
    * reg = *reg | newBit;
}


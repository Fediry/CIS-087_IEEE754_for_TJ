#pragma once

#include "main.h"

using namespace std;

// IEEE 754 single-precision float constants
uint8_t const width = 32U;
uint8_t const exp_width = 8U;
uint8_t const mantissa_width = width - exp_width - 1;
uint8_t const bias = 127U;

class ieee754 {
   public:
    ieee754() {}
    // using rule of zero

    float ieee_754(uint32_t const data);
};
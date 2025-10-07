#pragma once

#include "main.h"

using namespace std;

// IEEE 754 single-precision float constants
uint8_t const width = 32U;
uint8_t const exp_width = 8U;
uint8_t const mantissa_width = width - exp_width - 1;
uint8_t const bias = 127U;

class ieee754 {
   private:
    uint32_t bitwise_multiply(uint32_t a, uint32_t b);
    uint32_t bitwise_add(uint32_t a, uint32_t b);
    bool read_bits(uint32_t num, uint32_t n);
    bool read_bits(uint32_t num, uint32_t n, uint32_t m);

   public:
    ieee754() {}
    // using rule of zero

    float ieee_754(uint32_t const data);
};
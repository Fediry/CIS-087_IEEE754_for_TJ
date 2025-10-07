#pragma once

#include "main.h"

using namespace std;

// IEEE 754 single-precision float constants
uint8_t const width = 32U;
uint8_t const exp_width = 8U;
uint8_t const mantissa_width = width - exp_width - 1;
uint8_t const bias = 127U;
uint32_t const sign_mask = 0xFFFFFFFF;
uint32_t const exp_mask = 0x7F800000;
uint32_t const mantissa_mask = 0x7FFFFF;

class ieee754 {
   private:
    uint32_t bitwise_multiply(uint32_t a, uint32_t b);
    uint32_t bitwise_add(uint32_t a, uint32_t b);
    bool read_bit(uint32_t data, uint32_t n);
    uint32_t read_bit_segments(uint32_t data, uint32_t mask, uint32_t shift);

   public:
    ieee754() {}
    // using rule of zero

    float ieee_754(uint32_t const data);
};
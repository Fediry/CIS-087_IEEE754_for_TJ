#pragma once

#include "main.h"

using namespace std;

// IEEE 754 single-precision float constants
uint8_t const width = 32U;
uint8_t const exp_width = 8U;
uint8_t const mantissa_width = width - exp_width - 1U;
uint8_t const bias = 127U;

// Bit masks mapped to the segments of the IEEE 754 32-bit binary
// (Used hex for ease of reading)
uint32_t const sign_mask = 0xFFFFFFFF;       // 32'nd bit
uint32_t const exp_mask = 0x7F800000;        // 31'st to 23'rd bits
uint32_t const mantissa_mask = 0x7FFFFF;     // 22'nd to 0'th bits
uint32_t const leading_bit_mask = 0x800000;  // 24'th bit of mantissa (implicit bit)

class ieee754 {
   private:
    uint32_t bitwise_add(uint32_t a, uint32_t b);
    uint32_t bitwise_multiply(uint32_t a, uint32_t b);
    uint32_t bitwise_power(uint32_t a, uint32_t b);
    uint32_t read_bit_segments(uint32_t const data, uint32_t const mask, uint32_t const shift);
    uint32_t get_sign(uint32_t const data);
    int32_t get_exponent(uint32_t const data);
    uint32_t get_raw_mantissa(uint32_t const data);

   public:
    ieee754() {}
    // using rule of zero

    float ieee_754(uint32_t const data);
};
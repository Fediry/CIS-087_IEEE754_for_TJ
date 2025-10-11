#include "ieee_754.h"

using namespace std;

// read bits from data at mask bits and shift right to pull out segments
uint32_t ieee754::read_bit_segments(uint32_t const &data, uint32_t const mask, uint32_t const shift) {
    uint32_t result = data & mask;
    result = result >> shift;
    return result;
}

uint32_t ieee754::get_sign(uint32_t const &data) { return read_bit_segments(data, sign_mask, (width - 1U)); }

int32_t ieee754::get_exponent(uint32_t const &data) {
    int32_t raw_exponent = read_bit_segments(data, exp_mask, mantissa_width);
    return raw_exponent - bias;
}

uint32_t ieee754::get_raw_mantissa(uint32_t const &data) {
    uint32_t raw_mantissa = read_bit_segments(data, mantissa_mask, 0U);
    return raw_mantissa;
}

float ieee754::ieee_754(uint32_t const &data) {
    uint32_t sign_bit = get_sign(data);
    int8_t sign = (sign_bit == 0) ? 1 : -1;

    int32_t exponent = get_exponent(data);
    uint32_t raw_mantissa = get_raw_mantissa(data);

    uint8_t leading_bit = 1;

    float mantissa = leading_bit + (raw_mantissa * pow(2, -mantissa_width));
    float output_float = sign * (mantissa)*pow(2, exponent);
    return output_float;
}
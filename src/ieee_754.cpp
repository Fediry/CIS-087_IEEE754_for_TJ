#include "ieee_754.h"

using namespace std;

/* Multiply a and b by doubling a and halfing b until b is zero.
 * When b is odd during this process, add a to the result.
 */
uint32_t ieee754::bitwise_multiply(uint32_t a, uint32_t b) {
    uint32_t result = 0;

    while (b > 0) {
        if (b & 1) {
            result += a;
        }

        a = a << 1;
        b = b >> 1;
    }
    return result;
}

/* Adding a and b by XORing them for the base add, and getting the carry by ANDing them and
 * left shifting that by 1. When b is zero, a is the result.
 */
uint32_t ieee754::bitwise_add(uint32_t a, uint32_t b) {
    uint32_t result;

    while (b > 0) {
        uint32_t result = a ^ b;
        uint32_t carry = (a & b) << 1;
        a = result;
        b = carry;
    }
    return result;
}

bool ieee754::read_bit(uint32_t data, uint32_t n) { return data & (1 << n); }

// read bits from data at mask bits and shift to pull out segments
uint32_t ieee754::read_bit_segments(uint32_t const data, uint32_t const mask, uint32_t const shift) {
    uint32_t result = data & mask;
    result = result >> shift;
    return result;
}

uint32_t ieee754::get_sign(uint32_t const data) { return read_bit_segments(data, sign_mask, width - 1); }

int32_t ieee754::get_exponent(uint32_t const data) {
    int32_t raw_exponent = read_bit_segments(data, exp_mask, mantissa_width);
    return raw_exponent - bias;
}

uint32_t ieee754::get_raw_mantissa(uint32_t const data) {
    uint32_t raw_mantissa = read_bit_segments(data, mantissa_mask, 0);
    return raw_mantissa;
}

float ieee754::ieee_754(uint32_t const data) {
    uint32_t sign_bit = get_sign(data);
    int32_t exponent = get_exponent(data);
    uint32_t raw_mantissa = get_raw_mantissa(data);

    float mantissa = (1 + raw_mantissa * pow(2, -23));
    float output_float = pow(-1, sign_bit) * pow(2, exponent) * (mantissa);
    return output_float;
}
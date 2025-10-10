#include "ieee_754.h"

using namespace std;

/* Adding a and b by XORing them for the base add, and getting the carry by ANDing them and
 * left shifting that by 1. When b is zero, a is the result.
 */
uint32_t ieee754::bitwise_add(uint32_t a, uint32_t b) {
    uint32_t result;

    while (b > 0U) {
        uint32_t result = a ^ b;
        uint32_t carry = (a & b) << 1U;
        a = result;
        b = carry;
    }
    return result;
}

/* Multiply a and b by doubling a and halfing b until b is zero.
 * When b is odd during this process, add a to the result.
 */
uint32_t ieee754::bitwise_multiply(uint32_t a, uint32_t b) {
    uint32_t result = 0U;

    while (b > 0U) {
        if (b & 1U) {
            result += a;
        }

        a = a << 1U;
        b = b >> 1U;
    }
    return result;
}

uint32_t ieee754::bitwise_power(uint32_t a, uint32_t b) {}

// read bits from data at mask bits and shift right to pull out segments
uint32_t ieee754::read_bit_segments(uint32_t const data, uint32_t const mask, uint32_t const shift) {
    uint32_t result = data & mask;
    result = result >> shift;
    return result;
}

uint32_t ieee754::get_sign(uint32_t const data) { return read_bit_segments(data, sign_mask, (width - 1U)); }

int32_t ieee754::get_exponent(uint32_t const data) {
    int32_t raw_exponent = read_bit_segments(data, exp_mask, mantissa_width);
    return raw_exponent - bias;
}

uint32_t ieee754::get_raw_mantissa(uint32_t const data) {
    uint32_t raw_mantissa = read_bit_segments(data, mantissa_mask, 0U);
    return raw_mantissa;
}

float ieee754::ieee_754(uint32_t const data) {
    uint32_t sign_bit = get_sign(data);
    int8_t sign = (sign_bit == 0) ? 1 : -1;

    int32_t exponent = get_exponent(data);
    uint32_t raw_mantissa = get_raw_mantissa(data);

    uint8_t leading_bit = 1;
    // // check for denormalized state
    // if (exponent == 0U && raw_mantissa != 0U) {
    //     leading_bit = 0;
    // }

    float mantissa = (leading_bit + raw_mantissa * pow(2U, -mantissa_width));
    float output_float = sign * (mantissa)*pow(2U, exponent);
    return output_float;
}
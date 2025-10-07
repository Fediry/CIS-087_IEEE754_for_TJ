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
uint32_t ieee754::read_bit_segments(uint32_t data, uint32_t mask, uint32_t shift) {
    // uint32_t shifted_data = data >> start;
    // cout << " shifted_data: " << shifted_data;

    // uint32_t mask = (1 << end) - 1;
    // cout << "  mask: " << mask;

    // uint32_t result = shifted_data & mask;
    // cout << "  result: " << result << endl;

    uint32_t sign_mask = 0xFFFFFFFF;
    uint32_t sign = data & sign_mask;
    cout << "sign: " << (sign >> 31);
    uint32_t exp_mask = 0x7F800000;
    uint32_t result = data & exp_mask;
    cout << "  exp: " << ((result >> 23) - 127);
    uint32_t mantissa_mask = 0x7FFFFF;
    uint32_t result_m = data & mantissa_mask;
    cout << "  mantissa: " << (result_m) << endl;

    return result;
}

float ieee754::ieee_754(uint32_t const data) {
    float value;
    bool sign_bit = read_bit(data, width - 1);
    cout << "sign_bit: " << sign_bit << endl;

    uint8_t raw_exponent = read_bits(data, 1, exp_width);
    uint8_t exponent = raw_exponent - bias;

    uint32_t mantissa;

    // if exp = 0 and mant != 0, use denormalized form {mantissa leading bit = 0}
    uint8_t leading_m_bit = 1;
    if (exponent == 0 && mantissa != 0) {
        leading_m_bit = 0;
    }

    // value = (2 ^ exponent) * (-1 ^ sign_bit) * (leading_m_bit + mantissa);
    value = -1.5;
    return value;
}
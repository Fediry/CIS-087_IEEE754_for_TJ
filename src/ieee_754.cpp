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
uint32_t ieee754::read_bit_segments(uint32_t data, uint32_t mask, uint32_t shift) {
    uint32_t result = data & mask;
    result = result >> shift;
    return result;
}

float ieee754::ieee_754(uint32_t const data) {
    float output;
    // bool sign_bit = read_bit(data, width - 1);
    bool sign_bit = read_bit_segments(data, sign_mask, width - 1);
    cout << "sign_bit: " << sign_bit;

    uint32_t raw_exponent = read_bit_segments(data, exp_mask, mantissa_width);
    uint32_t exponent = raw_exponent - bias;
    cout << " exp: " << bitset<exp_width>(raw_exponent);

    uint32_t mantissa = read_bit_segments(data, mantissa_mask, 0);
    cout << " mantissa: " << bitset<mantissa_width>(mantissa);

    cout << " empty output: " << bitset<width>(output) << endl;
    // if exp = 0 and mant != 0, use denormalized form {mantissa leading bit = 0}
    uint32_t leading_m_bit = 1;
    if (exponent == 0 && mantissa != 0) {
        leading_m_bit = 0;
    }

    output = (-1 ^ sign_bit) * (2 ^ exponent) * (leading_m_bit + mantissa);

    cout << " filled output: " << bitset<width>(output) << endl;
    return output;
}
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

float ieee754::ieee_754(uint32_t const data) {
    float value;
    // This will fail the tests. Students should do the proper IEEE-754 calculation per assignment
    // using the 32 bit 'data' value passed into this function.
    value = 1.23;
    return value;
}
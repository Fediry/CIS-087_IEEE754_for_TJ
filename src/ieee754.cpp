#include "ieee754.h"

using namespace std;

// IEEE 754 single-precision float constants
uint8_t const width = 32U;
uint8_t const exp_width = 8U;
uint8_t const mantissa_width = width - exp_width - 1;
uint8_t const bias = 127U;

/*
 * *** STUDENTS SHOULD WRITE CODE FOR THIS FUNCTION ***
 * Students should create or add any data structures needed.
 * Students should create or add any functions or classes they may need.
 */
float ieee_754(uint32_t const data) {
    float value;
    // This will fail the tests. Students should do the proper IEEE-754 calculation per assignment
    // using the 32 bit 'data' value passed into this function.
    value = 1.23;
    return value;
}
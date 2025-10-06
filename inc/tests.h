#pragma once

#include "main.h"

using namespace std;

#define NUM_TESTS 10
#define MAX_VALUE 100
#define MIN_VALUE -100
uint8_t const table_width[] = {12, 12, 35, 12};

class tests {
   private:
    void header();
    void print_row(bool const test_success, float const rand_val, uint32_t const val_int, float const ieee_754_value);
    template <typename T>
    T rand_min_max(T const min, T const max);

   public:
    tests() {}
    // using rule of zero

    bool test();
};
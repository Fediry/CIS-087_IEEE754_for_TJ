#include "tests.h"

using namespace std;

/*
 * *** STUDENTS SHOULD NOT NEED TO CHANGE THE CODE BELOW. IT IS A CUSTOM TEST HARNESS. ***
 */

void header() {
    cout << left << setw(table_width[0]) << setfill(' ') << "pass/fail";
    cout << left << setw(table_width[1]) << setfill(' ') << "value";
    cout << left << setw(table_width[2]) << setfill(' ') << "bits";
    cout << left << setw(table_width[3]) << setfill(' ') << "IEEE-754" << endl;

    cout << left << setw(table_width[0]) << setfill(' ') << "--------";
    cout << left << setw(table_width[1]) << setfill(' ') << "--------";
    cout << left << setw(table_width[2]) << setfill(' ') << "--------";
    cout << left << setw(table_width[3]) << setfill(' ') << "--------" << endl;
}

void print_row(bool const test_success, float const rand_val, uint32_t const val_int, float const ieee_754_value) {
    // print results
    string const pass_fail = test_success ? "PASS" : "FAIL";
    cout << left << setw(table_width[0]) << setfill(' ') << pass_fail;
    cout << left << setw(table_width[1]) << setfill(' ') << rand_val;
    cout << left << setw(table_width[2]) << setfill(' ') << bitset<width>(val_int);
    cout << left << setw(table_width[3]) << setfill(' ') << ieee_754_value << endl;
}

template <typename T>
T rand_min_max(T const min, T const max) {
    T const rand_val = min + static_cast<double>(static_cast<double>(rand())) / (static_cast<double>(RAND_MAX / (max - min)));
    return rand_val;
}

bool test() {
    // the union
    union float_uint {
        float val_float;
        uint32_t val_int;
    } data;

    // print header
    header();

    // seed the random number generator
    srand(time(NULL));

    bool success = true;
    uint16_t pass = 0;
    for (size_t i = 0; i < NUM_TESTS; i++) {
        // random value
        float const rand_val = rand_min_max<float>(MIN_VALUE, MAX_VALUE);

        data.val_float = rand_val;

        // calculate using ieee_754 function
        float ieee_754_value = ieee_754(data.val_int);

        // test the results
        float const epsilon = std::numeric_limits<float>::epsilon();
        bool test_success = (abs(ieee_754_value - rand_val) < epsilon);
        if (test_success) {
            pass += 1;
        }

        // print row
        print_row(test_success, rand_val, data.val_int, ieee_754_value);
    }

    // summarize results
    cout << "-------------------------------------------" << endl;
    if (pass == NUM_TESTS) {
        cout << "SUCCESS ";
    } else {
        cout << "FAILURE ";
    }
    cout << pass << "/" << NUM_TESTS << " passed" << endl;
    cout << "-------------------------------------------" << endl;

    return success;
}
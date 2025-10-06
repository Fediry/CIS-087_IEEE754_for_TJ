#include "main.h"

#include "tests.h"

using namespace std;

int main() {
    tests test;

    if (!test.test()) {
        return -1;
    }
    return 0;
}
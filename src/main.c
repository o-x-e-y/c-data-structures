#include "../tests/ovec_tests.h"
#include "../tests/ostring_tests.h"
#include "../tests/oslice_tests.h"

int main(int argc, char** argv) {
    test_vec();
    test_string();
    test_slice();

    return 0;
}
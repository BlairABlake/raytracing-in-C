//
// Created by ryousuke kaga on 2023/09/25.
//
#include "tests.h"
#include "tuple_test.h"
#include "color_test.h"
#include "canvas_test.h"
#include "matrix_test.h"

MunitTest tests[] = {
        TUPLE_TESTS,
        COLOR_TESTS,
        CANVAS_TESTS,
        MATRIX_TESTS
};

static const MunitSuite suite = {
        "/my-tests/", /* name */
        tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
};


int main (int argc, const char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_COLOR_TEST_H
#define RAYTRACING_IN_C_COLOR_TEST_H

#include "tests.h"
#include "color.h"
#include "tuple.h"

TEST(test_color_instantiation) {
    color_t c = color(-0.5, 0.4, 1.7);
    munit_assert(c.red == -0.5f);
    munit_assert(c.green == 0.4f);
    munit_assert(c.blue == 1.7f);
}

TEST(test_color_comparison) {
    color_t c1 = color(-0.5, 0.4, 1.7);
    color_t c2 = color(-0.5, 0.4, 1.7);
    munit_assert(color_cmp(c1, c2));
}

TEST(test_color_to_tuple) {
    color_t c = color(0.9, 0.6, 0.75);
    tuple_t t = vector(0.9, 0.6, 0.75);
    munit_assert(tuple_cmp(color_to_tuple(c), t));
}

TEST(test_tuple_to_color) {
    color_t c = color(0.9, 0.6, 0.75);
    tuple_t t = vector(0.9, 0.6, 0.75);
    munit_assert(color_cmp(c, tuple_to_color(t)));
}

#define COLOR_TESTS \
    {               \
        "color_instantiation", \
        test_color_instantiation, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "color_to_tuple", \
        test_color_to_tuple, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    },              \
    {               \
        "tuple_to_color", \
        test_tuple_to_color, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL\
    }
#endif //RAYTRACING_IN_C_COLOR_TEST_H

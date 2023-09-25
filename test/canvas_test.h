//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_CANVAS_TEST_H
#define RAYTRACING_IN_C_CANVAS_TEST_H

#include "tests.h"

TEST(test_canvas_instantiation) {
    canvas_t c = canvas(10, 20);
    canvas_init(&c);

    color_t c_i = color(0, 0, 0);

    munit_assert(c.width == 10);
    munit_assert(c.height == 20);
    for(int i=0; i < c.width*c.height; i++) {
        munit_assert(color_cmp(c_i, c.pixels[i]));
    }

    canvas_free(&c);
}

TEST(test_canvas_write) {
    canvas_t c = canvas(10, 20);
    canvas_init(&c);
    color_t red = color(1, 0, 0);
    canvas_write(&c, 2, 3, red);
    munit_assert(color_cmp(canvas_at(&c, 2, 3), red));
}

TEST(test_canvas_write_ppm) {
    canvas_t c = canvas(100, 100);
    canvas_init(&c);
    color_t red = color(255, 0, 0);
    canvas_write(&c, 1, 1, red);
    FILE* f = fopen("./test.ppm", "w");
    canvas_write_ppm(&c, f);
    canvas_free(&c);
    fclose(f);
    return MUNIT_OK;
}

#define CANVAS_TESTS \
    {                \
        "canvas_instantiation", \
        test_canvas_instantiation, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "canvas_write", \
        test_canvas_write, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "canvas_write_ppm", \
        test_canvas_write_ppm, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    }
#endif //RAYTRACING_IN_C_CANVAS_TEST_H

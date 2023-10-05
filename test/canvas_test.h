//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_CANVAS_TEST_H
#define RAYTRACING_IN_C_CANVAS_TEST_H

#include "tests.h"

TEST(test_canvas_write_ppm) {
    int width = 100;
    int height = 200;
    tuple_t red = tuple(1, 0, 0, 0);
    tuple_t pixels[height][width];
    canvas_fill(width, height, pixels, red);
    FILE* fp = fopen("canvas_test.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);
    fclose(fp);
    return MUNIT_OK;
}

#define CANVAS_TESTS \
    {                \
        "canvas_write_ppm", \
        test_canvas_write_ppm, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    }
#endif //RAYTRACING_IN_C_CANVAS_TEST_H

//
// Created by ryousuke kaga on 2023/09/27.
//

#ifndef RAYTRACING_IN_C_LIGHT_TEST_H
#define RAYTRACING_IN_C_LIGHT_TEST_H

#include "tests.h"

TEST(test_point_light_instantiation) {
    tuple_t position = point(0, 0, 0);
    color_t intensity = color(1, 1, 1);
    point_light_t l = point_light(position, intensity);

    munit_assert(tuple_cmp2(position, l.position));
    munit_assert(color_cmp(intensity, l.intensity));
}

#define LIGHT_TESTS \
    {               \
        "point_light_instantiation", \
        test_point_light_instantiation, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,      \
        NULL\
    }


#endif //RAYTRACING_IN_C_LIGHT_TEST_H

//
// Created by ryousuke kaga on 2023/09/27.
//

#ifndef RAYTRACING_IN_C_MATERIAL_TEST_H
#define RAYTRACING_IN_C_MATERIAL_TEST_H

#include "tests.h"

TEST(test_material_instantiation) {
    color_t c = color(1, 1, 1);
    float ambient = 0.1f;
    float diffuse = 0.9f;
    float specular = 0.9f;
    float shininess = 200.0f;
    material_t m = material(c, ambient, diffuse, specular, shininess);

    munit_assert(color_cmp2(c, m.color));
    munit_assert(float_cmp2(ambient, m.ambient));
    munit_assert(float_cmp2(diffuse, m.diffuse));
    munit_assert(float_cmp2(specular, m.specular));
    munit_assert(float_cmp2(shininess, m.shininess));

    return MUNIT_OK;
}

TEST(test_lightning) {
    material_t m = material(color(1, 1, 1), 0.1 ,0.9, 0.9, 200.0);
    tuple_t position = point(0, 0, 0);
    tuple_t eyev = vector(0, 0, -1);
    tuple_t normalv = vector(0, 0, -1);
    point_light_t light = point_light(point(0, 0, -10), color(1, 1, 1));

    munit_assert(color_cmp2(color(1.9, 1.9, 1.9), lighting(m, light, position, eyev, normalv)));

    eyev = vector(0, 1/ sqrtf(2), -1/ sqrtf(2));
    munit_assert(color_cmp2(color(1.0, 1.0, 1.0), lighting(m, light, position, eyev, normalv)));

    eyev = vector(0, 0, -1);
    light = point_light(point(0, 10, -10), color(1, 1, 1));
    munit_assert(color_cmp2(color(0.7364, 0.7364, 0.7364), lighting(m, light, position, eyev, normalv)));

    eyev = vector(1, -1/ sqrtf(2), -1/ sqrtf(2));
    munit_assert(color_cmp2(color(1.6364, 1.6364, 1.6364), lighting(m, light, position, eyev, normalv)));

    eyev = vector(0, 0, -1);
    light = point_light(point(0, 0, 10), color(1, 1, 1));
    munit_assert(color_cmp2(color(0.1, 0.1, 0.1), lighting(m, light, position, eyev, normalv)));

    return MUNIT_OK;
}


#define MATERIAL_TESTS \
    {                 \
        "material_instantiation", \
        test_material_instantiation, \
        NULL,         \
        NULL,         \
        MUNIT_TEST_OPTION_NONE,   \
        NULL\
    },                 \
    {                 \
        "lightning", \
        test_lightning, \
        NULL,         \
        NULL,         \
        MUNIT_TEST_OPTION_NONE,   \
        NULL\
    }

#endif //RAYTRACING_IN_C_MATERIAL_TEST_H

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

    munit_assert(color_cmp(c, m.color));
    munit_assert(float_cmp2(ambient, m.ambient));
    munit_assert(float_cmp2(diffuse, m.diffuse));
    munit_assert(float_cmp2(specular, m.specular));
    munit_assert(float_cmp2(shininess, m.shininess));
}


#define MATERIAL_TESTS \
    {                 \
        "material_instantiation", \
        test_material_instantiation, \
        NULL,         \
        NULL,         \
        MUNIT_TEST_OPTION_NONE,   \
        NULL\
    }

#endif //RAYTRACING_IN_C_MATERIAL_TEST_H

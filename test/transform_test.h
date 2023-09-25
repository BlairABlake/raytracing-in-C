//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_TRANSFORM_TEST_H
#define RAYTRACING_IN_C_TRANSFORM_TEST_H

#include "tests.h"

TEST(test_tuple_translation) {
    tuple_t t = point(1.0f, 1.0f, 1.0f);
    munit_assert(tuple_cmp2(point(2.0f, 2.0f, 2.0f), tuple_transform(&t, translation_matrix(vector(1.0f, 1.0f, 1.0f)))));

    return MUNIT_OK;
}

TEST(test_tuple_rotation) {
        tuple_t t = vector(1.0f, 1.0f, 1.0f);
        tuple_t tx = vector(1.0f, -1.0f, 1.0f);
        tuple_t ty = vector(1.0f, 1.0f, -1.0f);
        tuple_t tz = vector(-1.0f, 1.0f, 1.0f);

        float rad = M_PI / 2;

        munit_assert(tuple_cmp2(tuple_transform(&t, rotation_x_matrix(rad)), tx));
        munit_assert(tuple_cmp2(tuple_transform(&t, rotation_y_matrix(rad)), ty));
        munit_assert(tuple_cmp2(tuple_transform(&t, rotation_z_matrix(rad)), tz));

        return MUNIT_OK;
}

#define TRANSFORM_TESTS \
    {                   \
        "tuple_translation", \
        test_tuple_translation, \
        NULL,           \
        NULL,           \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },                    \
    {                   \
        "tuple_rotation", \
        test_tuple_rotation, \
        NULL,           \
        NULL,           \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //RAYTRACING_IN_C_TRANSFORM_TEST_H

//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_SPHERE_TEST_H
#define RAYTRACING_IN_C_SPHERE_TEST_H

#include "tests.h"

TEST(test_sphere_instantiation) {
    tuple_t center = point(0, 0, 0);
    float radius = 1.0f;
    sphere_t s = sphere(center, radius);

    munit_assert(tuple_cmp2(s.center, center));
    munit_assert(float_cmp2(s.radius, radius));

    return MUNIT_OK;
}

TEST(test_sphere_hit) {
    sphere_t s = sphere(point(0, 0, 0), 1.0f);
    ray_t r = ray(point(0, 0, 0), vector(1, 1, 0));

    tuple_t hits[2];
    int hit_n = 0;
    sphere_hit(&s, &r, hits, &hit_n);

    munit_assert(hit_n == 2);
    munit_assert(tuple_cmp2(hits[0], point(cosf(M_PI / 4), sinf(M_PI / 4), 0)));
    munit_assert(tuple_cmp2(hits[1], point(cosf(M_PI / 4 * 5), sinf(M_PI / 4 * 5), 0)));

    return MUNIT_OK;
}

#define SPHERE_TESTS \
    {                \
        "sphere_instantiation", \
        test_sphere_instantiation, \
        NULL,        \
        NULL,        \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },               \
    {                \
        "sphere_hit", \
        test_sphere_hit, \
        NULL,        \
        NULL,        \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAYTRACING_IN_C_SPHERE_TEST_H

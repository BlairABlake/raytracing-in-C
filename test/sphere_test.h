//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_SPHERE_TEST_H
#define RAYTRACING_IN_C_SPHERE_TEST_H

#include "tests.h"

TEST(test_sphere_hit) {
    ray_t ray = ray(point(-2, -2, 0), vector(1, 1, 0));
    object_t sphere;
    object_init(&sphere);

    List hits = sphere_hit(&sphere, ray);
    ListElm* hit = hits.head;

    hit_t* hit1 = (hit_t*)hit->data;
    munit_assert(tuple_cmp2(hit1->position, point(cos(M_PI/4 * 5), sin(M_PI/4 * 5), 0)));

    hit_t* hit2 = (hit_t*)hit->next->data;
    munit_assert(tuple_cmp2(hit2->position, point(cos(M_PI/4), sin(M_PI/4), 0)));

    return MUNIT_OK;
}

#define SPHERE_TESTS \
    {                \
        "sphere_hit", \
        test_sphere_hit, \
        NULL,        \
        NULL,        \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //RAYTRACING_IN_C_SPHERE_TEST_H

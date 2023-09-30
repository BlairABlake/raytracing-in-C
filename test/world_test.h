//
// Created by ryousuke kaga on 2023/09/29.
//

#ifndef RAYTRACING_IN_C_WORLD_TEST_H
#define RAYTRACING_IN_C_WORLD_TEST_H

#include "tests.h"

TEST(test_world_instantiation) {
    world_t w = world();

    munit_assert(ll_length(w.objects) == 0);
    munit_assert(ll_length(w.lights) == 0);

    world_free(&w);

    return MUNIT_OK;
}

TEST(test_world_add) {
    world_t w = world();
    point_light_t light = point_light(point(-10, 10, -10), color(1, 1, 1));
    material_t m = material(color(0.8, 1.0, 0.6), 0, 0.7, 0.2, 1);
    sphere_t s1 = sphere_null(point(0, 0, 0), 10, m);
    sphere_t s2 = sphere(point(20, 20, 20), 10, scale_matrix(vector(0.5, 0.5, 0.5)), m);

    world_add(&w, &light, "light");
    world_add(&w, &s1, "sphere");
    world_add(&w, &s2, "sphere");

    munit_assert(&light == w.lights->next->data);
    munit_assert(&s1 == w.objects->next->data);

    return MUNIT_OK;
}

TEST(test_world_intersection) {
    world_t w = world();
    material_t m = material(color(0.8, 1.0, 0.6), 0, 0.7, 0.2, 1);
    sphere_t s1 = sphere_null(point(0, 0, 0), 1.0f, m);
    ray_t r = ray(point(0, -5, -5), vector(0, 1, 1));
    world_add(&w, &s1, "sphere");

    struct ll_node *intersections = world_intersect(&w, &r);
    munit_assert(strcmp(intersections->next->name, "sphere") == 0);
    munit_assert(((struct hit_s*)intersections->next->data)->object == &s1);

    tuple_t hit_p = ray_position(&r, ((struct hit_s*)intersections->next->data)->t);
    munit_assert(tuple_cmp2(hit_p, point(0, -1/sqrtf(2), -1/sqrtf(2))));

    intersections = intersections->next;

    munit_assert(strcmp(intersections->next->name, "sphere") == 0);
    munit_assert(((struct hit_s*)intersections->next->data)->object == &s1);

    hit_p = ray_position(&r, ((struct hit_s*)intersections->next->data)->t);
    munit_assert(tuple_cmp2(hit_p, point(0, 1/sqrtf(2), 1/sqrtf(2))));

    return MUNIT_OK;
}

#define WORLD_TESTS \
    {               \
        "world_instantiation", \
        test_world_instantiation, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,\
        NULL\
    },              \
    {               \
        "world_add", \
        test_world_add, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,\
        NULL\
    },              \
    {               \
        "world_intersection", \
        test_world_intersection, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,\
        NULL\
    }

#endif //RAYTRACING_IN_C_WORLD_TEST_H

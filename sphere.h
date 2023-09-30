//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_SPHERE_H
#define RAYTRACING_IN_C_SPHERE_H

#include <stdlib.h>
#include "tuple.h"
#include "ray.h"
#include "transform.h"
#include "material.h"

typedef struct {
    tuple_t center;
    double radius;
    matrix_t transform;
    material_t material;
} sphere_t;

#define sphere(center, radius, transform, material) (sphere_t) { center, radius, transform, material }

sphere_t sphere_null(tuple_t center, double radius, material_t material) {
    matrix_t m = matrix_null(4, 4);
    matrix_init(&m);
    return (sphere_t) { center, radius, m, material };
}

// buf should be declared like sphere_t buf[2];
void sphere_hit(sphere_t* s, ray_t* r, double* buf, int* len_buf) {
    tuple_t d = vector(r->origin.x - s->center.x, r->origin.y - s->center.y, r->origin.z - s->center.z);

    double a = tuple_dot(r->direction, r->direction);
    double b = tuple_dot(r->direction, d);
    double c = tuple_dot(d, d) - s->radius * s->radius;

    if (a == 0 && b != 0) {
        double t = -c / (2 * b);
        if(t <= 0) {
            *len_buf = 0;
            return;
        }

        buf[0] = t;
        *len_buf = 1;
        return;
    }

    double discriminant = b * b - a * c;

    if(discriminant < 0) {
        buf = NULL;
        *len_buf = 0;
        return;
    } else if(discriminant == 0) {
        double t = -b / a;
        if(t <= 0) {
            *len_buf = 0;
            return;
        }
        buf[0] = t;
        *len_buf = 1;
        return;
    }

    double t1 = (-b - sqrtf(discriminant)) / a;
    double t2 = (-b + sqrtf(discriminant)) / a;
    *len_buf = 0;

    if(t1 > 0) {
        buf[*len_buf] = t1;
        *len_buf += 1;
    }

    if(t2 > 0) {
        buf[*len_buf] = t2;
        *len_buf += 1;
    }
}

tuple_t sphere_normal(sphere_t s, tuple_t p) {
    tuple_t d = tuple_sub(p, s.center);
    return tuple_mtransform(&d, matrix_inv(&s.transform));
}

void sphere_set_transform(sphere_t* s, matrix_t* transform) {
    matrix_cpy(&s->transform, transform);
}

void sphere_mset_transform(sphere_t* s, matrix_t transform) {
    sphere_set_transform(s, &transform);
    matrix_free(&transform);
}

int sphere_cmp(sphere_t s1, sphere_t s2) {
    return tuple_cmp2(s1.center, s2.center) && \
        double_cmp2(s1.radius, s2.radius) && \
        matrix_cmp2(s1.transform, s2.transform);
}

#endif //RAYTRACING_IN_C_SPHERE_H

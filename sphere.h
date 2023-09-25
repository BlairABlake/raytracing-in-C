//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_SPHERE_H
#define RAYTRACING_IN_C_SPHERE_H

#include <stdlib.h>
#include "tuple.h"
#include "ray.h"

typedef struct {
    tuple_t center;
    float radius;
} sphere_t;

#define sphere(center, radius) (sphere_t) { center, radius }

// buf should be declared like sphere_t buf[2];
void sphere_hit(sphere_t* s, ray_t* r, tuple_t* buf, int* len_buf) {
    tuple_t d = vector(r->origin.x - s->center.x, r->origin.y - s->center.y, r->origin.z - s->center.z);

    float a = tuple_dot(r->direction, r->direction);
    float b = tuple_dot(r->direction, d);
    float c = tuple_dot(d, d) - s->radius * s->radius;

    if (a == 0) {
        buf[0] = ray_position(r, -c / (2 * b));
        *len_buf = 1;
        return;
    }

    float discriminant = b * b - a * c;

    if(discriminant < 0) {
        buf = NULL;
        *len_buf = 0;
        return;
    } else if(discriminant == 0) {
        float t = -b / a;
        buf[0] = ray_position(r, t);
        *len_buf = 1;
        return;
    }

    float t1 = (-b + sqrtf(discriminant)) / a;
    float t2 = (-b - sqrtf(discriminant)) / a;
    buf[0] = ray_position(r, t1);
    buf[1] = ray_position(r, t2);
    *len_buf = 2;
}

#endif //RAYTRACING_IN_C_SPHERE_H

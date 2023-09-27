//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_RAY_H
#define RAYTRACING_IN_C_RAY_H

#include "tuple.h"

typedef struct {
    tuple_t origin;
    tuple_t direction;
} ray_t;

#define ray(origin, direction) (ray_t){origin, direction}

tuple_t ray_position(ray_t* r, float t) {
    tuple_t result = tuple_add(r->origin, tuple_sc_mul(r->direction, t));
    result.w = 1;

    return result;
}

void ray_cpy(ray_t* destination, ray_t* source) {
    tuple_cpy(&destination->origin, &source->origin);
    tuple_cpy(&destination->direction, &source->direction);
}

#endif //RAYTRACING_IN_C_RAY_H

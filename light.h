//
// Created by ryousuke kaga on 2023/09/27.
//

#ifndef RAYTRACING_IN_C_LIGHT_H
#define RAYTRACING_IN_C_LIGHT_H

#include "tuple.h"

typedef struct {
    tuple_t position;
    color_t intensity;
} point_light_t;

#define point_light(position, intensity) (point_light_t){position, intensity}

int point_light_cmp(point_light_t p1, point_light_t p2) {
    return tuple_cmp2(p1.position, p2.position) && color_cmp2(p1.intensity, p2.intensity);
}

#endif //RAYTRACING_IN_C_LIGHT_H

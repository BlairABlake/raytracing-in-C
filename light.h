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

#endif //RAYTRACING_IN_C_LIGHT_H

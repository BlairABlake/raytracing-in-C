//
// Created by ryousuke kaga on 2023/10/01.
//

#ifndef RAYTRACING_IN_C_3DOBJECT_H
#define RAYTRACING_IN_C_3DOBJECT_H

#include "matrix.h"
#include "ray.h"

typedef struct object_s {
    matrix_t translation;
    matrix_t rotation;
    matrix_t scale;
} object_t;

typedef struct hit_s {
    tuple_t position;
    double t;
} hit_t;

object_t object_init(object_t* object);
ray_t transform_ray(object_t* object, ray_t* ray);

#endif //RAYTRACING_IN_C_3DOBJECT_H

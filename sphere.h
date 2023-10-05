//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_SPHERE_H
#define RAYTRACING_IN_C_SPHERE_H

#include <stdlib.h>
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "3Dobject.h"
#include "algorithms/list.h"

List sphere_hit(object_t* object, ray_t* ray);
//tuple_t sphere_normal(object_t* sphere, tuple_t point);

#endif //RAYTRACING_IN_C_SPHERE_H

//
// Created by ryousuke kaga on 2023/10/05.
//

#include "3Dobject.h"

object_t object_init(object_t* object) {
    matrix_id(&object->translation);
    matrix_id(&object->rotation);
    matrix_id(&object->scale);
}

ray_t transform_ray(object_t* object, ray_t* ray) {
    matrix_t t;
    ray_t result;
    matrix_inv(object->translation, &t);
    result.origin = tuple_transform(t, ray->origin);
    matrix_inv(object->rotation, &t);
    result.origin = tuple_transform(t, ray->origin);
    result.direction = tuple_transform(t, ray->direction);
    matrix_inv(object->scale, &t);
    result.direction = tuple_transform(t, ray->direction);
    result.origin = tuple_transform(t, ray->origin);

    return result;
}
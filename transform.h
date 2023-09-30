//
// Created by ryousuke kaga on 2023/09/26.
//

#ifndef RAYTRACING_IN_C_TRANSFORM_H
#define RAYTRACING_IN_C_TRANSFORM_H

#include "matrix.h"
#include "tuple.h"

matrix_t translation_matrix(tuple_t t) {
    double r[] = {1, 0, 0, t.x,
                0, 1, 0, t.y,
                0, 0, 1, t.z,
                0, 0, 0, 1};
    return matrix(4, 4, r);
}

matrix_t scale_matrix(tuple_t t) {
    double r[] = {t.x, 0, 0, 0,
                 0, t.y, 0, 0,
                 0, 0, t.z, 0,
                 0, 0, 0, 1};
    return matrix(4, 4, r);
}

matrix_t rotation_x_matrix(double rad) {
    double r[] = {1, 0, 0, 0,
                 0, cos(rad), -sin(rad), 0,
                 0, sin(rad), cos(rad), 0,
                 0, 0, 0, 1};
    return matrix(4, 4, r);
}

matrix_t rotation_y_matrix(double rad) {
    double r[] = {cos(rad), 0, sin(rad), 0,
                 0, 1, 0, 0,
                 -sin(rad), 0, cos(rad), 0,
                 0, 0, 0, 1};
    return matrix(4, 4, r);
}

matrix_t rotation_z_matrix(double rad) {
    double r[] = {cos(rad), -sin(rad), 0, 0,
                 sin(rad), cos(rad), 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1};
    return matrix(4, 4, r);
}

matrix_t matrix_transform(matrix_t* target, matrix_t* transform) {
    return matrix_mul(transform, target);
}

matrix_t matrix_mtransform(matrix_t* target, matrix_t transform) {
    matrix_t result = matrix_transform(target, &transform);
    matrix_free(&transform);
    return result;
}

tuple_t tuple_transform(tuple_t* target, matrix_t* transform) {
    matrix_t t = tuple_to_matrix(target);
    matrix_t mresult = matrix_transform(&t, transform);
    tuple_t result = matrix_to_tuple(&mresult);
    matrix_free(&t);
    matrix_free(&mresult);

    return result;
}

tuple_t tuple_mtransform(tuple_t* target, matrix_t transform) {
    tuple_t result = tuple_transform(target, &transform);
    return result;
}

ray_t ray_transform(ray_t* target, matrix_t* transform) {
    ray_t result;
    result.origin = tuple_transform(&target->origin, transform);
    result.direction = tuple_transform(&target->direction, transform);
    return result;
}

ray_t ray_mtransform(ray_t* target, matrix_t transform) {
    ray_t result = ray_transform(target, &transform);
    matrix_free(&transform);
    return result;
}

#endif //RAYTRACING_IN_C_TRANSFORM_H

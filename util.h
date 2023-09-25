//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_UTIL_H
#define RAYTRACING_IN_C_UTIL_H

#include <math.h>

#define EPSILON_DEFAULT 1e-4

int float_cmp(float a, float b, double epsilon)
{
    return fabsf(a-b) < epsilon;
}

int float_cmp2(float a, float b) {
    return float_cmp(a, b, EPSILON_DEFAULT);
}

#endif //RAYTRACING_IN_C_UTIL_H

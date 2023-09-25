//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_FLOAT_H
#define RAYTRACING_IN_C_FLOAT_H

#include <math.h>

#define EPSILON_DEFAULT 1e-4

int double_cmp(double a, double b, double epsilon)
{
    return fabs(a-b) < epsilon;
}

int double_cmp2(double a, double b) {
    return double_cmp(a, b, EPSILON_DEFAULT);
}

#endif //RAYTRACING_IN_C_FLOAT_H

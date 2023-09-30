//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_TUPLE_H
#define RAYTRACING_IN_C_TUPLE_H

#include "util.h"


typedef struct {
    double x;
    double y;
    double z;
    int w;
} tuple_t;

#define point(x, y, z) (tuple_t){x, y, z, 1}
#define vector(x, y, z) (tuple_t){x, y, z, 0}
#define tuple(x, y, z, w) (tuple_t){x, y, z, w}

int tuple_cmp(tuple_t t1, tuple_t t2, double delta) {
    return double_cmp(t1.x, t2.x, delta) && \
           double_cmp(t1.y, t2.y, delta) && \
           double_cmp(t1.z, t2.z, delta) && \
           t1.w == t2.w;
}

int tuple_cmp2(tuple_t t1, tuple_t t2) {
    return double_cmp2(t1.x, t2.x) && \
           double_cmp2(t1.y, t2.y) && \
           double_cmp2(t1.z, t2.z) && \
           t1.w == t2.w;
}

tuple_t tuple_add(tuple_t t1, tuple_t t2) {
    return (tuple_t){t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w};
}

tuple_t tuple_sub(tuple_t t1, tuple_t t2) {
    return (tuple_t){t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w};
}

tuple_t tuple_mul(tuple_t t1, tuple_t t2) {
    return (tuple_t){t1.x * t2.x, t1.y * t2.y, t1.z * t2.z, t1.w * t2.w};
}

tuple_t tuple_neg(tuple_t t) {
    return (tuple_t){-t.x, -t.y, -t.z, -t.w};
}

tuple_t tuple_sc_mul(tuple_t t, double s) {
    return (tuple_t){t.x * s, t.y * s, t.z * s, t.w * s};
}

tuple_t tuple_sc_div(tuple_t t, double s) {
    if(s == 0.0f) return t;
    return (tuple_t){t.x / s, t.y / s, t.z / s, t.w / s};
}

double tuple_mag(tuple_t t) {
    return sqrtf(t.x * t.x + t.y * t.y + t.z * t.z);
}

tuple_t tuple_norm(tuple_t t) {
    return tuple_sc_div(t, tuple_mag(t));
}

double tuple_dot(tuple_t t1, tuple_t t2) {
    return t1.x * t2.x + t1.y * t2.y + t1.z * t2.z;
}

tuple_t tuple_cross(tuple_t t1, tuple_t t2) {
    return vector(t1.y * t2.z - t1.z * t2.y,
                  t1.z * t2.x - t1.x * t2.z,
                  t1.x * t2.y - t1.y * t2.x);
}

void tuple_cpy(tuple_t* destination, tuple_t* source) {
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
    destination->w = source->w;
}

tuple_t tuple_reflect(tuple_t t, tuple_t n) {
    return tuple_sub(t, tuple_sc_mul(tuple_sc_mul(n, 2.0f), tuple_dot(t, n)));
}


#endif //RAYTRACING_IN_C_TUPLE_H

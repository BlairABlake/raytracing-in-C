//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_COLOR_H
#define RAYTRACING_IN_C_COLOR_H

#include "tuple.h"

typedef struct {
    double red;
    double green;
    double blue;
} color_t;

#define color(red, green, blue) (color_t){red, green, blue}

int color_cmp(color_t c1, color_t c2, double delta) {
    return double_cmp(c1.red, c2.red, delta) && double_cmp(c1.green, c2.green, delta) && double_cmp(c1.blue, c2.blue, delta);
}

int color_cmp2(color_t c1, color_t c2) {
    return color_cmp(c1, c2, EPSILON_DEFAULT);
}

color_t color_mul(color_t c1, color_t c2) {
    return color(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
}

tuple_t color_to_tuple(color_t c) {
    return vector(c.red, c.green, c.blue);
}

color_t tuple_to_color(tuple_t t) {
    return color(t.x, t.y, t.z);
}

void color_cpy(color_t* destination, color_t* source) {
    destination->red = source->red;
    destination->green = source->green;
    destination->blue = source->blue;
}

#endif //RAYTRACING_IN_C_COLOR_H

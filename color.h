//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_COLOR_H
#define RAYTRACING_IN_C_COLOR_H

typedef struct {
    float red;
    float green;
    float blue;
} color_t;

#define color(red, green, blue) (color_t){red, green, blue};

int color_cmp(color_t c1, color_t c2) {
    return c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue;
}

tuple_t color_to_tuple(color_t c) {
    return vector(c.red, c.green, c.blue);
}

color_t tuple_to_color(tuple_t t) {
    return color(t.x, t.y, t.z);
}

#endif //RAYTRACING_IN_C_COLOR_H

//
// Created by ryousuke kaga on 2023/09/25.
//
#include <stdio.h>
#include "canvas.h"
#include "tuple.h"
#include "color.h"

int main() {
    canvas_t c = canvas(900, 150);
    canvas_init(&c);

    color_t red = color(255, 0, 0);

    tuple_t g = vector(0, -0.1, 0);
    tuple_t v = tuple_sc_mul(tuple_norm(vector(1, 0.5, 0)), 10.25f);
    tuple_t r = vector(0, 0, 0);
    double delta = 0.1;

    for(int i=0; i < 10000; i++) {
        double t = delta * i;
        r.x = v.x * t;
        r.y = v.y * t + 0.5 * g.y * t * t;
        canvas_write(&c, (int)r.x, c.height - (int)r.y, red);
    }

    FILE* f = fopen("./projectile.ppm", "w");
    canvas_write_ppm(&c, f);
    canvas_free(&c);
    fclose(f);
    return 0;
}

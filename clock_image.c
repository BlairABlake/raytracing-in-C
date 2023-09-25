//
// Created by ryousuke kaga on 2023/09/25.
//
#include <stdio.h>
#include "canvas.h"
#include "tuple.h"
#include "color.h"
#include "matrix.h"

int main() {
    int width = 100;
    int height = 100;
    int n_rad = 20;
    canvas_t cv = canvas(width, height);
    canvas_init(&cv);

    tuple_t base = vector(20, 0, 0);
    float rad = M_PI / n_rad * 2;

    color_t red = color(255, 0, 0);

    for(int i=0; i < n_rad; i++) {
        tuple_t t = matrix_rotation_z(&base, rad * (float)i);
        canvas_write(&cv, width/2 + (int)t.x, height/2 + (int)t.y, red);
    }

    FILE* f = fopen("clock.ppm", "w");
    canvas_write_ppm(&cv, f);
    canvas_free(&cv);
    fclose(f);
    return 0;
}
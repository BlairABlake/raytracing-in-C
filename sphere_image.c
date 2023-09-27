//
// Created by ryousuke kaga on 2023/09/26.
//
#include <stdio.h>
#include "canvas.h"
#include "tuple.h"
#include "color.h"
#include "matrix.h"
#include "sphere.h"
#include "ray.h"
#include "transform.h"

int main() {
    int width = 200;
    int height = 200;
    int n_rad = 20;
    canvas_t cv = canvas(width, height);
    canvas_init(&cv);

    sphere_t s = sphere_null(point(0, 0, 0), width / 4.0f);
    sphere_mset_transform(&s, scale_matrix(point(1.5f, 1, 1)));
    tuple_t origin = point(0, 0, -200.0f);
    color_t red = color(255, 0, 0);

    for(int y = -height / 2; y < height / 2; y++) {
        for(int x = -width / 2; x < width / 2; x++) {
            tuple_t p = point(x, y, 0);
            ray_t r = ray(origin, tuple_sub(p, origin));
            r = ray_mtransform(&r, matrix_inv(&s.transform));

            tuple_t hits[2];
            int hit_n = 0;
            sphere_hit(&s, &r, hits, &hit_n);

            if(hit_n != 0) {
                canvas_write(&cv, x + width / 2, height - (y + height / 2), red);
            }
        }
    }

    FILE* f = fopen("sphere.ppm", "w");
    canvas_write_ppm(&cv, f);
    canvas_free(&cv);
    fclose(f);
    return 0;
}
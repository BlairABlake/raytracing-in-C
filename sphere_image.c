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
    int width = 300;
    int height = 300;
    int n_rad = 20;
    canvas_t cv = canvas(width, height);
    canvas_init(&cv);

    material_t m = material(color(0, 1, 1), 0.7, 0.7, 1, 100.0);
    sphere_t s = sphere(point(0, 0, 0), 80, matrix_id(4), m);
    tuple_t origin = point(0, 0, -100.0f);

    point_light_t l = point_light(point(-20, 20, -100.0f), color(2, 2, 2));

    for(int y = -height / 2; y < height / 2; y++) {
        for(int x = -width / 2; x < width / 2; x++) {
            tuple_t p = point(x, y, 0);
            ray_t r = ray(origin, tuple_sub(p, origin));
            r = ray_mtransform(&r, matrix_inv(&s.transform));

            tuple_t hits[2];
            int hit_n = 0;
            sphere_hit(&s, &r, hits, &hit_n);

            if(hit_n != 0) {
                tuple_t normal = sphere_normal(s, hits[1]);

                color_t c = lighting(s.material, l, hits[1], tuple_norm(r.direction), normal);
                canvas_write(&cv, x + width / 2, height - (y + height / 2),  c);
            }
        }
    }

    FILE* f = fopen("sphere.ppm", "w");
    canvas_write_ppm(&cv, f);
    canvas_free(&cv);
    fclose(f);
    return 0;
}
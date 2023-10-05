//
// Created by ryousuke kaga on 2023/09/26.
//
#include <stdio.h>
#include "canvas.h"
#include "tuple.h"
#include "matrix.h"
#include "sphere.h"
#include "ray.h"

int main() {
    int width = 1200;
    int height = 1200;
    tuple_t (*pixels)[height] = malloc(sizeof(tuple_t) * width * height);
    tuple_t bg_color = tuple(0, 0, 0, 0);
    tuple_t hit_color = tuple(1, 0, 0, 0);
    canvas_fill(width, height, pixels, bg_color);

    object_t sphere;
    object_init(&sphere);
    scaling_matrix(200, 200, 200, &sphere.scale);

    tuple_t origin = point(0, 0, -2000);

    tuple_t p = point(0, 0, 0);
    tuple_t direction;
    for(int i=0; i < height; i++) {
        for(int j=0; j < width; j++) {
            p.x = j - width / 2;
            p.y = height/2 - i;
            direction = tuple_norm(tuple_sub(p, origin));

            ray_t eye = ray(origin, direction);
            eye = transform_ray(&sphere, &eye);

            List hits = sphere_hit(&sphere, &eye);
            if(hits.head != NULL) {
                pixels[i][j] = hit_color;
            }
        }
    }

    FILE* fp = fopen("sphere_image.ppm", "w");
    canvas_write_ppm(width, height, pixels, fp);
    return 0;
}
//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_CANVAS_H
#define RAYTRACING_IN_C_CANVAS_H

#include <stdio.h>
#include "cstring/cstring.h"
#include "color.h"

typedef struct {
    int width;
    int height;
    color_t* pixels;
} canvas_t;

#define canvas(w, h) (canvas_t){w, h, NULL}


void canvas_init(canvas_t* c) {
    size_t size = c->width * c->height;
    color_t* pixels = malloc(sizeof(color_t) * size);
    for(int i=0; i < size; i++) {
        pixels[i] = color(0, 0, 0);
    }
    c->pixels = pixels;
}

void canvas_free(canvas_t* c) {
    free(c->pixels);
    c->pixels = NULL;
    c = NULL;
}

color_t canvas_at(canvas_t* c, int x, int y) {
    return c->pixels[x + y*c->width];
}

void canvas_write(canvas_t* cv, int x, int y, color_t co) {
    if(x >= 0 && x < cv->width && y >= 0 && y < cv->height) cv->pixels[x + y*cv->width] = co;
}

void canvas_write_ppm(canvas_t* cv, FILE* f) {
    char header[30];
    sprintf(header, "P3\n%d %d\n255\n", cv->width, cv->height);
    string_t s = string(header);
    for(int y=0; y < cv->height; y++) {
        for(int x=0; x < cv->width; x++) {
            color_t co = canvas_at(cv, x, y);
            char buf[6];
            string_t s_co;
            sprintf(buf, "%d ", (int)co.red);
            s_co = string(buf);
            string_mcat(&s, &s_co);
            sprintf(buf, "%d ", (int)co.green);
            s_co = string(buf);
            string_mcat(&s, &s_co);
            sprintf(buf, "%d ", (int)co.blue);
            s_co = string(buf);
            string_mcat(&s, &s_co);
            //a line in ppm file should not exceed 70 characters.
            //each value occupy 4 space at most.
            if(x != 0 && x % 16 == 0) {
                string_cat1(&s, string("\n"));
            }
        }
        string_cat1(&s, string("\n"));
    }

    string_cat1(&s, string("\n"));
    fprintf(f, "%s", (char*)s.data);
    string_free(&s);
}

#endif //RAYTRACING_IN_C_CANVAS_H

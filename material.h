//
// Created by ryousuke kaga on 2023/09/27.
//

#ifndef RAYTRACING_IN_C_MATERIAL_H
#define RAYTRACING_IN_C_MATERIAL_H

#include "color.h"

typedef struct {
    color_t color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} material_t;

#define material(color, ambient, diffuse, specular, shininess) (material_t){ color, ambient, diffuse, specular, shininess }

#endif //RAYTRACING_IN_C_MATERIAL_H

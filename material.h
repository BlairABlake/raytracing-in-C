//
// Created by ryousuke kaga on 2023/09/27.
//

#ifndef RAYTRACING_IN_C_MATERIAL_H
#define RAYTRACING_IN_C_MATERIAL_H

#include "color.h"
#include "tuple.h"
#include "light.h"

typedef struct {
    color_t color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} material_t;

#define material(color, ambient, diffuse, specular, shininess) (material_t){ color, ambient, diffuse, specular, shininess }


color_t lighting(material_t m, point_light_t l, tuple_t p, tuple_t e, tuple_t n) {
    tuple_t effective_color = color_to_tuple(color_mul(m.color, l.intensity));
    tuple_t lightv = tuple_norm(tuple_sub(l.position, p));

    tuple_t ambient, diffuse, specular;

    ambient = tuple_sc_mul(effective_color, m.ambient);

    double light_dot_normal = tuple_dot(lightv, n);

    if(light_dot_normal < 0) {
        diffuse = point(0, 0, 0);
        specular = point(0, 0, 0);
    }  else {
        diffuse = tuple_sc_mul(effective_color, m.diffuse * light_dot_normal);

        tuple_t reflectv = tuple_reflect(tuple_sc_mul(lightv, -1), n);
        double reflect_dot_eye = tuple_dot(reflectv, e);

        if(reflect_dot_eye <= 0) {
            specular = point(0, 0, 0);
        } else {
            double factor = powf(reflect_dot_eye, m.shininess);
            specular = tuple_sc_mul(color_to_tuple(l.intensity), m.specular * factor);
        }
    }

    return tuple_to_color(tuple_add(ambient, tuple_add(diffuse, specular)));
}


#endif //RAYTRACING_IN_C_MATERIAL_H

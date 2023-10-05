//
// Created by ryousuke kaga on 2023/10/05.
//

#include "sphere.h"

List sphere_hit(object_t* sphere, ray_t* ray) {
    List hits;
    list_init(&hits, free);

    double a = tuple_dot(ray->direction, ray->direction);
    double b = tuple_dot(ray->origin, ray->direction);
    double c = tuple_dot(ray->origin, ray->origin) - 1;

    if(a == 0) {
        if(b == 0)
            return hits;
        hit_t* hit = malloc(sizeof(hit_t));
        hit->t = -b/c;
        hit->position = ray_position(ray, hit->t);
        list_ins_next(&hits, NULL, hit);
        return hits;
    }

    double discriminant = b*b - a * c;
    if(discriminant < 0)
        return hits;


    if(discriminant == 0) {
        hit_t* hit = malloc(sizeof(hit_t));
        hit->t = -b/a;
        hit->position = ray_position(ray, hit->t);
        list_ins_next(&hits, NULL, hit);
    } else {
        hit_t* hit = malloc(sizeof(hit_t));
        hit->t = (-b - sqrt(discriminant)) / a;
        hit->position = ray_position(ray, hit->t);
        list_ins_next(&hits, NULL, hit);
        hit = malloc(sizeof(hit_t));
        hit->t = (-b + sqrt(discriminant)) / a;
        hit->position = ray_position(ray, hit->t);
        list_ins_next(&hits, hits.tail, hit);
    }

    return hits;
}


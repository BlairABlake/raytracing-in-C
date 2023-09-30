//
// Created by ryousuke kaga on 2023/09/29.
//

#ifndef RAYTRACING_IN_C_WORLD_H
#define RAYTRACING_IN_C_WORLD_H

#include "sphere.h"
#include "light.h"
#include "util.h"

typedef struct {
    struct ll_node* objects;
    struct ll_node* lights;
} world_t;

#define world() (world_t){ll_init(), ll_init()}

struct hit_s {
    void* object;
    double t;
    tuple_t eyev;
    tuple_t normalv;
    tuple_t p;
};

struct hit_s* hit_init() {
    return (struct hit_s*)malloc(sizeof(struct hit_s));
}

void world_add(world_t* w, void* object, char* name) {
    struct ll_node* node = ll_init();
    node->next = NULL;
    node->data = object;
    node->name = name;
    if(strcmp(name, "light") == 0) {
        ll_push(w->lights, node);
    } else {
        ll_push(w->objects, node);
    }
}

void world_free(world_t* w) {
    ll_free(w->objects);
    ll_free(w->lights);
}

struct hit_s* sphere_hit_data(sphere_t* s, ray_t* r, double t) {
    struct hit_s* hit = hit_init();
    hit->object = s;
    hit->t = t;
    hit->p = ray_position(r, hit->t);
    hit->normalv = sphere_normal(*s, hit->p);
    hit->eyev = r->direction;
    return hit;
}

struct ll_node* world_intersect(world_t* w, ray_t* r) {
    struct ll_node* results = ll_init();
    struct ll_node* object = w->objects;
    while(object->next) {
        object = object->next;

        if(strcmp(object->name, "sphere") == 0) {
            sphere_t* s = (sphere_t*)object->data;
            double hits[2];
            int hit_num=0;
            sphere_hit(s, r, hits, &hit_num);

            switch(hit_num) {
                case 1:
                {
                    struct ll_node* n = ll_init();
                    struct hit_s* hit = sphere_hit_data(s, r, hits[0]);
                    n->name = "sphere";
                    n->data = hit;
                    ll_push(results, n);
                    break;
                }
                case 2:
                {
                    struct ll_node* n1 = ll_init();
                    struct hit_s* hit1 = sphere_hit_data(s, r, hits[0]);
                    hit1->object = s;
                    hit1->t = hits[0];
                    n1->name = "sphere";
                    n1->data = hit1;
                    ll_push(results, n1);

                    struct ll_node* n2 = ll_init();
                    struct hit_s* hit2 = sphere_hit_data(s, r, hits[1]);
                    hit2->object = s;
                    hit2->t = hits[1];
                    hit2->p = ray_position(r, hit2->t);
                    hit2->eyev = r->direction;
                    hit2->normalv = sphere_normal(*s, hit2->p);
                    n2->name = "sphere";
                    n2->data = hit2;
                    ll_push(results, n2);
                    break;
                }
                default:
                    continue;
            }
        }
    }

    return results;
}

#endif //RAYTRACING_IN_C_WORLD_H

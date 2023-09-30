//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_UTIL_H
#define RAYTRACING_IN_C_UTIL_H

#include <math.h>

#define EPSILON_DEFAULT 1e-4

int double_cmp(double a, double b, double epsilon)
{
    return fabs(a-b) < epsilon;
}

int double_cmp2(double a, double b) {
    return double_cmp(a, b, EPSILON_DEFAULT);
}

struct ll_node {
    char* name;
    void* data;
    struct ll_node* next;
};

struct ll_node* ll_init() {
    struct ll_node* node = (struct ll_node*)malloc(sizeof(struct ll_node));
    node->next = NULL;
    node->name = "";
    node->data = NULL;
    return node;
}

int ll_length(struct ll_node* head) {
    int length = 0;
    if(head->data) return -1;

    while(head->next) {
        length++;
        head = head->next;
    }

    return length;
}

void ll_push(struct ll_node* target, struct ll_node* node) {
    if(!target) {
        target = node;
        return;
    }

    while(target->next) {
        target = target->next;
    }

    target->next = node;
}

void ll_free(struct ll_node* head) {
    if(head == NULL) return;

    struct ll_node* next;
    while(head->next) {
        next = head->next;
        free(head);
        head = NULL;
        head = next;
    }
}

#endif //RAYTRACING_IN_C_UTIL_H

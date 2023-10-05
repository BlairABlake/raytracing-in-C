//
// Created by ryousuke kaga on 2023/10/04.
//

#ifndef MYALGORITHMS_HTABLE_H
#define MYALGORITHMS_HTABLE_H

#include <stdlib.h>
#include "list.h"


typedef struct Htbl_ {
    int buckets;
    int (*hash)(const void* key);
    int (*match)(const void* key1, const void* key2);
    void (*destroy)(void* data);
    int size;
    List* table;
} Htbl;

#define HTABLE_SIZE 100

unsigned int hashpjw(const void* key);

int char_match(const void* c1, const void* c2);

int htbl_init(Htbl* htbl, int buckets, int (*hash)(const void* key), int (*match)(const void* key1, const void* key2), void (*destroy)(void* data));

void htbl_destroy(Htbl* htbl);

int htbl_insert(Htbl* htbl, const void* data);

int htbl_remove(Htbl* htbl, void** data);

int htbl_lookup(Htbl* htbl, void** data);

#define htbl_size(htbl) ((htbl)->size)

#endif //MYALGORITHMS_HTABLE_H

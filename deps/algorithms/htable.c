//
// Created by ryousuke kaga on 2023/10/04.
//

#include "htable.h"

unsigned int hashpjw(const void* key) {
    const char *ptr;
    unsigned int val;

    val = 0;
    ptr = key;

    while(*ptr != '\0') {
        unsigned int tmp;
        val = (val << 4) + (*ptr);
        if((tmp = (val & 0xf0000000))) {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }

        ptr++;
    }

    return val;
}

int char_match(const void* c1, const void* c2) {
    return strcmp((char*)c1, (char*)c2) == 0;
}


int htbl_init(Htbl* htbl, int buckets, int (*hash)(const void* key), int (*match)(const void* key1, const void* key2), void (*destroy)(void* data)) {
    htbl->buckets = buckets;
    htbl->hash = hash;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->size = 0;

    if((htbl->table = malloc(sizeof(List) * buckets)) == NULL)
        return -1;

    for(int i=0; i < buckets; i++) {
        list_init(&htbl->table[i], destroy);
    }

    return 0;
}

void htbl_destroy(Htbl* htbl) {
    for(int i=0; i<htbl->buckets; i++) {
        list_destroy(&htbl->table[i]);
    }

    free(htbl->table);
    memset(htbl, 0, sizeof(Htbl));
}

int htbl_insert(Htbl* htbl, const void* data) {
    void* tmp;
    int bucket, retval;

    tmp = (void*)data;

    if(htbl_lookup(htbl, &tmp) == 0)
        return 1;

    bucket = htbl->hash(data) % htbl->buckets;

    if((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;

    return retval;
}

int htbl_remove(Htbl* htbl, void** data) {
    ListElm *element, *prev;
    int bucket;

    bucket = htbl->hash(*data) % htbl->buckets;

    element = list_head(&htbl->table[bucket]);
    prev = NULL;

    while(element != NULL) {
        if(htbl->match(*data, list_data(element))) {
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
                htbl->size--;
                return 0;
            } else {
                return -1;
            }
        }
        prev = element;
        element = list_next(element);
    }

    return -1;
}

int htbl_lookup(Htbl* htbl, void** data) {
    ListElm *element;
    int bucket;

    bucket = htbl->hash(*data) % htbl->buckets;

    element = list_head(&htbl->table[bucket]);

    while(element != NULL) {
        if(htbl->match(*data, list_data(element))) {
            *data = list_data(element);
            return 0;
        }
        element = list_next(element);
    }

    return -1;
}
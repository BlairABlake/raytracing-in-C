#include "cstring.h"

#include <stdio.h>

string_t string(char* s) {
    size_t l = strlen(s);
    char* t = malloc((l+1) * sizeof(char)); // +1 indicates null terminator
    strcpy(t, s);
    return (string_t){l, (u_char*)t};
}

void string_init(string_t* s) {
    s->len = 0;
    s->data = NULL;
}

string_t string_init_n(size_t n) {
    return (string_t){n, malloc(sizeof(char) * (n + 1)) };
}

void string_cpy(string_t* destination, string_t* source) {
    string_free(destination);
    destination->len = source->len;
    destination->data = malloc((source->len+1) * sizeof(char));

    strcpy((char*)destination->data, (char*)source->data);
}

void string_mov(string_t* destination, string_t* source) {
    string_cpy(destination, source);
    string_free(source);
}

void string_free(string_t* s) {
    free(s->data);
    s->len = 0;
    s->data = NULL;
}

void string_cat(string_t* s1, string_t* s2) {
    char* t = malloc((s1->len + s2->len + 1) * sizeof(char));
    strcpy(t, (char*)s1->data);
    strcat(t, (char*)s2->data);
    string_free(s1);
    *s1 = string(t);
    free(t);
}

void string_cat1(string_t* s1, string_t s2) {
    char* t = malloc((s1->len + s2.len + 1) * sizeof(char));
    strcpy(t, (char*)s1->data);
    strcat(t, (char*)s2.data);
    string_free(s1);
    string_free(&s2);
    *s1 = string(t);
    free(t);
}

void string_mcat(string_t* s1, string_t* s2) {
    char* t = malloc((s1->len + s2->len + 1) * sizeof(char));
    strcpy(t, (char*)s1->data);
    strcat(t, (char*)s2->data);
    string_free(s1);
    string_free(s2);
    *s1 = string(t);
    free(t);
}

int string_cmp(string_t* s1, string_t* s2) {
    return strcmp((char*)s1->data, (char*)s2->data);
}

void string_ncpy(string_t* destination, string_t* source, size_t n) {
    string_free(destination);
    destination->len = n;
    destination->data = malloc((n+1) * sizeof(char) );

    strncpy((char*)destination->data, (char*)source->data, n);
}

void string_ncat(string_t* s1, string_t* s2, size_t n) {
    char* t = malloc((s1->len + n + 1) * sizeof(char));
    strcpy(t, (char*)s1->data);
    strncat(t, (char*)s2->data, n);
    string_free(s1);
    *s1 = string(t);
    free(t);
}

int string_ncmp(string_t* s1, string_t* s2, size_t n) {
    return strncmp((char*)s1->data, (char*)s2->data, n);
}

string_t string_str(string_t* s1, char* c) {
    string_t s2 = string(c);
    string_t current = *s1;
    for(int i=0; i < s1->len - s2.len; i++) {
        if(string_ncmp(&current, &s2, (int)s2.len) == 0) {
            return current;
        }
        current.data++;
        current.len--;
    }

    return current;
}
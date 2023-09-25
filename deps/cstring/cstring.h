#ifndef CSTRING_CSTRING_H
#define CSTRING_CSTRING_H

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    size_t len;
    u_char *data;
} string_t;

string_t string(char* s);
void string_init(string_t*);
string_t string_init_n(size_t n);
void string_cpy(string_t*, string_t*);
void string_mov(string_t*, string_t*);
void string_free(string_t*);
void string_cat(string_t*, string_t*);
void string_cat1(string_t*, string_t);
void string_mcat(string_t*, string_t*);
int string_cmp(string_t*, string_t*);
void string_ncpy(string_t*, string_t*, size_t);
void string_ncat(string_t*, string_t*, size_t);
int string_ncmp(string_t*, string_t*, size_t);
string_t string_str(string_t*, char*);

#endif //CSTRING_CSTRING_H

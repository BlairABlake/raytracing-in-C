//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_MATRIX_H
#define RAYTRACING_IN_C_MATRIX_H

#include <stdlib.h>

typedef struct {
    int width;
    int height;
    float* data;
} matrix_t;

#define matrix_null(w, h) (matrix_t){w, h, NULL}
#define matrix_cmp_delta 0.001

matrix_t matrix(int w, int h, float* data) {
    size_t size = w * h;
    float* data_c = malloc(sizeof(float) * size);
    for(int i=0; i < size; i++) {
        data_c[i] = data[i];
    }
    return (matrix_t){w, h, data_c};
}

void matrix_init(matrix_t* m) {
    size_t size = m->width * m->height;
    float* data = malloc(sizeof(float) * size);
    for(int i=0; i < size; i++) {
        data[i] = 0.0f;
    }
    m->data = data;
}

void matrix_free(matrix_t* m) {
    free(m->data);
    m->data = NULL;
    m = NULL;
}

float matrix_at(matrix_t* m, int x, int y) {
    return m->data[x + y*m->width];
}

void matrix_set(matrix_t* m, int x, int y, float f) {
    if(x >= 0 && x < m->width && y >= 0 && y < m->height) m->data[x + y*m->width] = f;
}

int matrix_cmp(matrix_t* m1, matrix_t* m2, float delta) {
    if(m1->width != m2->width || m1->height != m2->height) return 0;

    for(int y=0; y < m1->height; y++) {
        for(int x=0; x < m1->width; x++) {
            if(!float_cmp(matrix_at(m1, x, y), matrix_at(m2, x, y), delta)) return 0;
        }
    }

    return 1;
}

int matrix_cmp1(matrix_t* m1, matrix_t m2, float delta) {
    int result = matrix_cmp(m1, &m2, delta);

    return result;
}

matrix_t matrix_mul(matrix_t* m1, matrix_t* m2) {
    if(m1->width != m2->height) return matrix_null(0, 0);

    matrix_t t = matrix_null(m2->width, m1->height);
    matrix_init(&t);
    for (int y=0; y < m1->height; y++) {
        for(int x=0; x < m2->width; x++) {
            float v = 0.0f;
            for (int i=0; i < m1->width; i++) {
                v += matrix_at(m1, i, y) * matrix_at(m2, x, i);
            }
            matrix_set(&t, x, y, v);
        }
    }
    return t;
}

matrix_t tuple_to_matrix(tuple_t* t) {
    float data[] = {t->x, t->y, t->z, (float)t->w};
    return matrix(1, 4, data);
}

tuple_t matrix_to_tuple(matrix_t* m) {
    if(m->width == 1 && m->height == 4 || m->height == 1 && m->width == 4) return tuple(m->data[0], m->data[1], m->data[2], m->data[3]);

    return tuple(0, 0, 0, -1);
}

int matrix_is_square(matrix_t* m) {
    return m->width == m->height;
}

matrix_t matrix_id(int n) {
    matrix_t t = matrix_null(n, n);
    matrix_init(&t);
    for(int i=0; i < n; i++) {
        matrix_set(&t, i, i, 1.0f);
    }
    return t;
}

matrix_t matrix_T(matrix_t* t) {
    matrix_t m = matrix_null(t->width, t->height);
    matrix_init(&m);
    for(int y=0; y < t->height; y++) {
        for(int x=0; x < t->width; x++) {
            matrix_set(t, y, x, matrix_at(t, x, y));
        }
    }
}

matrix_t matrix_submatrix(matrix_t* t, int a, int b) {
    matrix_t m = matrix_null(t->width - 1, t->height - 1);
    matrix_init(&m);
    for(int y=0; y < t->height; y++) {
        if(y == b) continue;
        for(int x=0; x < t->width; x++) {
            if(x == a) continue;
            matrix_set(&m, x > a ? x - 1 : x, y > b ? y - 1 : y, matrix_at(t, x, y));
        }
    }

    return m;
}

float matrix_det(matrix_t* t) {
    if(!matrix_is_square(t)) return -1.0f;
    if(t->width == 2 && t->height == 2) {
        return t->data[0] * t->data[3] - t->data[1] * t->data[2];
    }

    float v = 0;
    for(int i=0; i < t->width; i++) {
        matrix_t sub = matrix_submatrix(t, i, 0);
        v += i % 2 ? -1 * t->data[i] * matrix_det(&sub) : t->data[i] * matrix_det(&sub);
        matrix_free(&sub);
    }

    return v;
}

int matrix_is_invertible(matrix_t* t) {
    return (int)matrix_det(t);
}

float matrix_minor(matrix_t* t, int a, int b) {
    matrix_t sub = matrix_submatrix(t, a, b);
    float result = matrix_det(&sub);
    matrix_free(&sub);

    return result;
}

float matrix_cofactor(matrix_t* t, int a, int b) {
    return (a + b) % 2 ? -matrix_minor(t, a, b) : matrix_minor(t, a, b);
}

matrix_t matrix_inv(matrix_t* t) {
    matrix_t m = matrix_null(t->width, t->height);
    matrix_init(&m);
    float det = matrix_det(t);
    if(det == 0) return *t;
    for(int y=0; y < t->height; y++) {
        for(int x=0; x < t->width; x++) {
            matrix_set(&m, x, y, matrix_cofactor(t, y, x) / det);
        }
    }
    return m;
}

tuple_t matrix_rotation_x(tuple_t* t, float rad) {
    matrix_t mt = tuple_to_matrix(t);
    float r[] = {1, 0, 0, 0,
               0, cosf(rad), -sinf(rad), 0,
               0, sinf(rad), cosf(rad), 0,
               0, 0, 0, 1};
    matrix_t mr = matrix(4, 4, r);

    matrix_t mresult = matrix_mul(&mr, &mt);
    tuple_t result = matrix_to_tuple(&mresult);

    matrix_free(&mresult);
    matrix_free(&mt);
    matrix_free(&mr);

    return result;
}

tuple_t matrix_rotation_y(tuple_t* t, float rad) {
    matrix_t mt = tuple_to_matrix(t);
    float r[] = {cosf(rad), 0, sinf(rad), 0,
                 0, 1, 0, 0,
                 -sinf(rad), 0, cosf(rad), 0,
                 0, 0, 0, 1};
    matrix_t mr = matrix(4, 4, r);

    matrix_t mresult = matrix_mul(&mr, &mt);
    tuple_t result = matrix_to_tuple(&mresult);

    matrix_free(&mresult);
    matrix_free(&mt);
    matrix_free(&mr);

    return result;
}

tuple_t matrix_rotation_z(tuple_t* t, float rad) {
    matrix_t mt = tuple_to_matrix(t);
    float r[] = {cosf(rad), -sinf(rad), 0, 0,
                 sinf(rad), cosf(rad), 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1};
    matrix_t mr = matrix(4, 4, r);

    matrix_t mresult = matrix_mul(&mr, &mt);
    tuple_t result = matrix_to_tuple(&mresult);

    matrix_free(&mresult);
    matrix_free(&mt);
    matrix_free(&mr);

    return result;
}

void matrix_cpy(matrix_t* destination, matrix_t* source) {
    if(destination->data == NULL) {
        matrix_init(destination);
    }

    size_t size = destination->width * destination->height;

    if(size != source->width * source->height) {
        return;
    }

    for(int i=0; i < size; i++) {
        destination->data[i] = source->data[i];
    }

    destination->width = source->width;
    destination->height = source->height;
}

#endif //RAYTRACING_IN_C_MATRIX_H

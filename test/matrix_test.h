//
// Created by ryousuke kaga on 2023/09/25.
//

#ifndef RAYTRACING_IN_C_MATRIX_TEST_H
#define RAYTRACING_IN_C_MATRIX_TEST_H

#include "tests.h"

TEST(test_matrix_instantiation) {
    matrix_t m = matrix_null(10, 20);
    matrix_init(&m);

    float f = 0.f;

    munit_assert(m.width == 10);
    munit_assert(m.height == 20);
    for(int i=0; i < m.width*m.height; i++) {
        munit_assert(float_cmp2(f, m.data[i]));
    }

    matrix_free(&m);
}

TEST(test_matrix_set) {
    matrix_t m = matrix_null(10, 20);
    matrix_init(&m);
    matrix_set(&m, 2, 3, 1.0f);
    munit_assert(float_cmp2(matrix_at(&m, 2, 3), 1.0f));

    matrix_free(&m);
}

TEST(test_matrix_comparison) {
    matrix_t m1 = matrix_null(2, 2);
    matrix_t m2 = matrix_null(2, 2);

    matrix_init(&m1);
    matrix_init(&m2);
    matrix_set(&m1, 1, 1, 1.0f);
    munit_assert(!matrix_cmp(&m1, &m2, matrix_cmp_delta));
    matrix_set(&m2, 1, 1, 1.0f);
    munit_assert(matrix_cmp(&m1, &m2, matrix_cmp_delta));
    matrix_free(&m1);
    matrix_free(&m2);
}

TEST(test_matrix_multiplication) {
    float data1[] = {1.0f, 2.0f,
                     3.0f, 4.0f};
    float data2[] = {2.0f, 3.0f,
                     4.0f, 5.0f};
    float datat[] = {10.0f, 13.0f,
                     22.0f, 29.0f};
    matrix_t m1 = matrix(2, 2, data1);
    matrix_t m2 = matrix(2, 2, data2);
    matrix_t mt = matrix(2, 2, datat);

    matrix_t r = matrix_mul(&m1, &m2);


    munit_assert(matrix_cmp1(&mt, matrix_mul(&m1, &m2), matrix_cmp_delta));

    matrix_free(&m1);
    matrix_free(&m2);
    matrix_free(&mt);
    matrix_free(&r);
}

TEST(test_matrix_identity) {
    float data1[] = {1.0f, 2.0f,
                     3.0f, 4.0f};
    float data2[] = {1.0f, 0.0f,
                     0.0f, 1.0f};

    matrix_t m = matrix(2, 2, data1);
    matrix_t t = matrix(2, 2, data2);

    matrix_t i = matrix_id(2);

    munit_assert(matrix_cmp(&t, &i, matrix_cmp_delta));
    munit_assert(matrix_cmp1(&m, matrix_mul(&m, &i), matrix_cmp_delta));

    matrix_free(&m);
    matrix_free(&t);
    matrix_free(&i);
}

TEST(test_matrix_transpose) {
    float data1[] = {1.0f, 2.0f, 3.0f,
                     4.0f, 5.0f, 6.0f};
    float data2[] = {1.0f, 4.0f,
                     2.0f, 5.0f,
                     3.0f, 6.0f};
    matrix_t m1 = matrix(3, 2, data1);
    matrix_t m2 = matrix(2, 3, data2);

    munit_assert(matrix_cmp1(&m2, matrix_T(&m1), matrix_cmp_delta));

    matrix_free(&m1);
    matrix_free(&m2);
}

TEST(test_matrix_submatrix) {
    float data1[] = {1.0f, 2.0f, 3.0f,
                     4.0f, 5.0f, 6.0f,
                     7.0f, 8.0f, 9.0f};
    float data2[] = {5.0f, 6.0f,
                     8.0f, 9.0f};
    matrix_t m1 = matrix(3, 3, data1);
    matrix_t m2 = matrix(2, 2, data2);

    munit_assert(matrix_cmp1(&m2, matrix_submatrix(&m1, 0, 0), matrix_cmp_delta));

    matrix_free(&m1);
    matrix_free(&m2);
}

TEST(test_matrix_determinant) {
    float data1[] = {1.0f, 2.0f, 3.0f,
                     4.0f, 5.0f, 6.0f,
                     7.0f, 8.0f, 9.0f};
    float data2[] = {5.0f, 6.0f,
                     8.0f, 9.0f};
    matrix_t m1 = matrix(3, 3, data1);
    matrix_t m2 = matrix(2, 2, data2);

    munit_assert(float_cmp2(matrix_det(&m1), 0.0f));
    munit_assert(float_cmp2(matrix_det(&m2), -3.0f));

    matrix_free(&m1);
    matrix_free(&m2);
}

TEST(test_matrix_invertible) {
    float data1[] = {1.0f, 2.0f, 3.0f,
                     4.0f, 5.0f, 6.0f,
                     7.0f, 8.0f, 9.0f};
    float data2[] = {5.0f, 6.0f,
                     8.0f, 9.0f};
    matrix_t m1 = matrix(3, 3, data1);
    matrix_t m2 = matrix(2, 2, data2);

    munit_assert(!matrix_is_invertible(&m1));
    munit_assert(matrix_is_invertible(&m2));

    matrix_free(&m1);
    matrix_free(&m2);
}

TEST(test_matrix_inversion) {
    float data[] = {-5, 2, 6, -8,
                    1, -5, 1, 8,
                    7, 7, -6, -7,
                    1, -3, 7, 4};
    float datat[] = {0.21805f, 0.45113f, 0.24060f, -0.04511f,
                     -0.80827f, -1.45677f, -0.44361f, 0.52068f,
                     -0.07895f, -0.22368f, -0.05263f, 0.19737f,
                     -0.52256f, -0.81391f, -0.30075f, 0.30639f};
    matrix_t m = matrix(4, 4, data);
    matrix_t t = matrix(4, 4, datat);

    matrix_t inv = matrix_inv(&m);

    munit_assert(matrix_cmp(&t, &inv, matrix_cmp_delta));

    matrix_t id = matrix_id(4);
    matrix_t mul = matrix_mul(&m, &inv);

    munit_assert(matrix_cmp(&mul, &id, matrix_cmp_delta));

    matrix_free(&m);
    matrix_free(&t);
    matrix_free(&inv);
    matrix_free(&id);
    matrix_free(&mul);
}


#define MATRIX_TESTS \
    {                \
        "matrix_instantiation", \
        test_matrix_instantiation, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_set", \
        test_matrix_set, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_comparison", \
        test_matrix_comparison, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_multiplication", \
        test_matrix_multiplication, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_identity", \
        test_matrix_identity, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_transpose", \
        test_matrix_transpose, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_submatrix", \
        test_matrix_submatrix, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_determinant", \
        test_matrix_determinant, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_invertible", \
        test_matrix_invertible, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    },               \
    {                \
        "matrix_inversion", \
        test_matrix_inversion, \
        NULL,       \
        NULL,       \
        MUNIT_TEST_OPTION_NONE,  \
        NULL    \
    }




#endif //RAYTRACING_IN_C_MATRIX_TEST_H


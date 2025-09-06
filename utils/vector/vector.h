#ifndef VECTOR_H
#define VECTOR_H

/*
    macro for generating vectors
*/
#include "../../lexer/token.h"
#include <stdio.h>


#define DECLARE_VECTOR_DECORATOR(TYPE)                                      \
                                                                            \
typedef struct {                                                            \
    size_t capacity, size;                                                  \
    TYPE *vals;                                                             \
} Vector_##TYPE;                                                            \
                                                                            \
void Vector_##TYPE##_init(Vector_##TYPE *vec);                              \
void Vector_##TYPE##_delete(Vector_##TYPE *vec);                            \
void Vector_##TYPE##_push_back(Vector_##TYPE *vec, TYPE val);               \
TYPE Vector_##TYPE##_get(Vector_##TYPE *vec, size_t idx);                   \
TYPE Vector_##TYPE##_pop_back(Vector_##TYPE *vec);                          \
void Vector_##TYPE##_clear(Vector_##TYPE *vec);                             \


DECLARE_VECTOR_DECORATOR(char)
DECLARE_VECTOR_DECORATOR(Token)

#endif
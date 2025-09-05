#ifndef VECTOR_H
#define VECTOR_H

/*
    macro for generating vectors
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "handle_error.h"

#define DECLARE_VECTOR(TYPE)                                        \
typedef struct {                                                    \
    size_t capacity, size;                                          \
    TYPE *vals;                                                     \
} Vector_##TYPE;                                                    \
                                                                    \
Vector_##TYPE* Vector_##TYPE##_init() {                             \
    Vector_##TYPE *vec = malloc(sizeof Vector_##TYPE);              \
vec -> capacity = 4;                                                \
    vec -> size = 0;                                                \
}                                                                   \
                                                                    \
void Vector_##TYPE##_delete(Vector_#TYPE *vec) {                    \
    free(vec -> vals);                                              \
    vec -> capacity = vec -> size = 0;                              \
    free(vec);                                                      \
}                                                                   \
                                                                    \
void Vector_##TYPE##_push_back(Vector_##TYPE *vec, ##TYPE val) {    \
    vec -> vals[vec -> size++] = val;                               \
    if(vec -> size == vec -> capacity) {                            \
        vec -> capacity *= 2;                                       \
        ##TYPE *temp = realloc(vec -> vals, vec -> capacity);       \
                                                                    \
        if(!temp) {                                                 \
            handle_error();                                         \
            free(vec -> vals);                                      \
            exit(errno);                                            \
        }                                                           \
                                                                    \
        vec -> vals = temp;                                         \
    }                                                               \
}                                                                   \
                                                                    \
##TYPE Vector_##TYPE##_get(Vector_##TYPE *vec, size_t idx) {        \
    if(idx >= vec -> capacity) {                                    \
        errno = EINVAL;                                             \
        handle_error();                                             \
        exit(errno);                                                \
    }                                                               \
                                                                    \
    return vec -> vals[idx];                                        \
}                                                                   \
                                                                    \
##TYPE Vector_##TYPE##_pop_back(Vector_##TYPE *vec) {               \
    if(!vec -> size) {                                              \
        errno = EINVAL;                                             \
        handle_error();                                             \
        exit(errno);                                                \
    }                                                               \
                                                                    \
    return vec -> vals[--vec -> size];                              \
}                                                                   \

#endif
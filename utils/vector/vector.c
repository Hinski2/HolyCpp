#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "vector.h"
#include "../handle_error/handle_error.h"


#define DECLARE_VECTOR(TYPE)                                                \
                                                                            \
void Vector_##TYPE##_init(Vector_##TYPE *vec) {                             \
    vec -> capacity = 4;                                                    \
    vec -> size = 0;                                                        \
    vec -> vals = malloc(vec -> capacity * sizeof(TYPE));                   \
    if(!vec -> vals) {                                                      \
        handle_error("couldn't alocate memory");                            \
        exit(errno);                                                        \
    }                                                                       \
}                                                                           \
                                                                            \
void Vector_##TYPE##_delete(Vector_##TYPE *vec) {                           \
    free(vec -> vals);                                                      \
    vec -> capacity = vec -> size = 0;                                      \
}                                                                           \
                                                                            \
void Vector_##TYPE##_push_back(Vector_##TYPE *vec, TYPE val) {              \
    if(vec -> size >= vec -> capacity) {                                    \
        vec -> capacity *= 2;                                               \
        TYPE *temp = realloc(vec -> vals, vec -> capacity * sizeof(TYPE));  \
                                                                            \
        if(!temp) {                                                         \
            handle_error("couldn't alocate memory");                        \
            free(vec -> vals);                                              \
            exit(errno);                                                    \
        }                                                                   \
                                                                            \
        vec -> vals = temp;                                                 \
    }                                                                       \
                                                                            \
    vec -> vals[vec -> size++] = val;                                       \
}                                                                           \
                                                                            \
TYPE Vector_##TYPE##_get(Vector_##TYPE *vec, size_t idx) {                  \
    if(idx >= vec -> size) {                                                \
        errno = EINVAL;                                                     \
        handle_error("innapropriate argument %d, vector has capacity %d",   \
                idx, vec -> capacity);                                      \
        exit(errno);                                                        \
    }                                                                       \
                                                                            \
    return vec -> vals[idx];                                                \
}                                                                           \
                                                                            \
TYPE Vector_##TYPE##_pop_back(Vector_##TYPE *vec) {                         \
    if(!vec -> size) {                                                      \
        errno = EINVAL;                                                     \
        handle_error("vec is empty, you can't pop_back");                   \
        exit(errno);                                                        \
    }                                                                       \
                                                                            \
    return vec -> vals[--vec -> size];                                      \
}                                                                           \
                                                                            \
void Vector_##TYPE##_clear(Vector_##TYPE *vec) {                            \
    vec -> size = 0;                                                        \
}                                                                           \

DECLARE_VECTOR(char)
DECLARE_VECTOR(Token)

#ifndef MAP_STR_TOKEN_H
#define MAP_STR_TOKEN_H

// naive implementation of map
//TODO change this structure to TRIE for better performance

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "token.h"

typedef struct {
    const char* str;
    TokenType tokenType;

    Bop bopType; // in future wrap this in union
} Pair_str_token;

extern const Pair_str_token map_str_token[];

// converts str to token
Token convert_str_to_token(const char* str);

// number conversion
bool is_int(const char* str);
int64_t convert_to_int(const char* str);
bool is_float(const char* str);
double convert_to_float(const char* str);

#endif
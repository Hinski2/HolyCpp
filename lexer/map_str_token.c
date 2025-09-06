#include "map_str_token.h"
#include <string.h>

const Pair_str_token map_str_token[] = {
    {"*", TOK_BOP, BOP_MULT},
    {"/", TOK_BOP, BOP_DIV},
    {"-", TOK_BOP, BOP_SUB},
    {"+", TOK_BOP, BOP_ADD},

    {"True", TOK_BOOL, BOP_NONE},
    {"False", TOK_BOOL, BOP_NONE},

    {"(", TOK_L_PAREN, BOP_NONE},
    {")", TOK_R_PAREN, BOP_NONE},

    {"\0", TOK_EOF, BOP_NONE},
};

Token convert_str_to_token(const char* str) {

    TokenType tokenType = TOK_NONE;
    Token token = {0};

    const size_t MAP_STR_TOKEN_SIZE = sizeof(map_str_token) / sizeof(map_str_token[0]);
    for(size_t i = 0; i < MAP_STR_TOKEN_SIZE; i++) {
        if(strcmp(map_str_token[i].str, str) == 0) {
            tokenType = token.type = map_str_token[i].tokenType;
            token.bop_type = map_str_token[i].bopType;
        }
    }

    if(tokenType == TOK_BOOL) {
        if(strcmp(str, "True") == 0) token.b_val = true;
        else token.b_val = false;
    } else if(tokenType == TOK_NONE && is_int(str)) {
        tokenType = token.type = TOK_INT;
        token.i_val = convert_to_int(str);
    } else if(tokenType == TOK_NONE && is_float(str)) {
        tokenType = token.type = TOK_FLOAT;
        token.f_val = convert_to_float(str);
    }

    return token;
}

bool is_int(const char* str) {
    for(size_t idx = 0; str[idx] != '\0'; idx++) {
        if(str[idx] < '0' || str[idx] > '9') return false;
    }

    return true;
}

bool is_float(const char* str) {
    bool dot = false;

    for(size_t idx = 0; str[idx] != '\0'; idx++) {
        if(str[idx] == '.' && !dot) dot = true;
        else if(str[idx] == '.' && dot) return false;
        else if(str[idx] < '0' || str[idx] > '9') return false;
    }

    return true;
}

int64_t convert_to_int(const char* str) {
    int64_t number = 0;
    for(size_t idx = 0; str[idx] != '\0'; idx++) {
        number = number * 10 + str[idx] - '0';
    }

    return number;
}

double convert_to_float(const char* str) {
    int64_t number = 0, div = 1;
    bool dot = false;

    for(size_t idx = 0; str[idx] != '\0'; idx++) {
        if(dot) div *= 10;

        if(str[idx] == '.') {
            dot = true;
        } else {
            number = number * 10 + str[idx] - '0';
        }
    }

    return (double) number / div;
}



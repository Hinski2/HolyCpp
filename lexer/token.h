#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>
#include <stdbool.h>

// enums for binary operations
typedef enum {
    BOP_NONE,   // if it's not a bop
    BOP_MULT,
    BOP_DIV,
    BOP_ADD,
    BOP_SUB,
} Bop;

// enum for token types
typedef enum {
    TOK_NONE,   // if it's not a token
    TOK_INT,
    TOK_FLOAT,
    TOK_BOOL,
    TOK_BOP,
    TOK_L_PAREN,
    TOK_R_PAREN,
    TOK_EOF,
} TokenType;

// struct for tokens
typedef struct {
    TokenType type;         // Token's type
    union {
        bool    b_val;
        int64_t i_val;
        double  f_val;

        Bop bop_type;
    };
} Token;

// utils
const char *bop_to_str(Bop bop);

#endif
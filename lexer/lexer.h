#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdint.h>
#include "../utils/vector_types.h"

// enums for binary operations
typedef enum {
    BOP_MULT,
    BOP_DIV, 
    BOP_ADD,
    BOP_SUB,
    BOP_EQ,
    BOP_LT,
    BOP_GT,
    BOP_LEQ,
    BOP_GEQ,
    BOP_NEQ,
} Bop;

// enum for token types
typedef enum {
    TOK_INT,
    TOK_DOUBLE,
    TOK_BOOL,
    TOK_BOP, 
} TokenType;

// struct for tokens
typedef struct {
    TokenType type;         // Token's type
    union {                 // for numbers, it's value
        int64_t i_val;
        double d_val;
        bool b_val;
    };
} Token;

// tokenizer
typedef struct {
    char *line;
    Vector_Token tokens;
    Vector_char buf;
} Tokenizer;

Tokenizer* Tokenizer_init(char *line);
void Tokenizer_delete(Tokenizer *tokenizer);

#endif

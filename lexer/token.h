#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>
#include <stdbool.h>


// enum for token types
typedef enum {
    // special
    TOK_NONE,
    TOK_EOF,

    // values
    TOK_FLOAT,
    TOK_INT,
    TOK_BOOL,

    // bop (binary operators)
    TOK_ADD,        // +
    TOK_SUB,        // -
    TOK_MULT,       // *
    TOK_DIV,        // /

    TOK_EQ,         // ==
    TOK_NEQ,        // !=
    TOK_GEQ,        // >=
    TOK_LEQ,        // <=
    TOK_GT,         // >
    TOK_LT,         // <
    TOK_LOG_AND,    // and
    TOK_LOG_OR,     // or
    TOK_BIT_AND,    // &
    TOK_BIT_OR,     // |  
    TOK_XOR,        // ^
    TOK_NOT,        // !

    // paren
    TOK_L_ROUND_PAREN,
    TOK_R_ROUND_PAREN,

    // counter
    TOK_COUNT,
} TokenType;

// struct for tokens
typedef struct {
    TokenType type;         // Token's type
    void* value;
} Token;

// utils
void print_token(Token token);

#endif
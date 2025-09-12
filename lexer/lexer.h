#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdint.h>
#include "../data_structures/vector/vector.h"
#include "token.h"

// tokenizer
typedef struct {
    char *line;
    Vector_Token tokens;
} Lexer;

// function that will create lexer, tokenize line and delete lexer
Vector_Token* tokenize(char *line, size_t line_number); 

// constructor and destructor
void lexer_init(Lexer *lexer, char *line); // lexer owns line
void lexer_deinit(Lexer *lexer);

// debug
void print_lexer(Lexer *lexer);

#endif

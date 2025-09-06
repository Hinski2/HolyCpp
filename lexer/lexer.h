#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdint.h>
#include "../utils/vector/vector.h"
#include "token.h"

// tokenizer
typedef struct {
    char *cursor;
    Vector_Token tokens;
    Vector_char buf;
} Lexer;

    // main
// function that will create lexer, tokenize line and delete lexer
Vector_Token* tokenize(char *line, size_t line_number); 

    // constructor and destructor
void lexer_init(Lexer *lexer, char *line);
void lexer_delete(Lexer *lexer);

    // utils for lexer
// returns the next char and consume it
char lexer_cursor_next(Lexer *lexer);
// returns the next char without consiming it
char lexer_cursor_peek(Lexer *lexer);

    // debug
void print_lexer(Lexer *lexer);

#endif

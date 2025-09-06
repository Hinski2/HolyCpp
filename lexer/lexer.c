#include <stdio.h> 
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "lexer.h"
#include "../utils/handle_error/handle_error.h"
#include "map_str_token.h"

Vector_Token* tokenize(char *line, size_t line_number) {
    // create lexer
    Lexer lexer; lexer_init(&lexer, line);

    // tokenize data
    char c;
    do {
        c = lexer_cursor_next(&lexer);
        if(c == ' ' || c == '\0') {
            Vector_char_push_back(&lexer.buf, '\0');
            Token token = convert_str_to_token(lexer.buf.vals); 
            
            // if bad token
            if(token.type == TOK_NONE) {
                errno = EINVAL;
                handle_error("inappropriate token in line: %d", line_number);
                exit(errno);
            }

            // ok token
            Vector_Token_push_back(&lexer.tokens, token);
            Vector_char_clear(&lexer.buf);
        } else {
            Vector_char_push_back(&lexer.buf, c);
        }
    } while(c != '\0');

    
    // c == '\0'
    Token token = convert_str_to_token("\0");
    Vector_Token_push_back(&lexer.tokens, token);
    lexer.buf.vals[0] = '\0';

    // create vector token
    Vector_Token *tokens = malloc(sizeof(Vector_Token)); 
    if(!tokens) {
        handle_error("couldn't allocated memory");
        exit(errno);
    }

    Vector_Token_init(tokens);
    for(size_t i = 0; i < lexer.tokens.size; i++)
        Vector_Token_push_back(tokens, Vector_Token_get(&lexer.tokens, i));

    // delete lexer
    print_lexer(&lexer); //!!!!!!!!!!!!!!!!!!!! debug
    lexer_delete(&lexer);

    return tokens;
}

char lexer_cursor_next(Lexer *lexer) {
    return *lexer -> cursor ? *lexer -> cursor++ : '\0';
}

char lexer_cursor_peek(Lexer *lexer) {
    return *lexer -> cursor ? *lexer -> cursor : '\0';
}

void lexer_init(Lexer *lexer, char *line) {
    lexer -> cursor = line;
    Vector_Token_init(&lexer -> tokens);
    Vector_char_init(&lexer -> buf);
}

void lexer_delete(Lexer *lexer) {
    Vector_char_delete(&lexer -> buf);
    Vector_Token_delete(&lexer -> tokens);
    free(lexer -> cursor);
}

void print_lexer(Lexer *lexer) {
    printf("{\n");
    printf("    Buf:\n");
    printf("        %s\n", lexer -> buf.vals);
    printf("    Tokens:\n");

    for (size_t i = 0; i < lexer -> tokens.size; i++) {
        Token token = Vector_Token_get(&lexer -> tokens, i);
        switch (token.type) {
            case TOK_NONE:
                printf("        {TokenType: TOK_NONE}\n");
                break;
            case TOK_INT:
                printf("        {TokenType: TOK_INT, i_val: %ld}\n", token.i_val);
                break;
            case TOK_FLOAT:
                printf("        {TokenType: TOK_FLOAT, f_val: %f}\n", token.f_val);
                break;
            case TOK_BOOL:
                printf("        {TokenType: TOK_BOOL, b_val: %s}\n", token.b_val ? "true" : "false");
                break;
            case TOK_BOP:
                printf("        {TokenType: TOK_BOP, bop: %s}\n", bop_to_str(token.bop_type));
                break;
            case TOK_L_PAREN:
                printf("        {TokenType: TOK_L_PAREN}\n");
                break;
            case TOK_R_PAREN:
                printf("        {TokenType: TOK_R_PAREN}\n");
                break;
            case TOK_EOF:
                printf("        {TokenType: TOK_EOF}\n");
                break;
        }
    }

    printf("}\n");
}
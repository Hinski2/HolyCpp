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

    // tokenize line
    Token token;
    do{
        char **line_new_start = malloc(sizeof(char*));
        token = get_token_from_line(lexer.line, line_new_start);
        lexer.line = *line_new_start;

        if(token.type == TOK_NONE) {
            handle_error("innapropriate token in line: %d", line_number);
            exit(EXIT_FAILURE);
        }

        Vector_Token_push_back(&lexer.tokens, token);
        free(line_new_start);
    } while(token.type != TOK_EOF);

    // make ans
    Vector_Token *tokens = Vector_Token_new();
    for(size_t i = 0; i < lexer.tokens.size; i++)
        Vector_Token_push_back(tokens, lexer.tokens.vals[i]);

    // delete lexer
    print_lexer(&lexer); //!!!!!!!!!!!!!!!!!!!! debug
    lexer_deinit(&lexer);

    return tokens;
}

void lexer_init(Lexer *lexer, char *line) {
    lexer -> line = line;
    Vector_Token_init(&lexer -> tokens);
}

void lexer_deinit(Lexer *lexer) {
    Vector_Token_deinit(&lexer -> tokens);
}

void print_lexer(Lexer *lexer) {
    printf("{\n");
    printf("    Tokens:\n");

    for (size_t i = 0; i < lexer -> tokens.size; i++) {
        Token token = Vector_Token_get(&lexer -> tokens, i);
        printf("\t\t");
        print_token(token);
    }

    printf("}\n");
}
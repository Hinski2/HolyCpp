#ifndef MAP_STR_TOKEN_H
#define MAP_STR_TOKEN_H

#include <regex.h>
#include "token.h"
#include "../data_structures/pair/pair.h"

Token get_token_from_line(char *line, char **line_new_start);
void* get_str_numb(char* line, size_t start, size_t end, TokenType TokenType);
Pair_int search(TokenType tokenType, size_t end, char *line);  // returns pos if finds else {-1, -1}, end is inclusive
void search_init(); // use it before searching

#endif
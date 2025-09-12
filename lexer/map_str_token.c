#include <stdlib.h>
#include <string.h>
#include "map_str_token.h"
#include "../utils/handle_error/handle_error.h"


regex_t search_fun[TOK_COUNT];
size_t max_search_len[TOK_COUNT];

int min(int a, int b) {
    return a < b ? a : b;
}

Token get_token_from_line(char *line, char **line_new_start) {
    search_init();
    Token token = {0};
    token.type = TOK_NONE;

    while(*line == ' ') line++; // skipp white spaces
    size_t len = strlen(line);
    if(len == 0) {
        token.type = TOK_EOF;
        *line_new_start = line;
        return token;
    }

    for(TokenType tokenType = 2; tokenType < TOK_COUNT; tokenType++) {
        Pair_int res = search(tokenType, min(len - 1, max_search_len[tokenType]), line);
        if(res.fi) continue;

        token.type = tokenType;
        if(tokenType == TOK_INT || tokenType == TOK_FLOAT || tokenType == TOK_BOOL) {
            token.value = get_str_numb(line, res.fi, res.se, tokenType);
        }

        line += res.se + 1;
        break;
    }

    *line_new_start = line;
    return token;
}

void* get_str_numb(char* line, size_t start, size_t end, TokenType TokenType) {
    // end is inclusive
    void* val;

    if(TokenType == TOK_INT) val = malloc(sizeof(int64_t));
    else if(TokenType == TOK_FLOAT) val = malloc(sizeof(double));
    else val = malloc(sizeof(bool));

    if(!val) {
        handle_error("couldn't alocate memory\n");
        exit(EXIT_FAILURE);
    }

    char char_end = line[end + 1];
    line[end + 1] = '\0';
    if(TokenType == TOK_INT) {
        char *pend;
        *(int64_t*) val = strtol(line + start, &pend, 10);
    } else if(TokenType == TOK_FLOAT) {
        char *pend;
        *(double*) val = strtod(line + start, &pend);
    } else {
        if(line[start] == 't') *(bool*) val = true;
        else *(bool*) val = false;
    }

    line[end + 1] = char_end;
    return val;
}

Pair_int search(TokenType tokenType, size_t end, char *line) {
    // end is inclusive

    Pair_int res = {-1, -1};
    char old_char = line[end + 1];
    line[end + 1] = '\0';

    regmatch_t m[1];
    if(regexec(&search_fun[tokenType], line, 1, m, 0) == 0) {
        res.fi = m[0].rm_so;
        res.se = m[0].rm_eo - 1;
    }

    line[end + 1] = old_char;
    return res;
}

void search_init() {
    static bool initialized = false;
    if(initialized) return;
    initialized = true;

    const char* pat[TOK_COUNT];

    pat[TOK_NONE]       = "";
    pat[TOK_EOF]        = "\\0"; 
    pat[TOK_FLOAT]      = "^[0-9]+\\.[0-9]*|^[0-9]*\\.[0-9]+";
    pat[TOK_INT]        = "^[0-9]+";

    pat[TOK_BOOL]       = "^(true|false)([^[:alnum:]_]|$)";
    pat[TOK_LOG_AND]    = "^(and)([^[:alnum:]_]|$)";
    pat[TOK_LOG_OR]     = "^(or)([^[:alnum:]_]|$)";

    pat[TOK_EQ]         = "^==";
    pat[TOK_NEQ]        = "^!=";
    pat[TOK_GEQ]        = "^>=";
    pat[TOK_LEQ]        = "^<=";

    pat[TOK_ADD]        = "^\\+";
    pat[TOK_SUB]        = "^-";
    pat[TOK_MULT]       = "^\\*";
    pat[TOK_DIV]        = "^/";
    pat[TOK_GT]         = "^>";
    pat[TOK_LT]         = "^<";
    pat[TOK_BIT_AND]    = "^&";
    pat[TOK_BIT_OR]     = "^\\|";
    pat[TOK_XOR]        = "^\\^";
    pat[TOK_NOT]        = "^!";

    pat[TOK_L_ROUND_PAREN] = "^\\(";
    pat[TOK_R_ROUND_PAREN] = "^\\)";

    max_search_len[TOK_NONE]     = 0;
    max_search_len[TOK_EOF]      = 1;

    max_search_len[TOK_INT]      = 20;
    max_search_len[TOK_FLOAT]    = 64;

    max_search_len[TOK_BOOL]     = 5;
    max_search_len[TOK_LOG_AND]  = 3;
    max_search_len[TOK_LOG_OR]   = 2;

    max_search_len[TOK_EQ]       = 2;
    max_search_len[TOK_NEQ]      = 2;
    max_search_len[TOK_GEQ]      = 2;
    max_search_len[TOK_LEQ]      = 2;
    max_search_len[TOK_GT]       = 1;
    max_search_len[TOK_LT]       = 1;
    max_search_len[TOK_ADD]      = 1;
    max_search_len[TOK_SUB]      = 1;
    max_search_len[TOK_MULT]     = 1;
    max_search_len[TOK_DIV]      = 1;
    max_search_len[TOK_BIT_AND]  = 1;
    max_search_len[TOK_BIT_OR]   = 1;
    max_search_len[TOK_XOR]      = 1;
    max_search_len[TOK_NOT]      = 1;

    max_search_len[TOK_L_ROUND_PAREN] = 1;
    max_search_len[TOK_R_ROUND_PAREN] = 1;


for (int i = 0; i < TOK_COUNT; ++i) {
        regcomp(&search_fun[i], pat[i], REG_EXTENDED);
    }
}
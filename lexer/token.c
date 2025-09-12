#include <stdio.h>
#include "token.h"

void print_token(Token token) {
    switch(token.type) {
        case TOK_NONE:
            printf("NONE\n");
            break;
        case TOK_EOF:
            printf("EOF\n");
            break;
        case TOK_INT:
            printf("INT: %ld\n", *(int64_t*)token.value);
            break;
        case TOK_FLOAT:
            printf("FLOAT: %f\n", *(double*)token.value);
            break;
        case TOK_BOOL:
            printf("BOOL: %s\n", (*(bool*)token.value) ? "true" : "false");
            break;
        case TOK_ADD:
            printf("ADD: +\n");
            break;
        case TOK_SUB:
            printf("SUB: -\n");
            break;
        case TOK_MULT:
            printf("MULT: *\n");
            break;
        case TOK_DIV:
            printf("DIV: /\n");
            break;
        case TOK_EQ:
            printf("EQ: ==\n");
            break;
        case TOK_NEQ:
            printf("NEQ: !=\n");
            break;
        case TOK_GT:
            printf("GT: >\n");
            break;
        case TOK_LT:
            printf("LT: <\n");
            break;
        case TOK_GEQ:
            printf("GEQ: >=\n");
            break;
        case TOK_LEQ:
            printf("LEQ: <=\n");
            break;
        case TOK_LOG_AND:
            printf("LOG_AND: and\n");
            break;
        case TOK_LOG_OR:
            printf("LOG_OR: or\n");
            break;
        case TOK_NOT:
            printf("NOT: !\n");
            break;
        case TOK_BIT_AND:
            printf("BIT_AND: &\n");
            break;
        case TOK_BIT_OR:
            printf("BIT_OR: |\n");
            break;
        case TOK_XOR:
            printf("XOR: ^\n");
            break;
        case TOK_L_ROUND_PAREN:
            printf("L_ROUND_PAREN: (\n");
            break;
        case TOK_R_ROUND_PAREN:
            printf("R_ROUND_PAREN: )\n");
            break;
        default:
            printf("UNKNOWN TOKEN\n");
            break;
    }
}
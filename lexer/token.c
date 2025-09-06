#include "token.h"

const char *bop_to_str(Bop bop) {
    switch (bop) {
        case BOP_MULT: return "*";
        case BOP_DIV:  return "/";
        case BOP_ADD:  return "+";
        case BOP_SUB:  return "-";
        default:       return "NONE";
    }
}
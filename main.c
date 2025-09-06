#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "utils/read_line/read_line.h"
#include "utils/handle_error/handle_error.h"
#include "lexer/lexer.h"

int main(int argc, char *argv[]) {
    FILE *file = NULL;

    if(argc > 1) {
        file = fopen(argv[1], "r");
        if(!file) {
            handle_error("couldn't open file %s", argv[1]);
            return errno;
        }
    } else {
        file = stdin;
    }

    char *line; 
    for(size_t i = 0; (line = read_line(file)) != NULL; i++) {
        // lexer
        Vector_Token *tokens = tokenize(line, i);

        // parser

        // eval
    }
    
    free(line);
    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "utils/read_line.h"
#include "utils/handle_error.h"

int main(int argc, char *argv[]) {
    FILE *file = NULL;

    if(argc > 1) {
        file = fopen(argv[1], "r");
        if(!file) {
            handle_error();
            return errno;
        }
    } else {
        file = stdin;
    }

    char *line; 
    while((line = read_line(file))) {
        printf("%s\n", line);
        // parser
        
        // lexer

        // eval
        
        free(line);
    }
    
    free(line);
    fclose(file);
}

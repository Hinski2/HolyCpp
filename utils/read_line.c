#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "handle_error.h"
#include "read_line.h"

char* read_line(FILE *file) {
    size_t capacity = 128, len = 0;
    char c, *buff;

    buff = malloc(capacity);
    if(!buff) {
        handle_error();
        return NULL;
    }

    while((c = getc(file)) != EOF && c != '\n') {
        buff[len++] = c;
        if(len + 1 > capacity) {
            capacity *= 2;
            char *temp = realloc(buff, capacity);

            if(!temp) {
                handle_error();
                free(buff);
                return NULL;
            }

            buff = temp;
        }
    }
    if(len == 0) {
        free(buff);
        return NULL;
    }

    buff[len] = '\0';
    return buff;
}

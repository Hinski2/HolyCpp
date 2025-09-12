#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include "handle_error.h"

void handle_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "{\n");
    fprintf(stderr, "    ERROR\n");
    fprintf(stderr, "    err: %s\n", strerror(errno));
    fprintf(stderr, "    desc: "); vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n}\n");

    va_end(args);
}

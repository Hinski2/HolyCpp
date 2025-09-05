#include <stdio.h>
#include <errno.h>
#include <string.h> 
#include "handle_error.h"

void handle_error() {
    printf("error: %s", strerror(errno));
}

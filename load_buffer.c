#include <stdlib.h>
#include <stdio.h>
#include "load_buffer.h"

load_buffer* create_load_buffer() {
    load_buffer* new = (load_buffer*) calloc(1, sizeof(load_buffer));

    if(new != NULL) {
        new->busy = 'n';
    }
}


#include <stdlib.h>
#include <stdio.h>
#include "load_buffer.h"

load_buffer* create_load_buffer() {
    load_buffer* new = (load_buffer*) calloc(1, sizeof(load_buffer));

    if(new != NULL) {
        new->busy = 'n';
    }

    return;
}

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction) {
    load_buffer->address = instruction->rt;
    load_buffer->busy = 'y';
    load_buffer->time = 2;
    
    instruction->pending_buffer = load_buffer;

    return;
}
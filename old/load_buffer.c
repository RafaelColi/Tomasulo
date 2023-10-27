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
    load_buffer->op = instruction;
    load_buffer->target = instruction->rs;
    load_buffer->address = instruction->rt;
    load_buffer->busy = 'y';
    load_buffer->time = 2;

    instruction->pending_buffer = load_buffer;
    instruction->rs->l_b_fu = load_buffer;

    return;
}

void clear_load_buffer(load_buffer* load_buffer) {
    load_buffer->busy = 'n';
    load_buffer->address = NULL;
    load_buffer->op = NULL;
    load_buffer->target = NULL;

    return;
}


void refresh_load_buffer(load_buffer* load_buffer) {
    instruction* instruction = load_buffer->op;

    instruction->rs->l_b_fu = NULL;
}
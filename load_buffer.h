#ifndef LOAD_BUFFER.H
#define LOAD_BUFFER.H
#include "instruction.h"
#include "register.h"

typedef struct load_buffer {
    char busy;
    register_* address;
    int time;
} load_buffer;

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction)

#endif
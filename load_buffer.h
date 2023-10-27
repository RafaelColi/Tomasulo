#ifndef LOAD_BUFFER_H
#define LOAD_BUFFER_H
#include "instruction.h"
#include "register.h"
#include "buffers_table.h"

typedef struct load_buffer load_buffer;

load_buffer* create_load_buffer();

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction);

void clear_load_buffer(load_buffer* load_buffer);

#endif
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "register.h"
#include "reservation_station.h"
#include "load_buffer.h"

typedef struct instruction{
    char* opcode;
    register_* rs;
    register_* rt;
    register_* rd;
    reservation_station* pending_station;
    load_buffer* pending_buffer;
    int issued;
    int executed;
    int finished;

} instruction;

instruction* create_instruction(char* opcode, char* rs, char* rt, char* rd, register_pool* r_p);

void add_operation(instruction* instruction);

void sub_operation(instruction* instruction);

void mult_operation(instruction* instruction);

void div_operation(instruction* instruction);

void load_operation(instruction* instruction);

#endif
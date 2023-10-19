#ifndef INSTRUCTION.H
#define INSTRUCTION.H
#include "register.h"
#include "reservation_station.h"

typedef struct {
    char* opcode;
    register_* rs;
    register_* rt;
    register_* rd;
    reservation_station* pending;

} instruction;

instruction* create_instruction();

void add_operation(instruction* instruction);

void sub_operation(instruction* instruction);

void mult_operation(instruction* instruction);

void div_operation(instruction* instruction);

void load();
#endif
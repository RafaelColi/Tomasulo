#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "register.h"

typedef struct instruction {
    char* opcode;
    reg* rs;
    reg* rt;
    reg* rd;
    int issued;
    int executed;
    int finished;
    double temp;
} instruction;

instruction* create_instruction(char* opcode, char* rs, char* rt, char* rd, registers_pool* r_p);

void begin_operation(instruction* instruction);

void add_operation(instruction* instruction);

void sub_operation(instruction* instruction);

void mult_operation(instruction* instruction);

void div_operation(instruction* instruction);

void load_operation(instruction* instruction);

#endif
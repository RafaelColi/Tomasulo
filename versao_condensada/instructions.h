#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "stations.h"

typedef struct register_ {
    char* id;
    double value;
    reservation_station* r_s_fu;
    load_buffer* l_b_fu;
} register_;

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

typedef struct register_pool {
    register_** registers;
    int size;
    int cap;
} register_pool;

instruction* create_instruction(char* opcode, char* rs, char* rt, char* rd, register_pool* r_p);

void add_operation(instruction* instruction);

void sub_operation(instruction* instruction);

void mult_operation(instruction* instruction);

void div_operation(instruction* instruction);

void load_operation(instruction* instruction);

register_* create_register(char* id);

void add_register_to_pool(register_pool* register_pool, register_* reg);

register_pool* create_register_pool(int size);

#endif
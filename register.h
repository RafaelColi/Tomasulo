#ifndef REGISTER_H
#define REGISTER_H

typedef struct reg {
    char* id;
    double value;
} reg;

typedef struct registers_pool {
    reg** registers;
    int size;
    int cap;
} registers_pool;

reg* create_register(char* id);

void add_register_to_pool(registers_pool* register_pool, reg* reg);

registers_pool* create_register_pool(int size);

int register_pool_is_full(registers_pool* reg_pool);

int register_pool_is_empty(registers_pool* reg_pool);

#endif
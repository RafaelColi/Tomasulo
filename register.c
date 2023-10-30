#include <stdlib.h>
#include <stdio.h>
#include "register.h"

registers_pool* create_register_pool(int size) {
    registers_pool* new = (registers_pool*) calloc(1, sizeof(registers_pool));

    if(new != NULL) {
        new->registers = (reg**) calloc(size, sizeof(reg*));
        new->cap = size;
    }

    return new;
}

reg* create_register(char* id) {
    reg* new = (reg*) calloc(1, sizeof(reg));

    if(new != NULL) {
        new->id = (char*) calloc(4, sizeof(char));
        new->id = id;
    }

    return new;
}

void add_register_to_pool(registers_pool* reg_pool, reg* reg) {
    if(register_pool_is_full(reg_pool)) {
        printf("Register pool is full\n");
        return;
    }

    reg_pool->registers[reg_pool->size] = reg;
    reg_pool->size++;

    return;
}

int register_pool_is_full(registers_pool* reg_pool) {
    if(reg_pool->size == reg_pool->cap) {
        return 1;
    }

    return 0;
}

int register_pool_is_empty(registers_pool* reg_pool) {
    if(reg_pool->size == 0) {
        return 1;
    }

    return 0;
}
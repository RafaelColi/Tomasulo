#include <stdlib.h>
#include <stdio.h>
#include "register.h"

registers_pool* create_register_pool(int size) {
    registers_pool* new = (registers_pool*) calloc(1, sizeof(registers_pool));

    if(new == NULL) {
        printf("Failed to allocate memory for register pool\n");
        return NULL;
    }

    new->registers = (reg**) calloc(size, sizeof(reg*));

    if(new->registers == NULL) {
        printf("Failed to allocate memory for registers array\n");
        return NULL;
    }

    new->cap = size;

    return new;
}

reg* create_register(char* id) {
    reg* new = (reg*) calloc(1, sizeof(reg));

    if(new == NULL) {
        printf("Failed to allocate memory for register\n");
        return NULL;
    }

    new->id = id;

    return new;
}

void add_register_to_pool(registers_pool* reg_pool, reg* reg) {
    if(reg_pool == NULL) {
        printf("NULL pointer to registers pool\nadd_register_to_pool() cancelled\n");
        return;
    }

    if(reg == NULL) {
        printf("NULL pointer to register\nadd_register_to_pool() cancelled\n");
        return;
    }
    
    if(register_pool_is_full(reg_pool)) {
        return;
    }

    reg_pool->registers[reg_pool->size] = reg;
    reg_pool->size++;

    return;
}

int register_pool_is_full(registers_pool* reg_pool) {
    if(reg_pool == NULL) {
        printf("NULL pointer to registers pool\nregister_pool_is_full() cancelled\n");
        return -1;
    }
    
    if(reg_pool->size == reg_pool->cap) {
        printf("Register pool is full\n");
        return 1;
    }

    return 0;
}

int register_pool_is_empty(registers_pool* reg_pool) {
    if(reg_pool == NULL) {
        printf("NULL pointer to registers pool\nregister_pool_is_empty() cancelled\n");
        return -1;
    }
    
    if(reg_pool->size == 0) {
        return 1;
    }

    return 0;
}
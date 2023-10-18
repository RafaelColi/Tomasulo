#include <stdlib.h>
#include <stdio.h>
#include "register.h"

register_pool* create_register_pool(int size) {
    register_pool* new = (register_pool*) calloc(1, sizeof(register_pool));

    if(new != NULL) {
        new->registers = (register_**) calloc(size, sizeof(register_*));

        if(new->registers == NULL) {
            return NULL;
        }

        new->size = size;
    }
}

register_* create_register() {
    register_* new = (register_*) calloc(1, sizeof(register_));

    return new;
}

void add_register_to_pool(register_pool* register_pool, register_* reg) {
    if(register_pool_is_full(register_pool)) {
        printf("Register pool is full\n");
        return;
    }

    register_pool->registers[register_pool->size] = reg;
    register_pool->size++;

    return;
}

int register_pool_is_full(register_pool* stations_table) {
    if(stations_table->size == stations_table->cap) {
        return 1;
    }

    return 0;
}

int register_pool_is_empty(register_pool* stations_table) {
    if(stations_table->size == 0) {
        return 1;
    }

    return 0;
}


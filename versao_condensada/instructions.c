#include <stdlib.h>
#include <stdio.h>
#include "instructions.h"

instruction* create_instruction(char* opcode, char* rs, char* rt, char* rd, register_pool* r_p) {
    instruction* new = (instruction*) calloc(1, sizeof(instruction));

    if(new != NULL) {
        for(int i = 0; i < r_p->size; i++) {
            register_* r = r_p->registers[i];

            if(strcmp(r->id, rs)) {
                new->rs = r;
            }

            if(strcmp(r->id, rd)) {
                new->rd = r;
            }

            if(strcmp(r->id, rt)) {
                new->rt = r;
            }
        }

        new->issued = -1;
        new->executed = -1;
        new->finished = -1;
    }

    return new;

}

void add_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value + instruction->rd->value;
}

void sub_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value - instruction->rd->value;
}

void mult_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value * instruction->rd->value;
}

void div_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value / instruction->rd->value;
}

void load_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value;
}

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

register_* create_register(char* id) {
    register_* new = (register_*) calloc(1, sizeof(register_));

    if(new != NULL) {
        new->id = id;
    }

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
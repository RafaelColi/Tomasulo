#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "instruction.h"

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

}
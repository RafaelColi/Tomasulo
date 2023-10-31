#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "instruction.h"

instruction* create_instruction(char* opcode, char* rs, char* rt, char* rd, registers_pool* r_p) {
    if(r_p == NULL) {
        printf("NULL pointer to registers pool\ncreate_instruction() cancelled\n");
        return NULL;
    }
    
    instruction* new = (instruction*) calloc(1, sizeof(instruction));

    if(new == NULL) {
        printf("Failed to allocate memory for instruction\n");
        return NULL;
    }

    for(int i = 0; i < r_p->size; i++) {
        reg* r = r_p->registers[i];
        
        if(!strcmp(r->id, rs)) {
            new->rs = r;
        }

        if(!strcmp(r->id, rt)) {
            new->rt = r;
        }

        if(!strcmp(r->id, rd)) {
            new->rd = r;
        }
    }

    new->opcode = opcode;

    new->issued = -1;
    new->executed = -1;
    new->finished = -1;

    return new;
}

void add_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("NULL pointer to instruction\nadd_operation() cancelled");
        return;
    }

    instruction->rs->value = instruction->rt->value + instruction->rd->value;

    return;
}

void sub_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("NULL pointer to instruction\nsub_operation() cancelled");
        return;
    }

    instruction->rs->value = instruction->rt->value - instruction->rd->value;

    return;
}

void mult_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("NULL pointer to instruction\nmult_operation() cancelled");
        return;
    }

    instruction->rs->value = instruction->rt->value * instruction->rd->value;

    return;
}

void div_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("NULL pointer to instruction\ndiv_operation() cancelled");
        return;
    }

    instruction->rs->value = instruction->rt->value / instruction->rd->value;

    return;
}

void load_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("NULL pointer to instruction\nload_operation() cancelled");
        return;
    }

    instruction->rs->value = instruction->rt->value;

    return;
}
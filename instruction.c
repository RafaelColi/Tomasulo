#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"


typedef struct instruction_queue {
    instruction* instructions;
    int tam;
} instruction_queue;

typedef struct register_ {
    char name[2];
    double value;
} register_;

typedef struct {
    char* opcode;
    register_* rs;
    register_* rt;
    register_* rd;
    reservation_station* pending;

} instruction;


void issue() {

}

void execute(instruction* instruction, stations_table* stations_table) {
    
}

void write_result() {

}

void load() {

}

void add(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value + instruction->rd->value;
}

void sub(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value - instruction->rd->value;
}

void mult(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value * instruction->rd->value;
}

void div(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value / instruction->rd->value;
}



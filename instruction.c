#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"
#include "instruction.h"

instruction* create_instruction() {

}

#include <stdlib.h>
#include <stdio.h>

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

void load() {

}
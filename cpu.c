#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

cpu* create_cpu() {
    cpu* new = (cpu*) calloc(1, sizeof(cpu));

    if(new == NULL) {
        printf("Failed to allocate memory for cpu");
        return NULL;
    }

    return new;
}

void next_clock(cpu* cpu) {
    if(cpu == NULL) {
        printf("NULL pointer to cpu\nnext_clock() cancelled\n");
        return;
    }

    cpu->clock++;

    return;
}
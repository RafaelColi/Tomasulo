#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

cpu* create_cpu() {
    cpu* new = (cpu*) calloc(1, sizeof(cpu));

    return new;
}

void next_clock(cpu* cpu) {
    cpu->clock++;

    return;
}
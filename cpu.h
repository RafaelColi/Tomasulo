#ifndef CPU_H
#define CPU_H

typedef struct cpu {
    int clock;
    int finished;
} cpu;

cpu* create_cpu();

void next_clock(cpu* cpu);

#endif
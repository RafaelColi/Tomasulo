#ifndef CPU_H
#define CPU_H

typedef struct cpu cpu;

cpu* create_cpu();

void next_clock(cpu* cpu);

#endif
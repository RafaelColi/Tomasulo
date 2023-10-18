#ifndef INSTRUCTION_QUEUE.H
#define INSTRUCTION_QUEUE.H
#include "instruction.h"

typedef struct instruction_queue {
    instruction** instructions;
    int size;
    int cap;
} instruction_queue;

#endif
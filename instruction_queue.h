#ifndef INSTRUCTION_QUEUE_H
#define INSTRUCTION_QUEUE_H
#include "instruction.h"

typedef struct instruction_queue instruction_queue;

instruction_queue* create_instruction_queue(int size);

void add_instruction_into_queue(instruction* instruction, instruction_queue* instruction_queue);

instruction* instruction_queue_front(instruction_queue* instruction_queue);

void remove_instruction_from_queue(instruction_queue* instruction_queue);

int instruction_queue_is_full(instruction_queue* instruction_queue);

int instruction_queue_is_empty(instruction_queue* instruction_queue);

#endif
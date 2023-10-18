#include <stdlib.h>
#include <stdio.h>
#include <instruction_queue.h>

instruction_queue* create_instruction_queue(int num) {
    instruction_queue* new = (instruction_queue*) calloc(1, sizeof(instruction_queue));

    if(new != NULL) {
        new->instructions = (instruction**) calloc(num, sizeof(instruction*));
        new->size = num;
    }

    return new;
}

void add_instruction_into_queue(instruction* instruction, instruction_queue* instruction_queue) {
    if(instruction_queue_is_full(instruction_queue)) {
       printf("Queue is full\n");
       return; 
    }

    instruction_queue->instructions[instruction_queue->size] = instruction;
    instruction_queue->size++;

    return;
}

instruction* remove_instruction_from_queue(instruction_queue* instruction_queue) {
    if(instruction_queue_is_empty(instruction_queue)) {
        printf("Queue is empty\n");
        return NULL;
    }

    instruction* removed = instruction_queue->instructions[0];

    for(int i = 0; i < instruction_queue->size - 1; i++) {
        instruction_queue->instructions[i] = instruction_queue->instructions[i + 1];
    }

    instruction_queue->size--;

    return removed;
}

int instruction_queue_is_full(instruction_queue* instruction_queue) {
    if(instruction_queue->size == instruction_queue->cap) {
        return 1;
    }

    return 0;
}

int instruction_queue_is_empty(instruction_queue* instruction_queue) {
    if(instruction_queue->size == 0) {
        return 1;
    }

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"
#include "instruction.h"
#include "instruction_queue.h"
#include "stations_table.h"
#include "register.h"
#include "load_buffer.h"
#include "buffers_table.h"

void issue(instruction_queue* instruction_queue, stations_table* stations_table) {

    for(int i = 0; i < instruction_queue->size; i++) {
        instruction* instruction = instruction_queue->instructions;

        if(instruction->opcode = "add" || instruction->opcode == "sub") {
            
        }
    }
}

void execute(instruction* instruction, stations_table* stations_table) {
    
}

void write_result() {

}

int main() {

}
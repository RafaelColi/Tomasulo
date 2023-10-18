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
    instruction* instruction = instruction_queue_front(instruction_queue);

    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if(instruction->opcode == r_s->op->opcode) {
            if(r_s->busy == 'n') {
                add_instruction_to_reservation_station(r_s, instruction);
            }
        }
    }
}

void execute(instruction* instruction, stations_table* stations_table) {
    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if(r_s->busy == 'y') {
            if(r_s->qj == NULL && r_s->qk == NULL) {
                if(r_s->time > 0) {
                    r_s->time--;
                } else {
                    write_result(r_s);
                }
            }
        }
    }
}

void write_result(reservation_station* reservation_station) {

}

int main() {

}
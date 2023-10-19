#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"
#include "instruction.h"
#include "instruction_queue.h"
#include "stations_table.h"
#include "register.h"
#include "load_buffer.h"
#include "buffers_table.h"
#include <string.h>

void issue(instruction_queue* instruction_queue, stations_table* stations_table) {
    instruction* instruction = instruction_queue_front(instruction_queue);

    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if((strcmp(instruction->opcode, "add") && strcmp(r_s->name, "add")) || (strcmp(instruction->opcode, "sub") && strcmp(r_s->name, "add")) ||
        (strcmp(instruction->opcode, "mult") && strcmp(r_s->name, "mult")) || (strcmp(instruction->opcode, "div") && strcmp(r_s->name, "mult"))) {
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
                    write_result(r_s, stations_table);
                }
            }
        }
    }
}

void write_result(reservation_station* reservation_station, stations_table* stations_table) {
    instruction* instruction = reservation_station->op;

    instruction->pending = NULL;
    instruction->rs->fu = NULL;

    if(strcmp(instruction->opcode, "add")) {
        add_operation(instruction);
    } else if(strcmp(instruction->opcode, "sub")) {
        sub_operation(instruction);
    } else if(strcmp(instruction->opcode, "mult")) {
        mult_operation(instruction);
    } else if(strcmp(instruction->opcode, "div")) {
        div_operation(instruction);
    }
    
    reservation_station->busy = 'n';
    reservation_station->op = NULL;
    reservation_station->qj = NULL;
    reservation_station->qk = NULL;
    reservation_station->vj = NULL;
    reservation_station->vk = NULL;

    refresh_stations_table(stations_table);
}

int main() {

}
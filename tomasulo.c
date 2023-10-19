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

void issue(instruction_queue* instruction_queue, stations_table* stations_table, buffers_table* buffers_table) {
    instruction* instruction = instruction_queue_front(instruction_queue);

    if(strcmp(instruction->opcode, "load")) {
        for(int i = 0; i < buffers_table->size; i++) {
            load_buffer* l_b = buffers_table->buffers[i];

            if(l_b->busy == 'n') {
                add_instruction_to_load_buffer(l_b, instruction);
            }
        }
    }

    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if((strcmp(instruction->opcode, "add") && strcmp(r_s->name, "add")) || (strcmp(instruction->opcode, "sub") && strcmp(r_s->name, "add")) ||
        (strcmp(instruction->opcode, "mult") && strcmp(r_s->name, "mult")) || (strcmp(instruction->opcode, "div") && strcmp(r_s->name, "mult"))) {
            if(r_s->busy == 'n') {
                add_instruction_to_reservation_station(r_s, instruction);
                remove_instruction_from_queue(instruction_queue);
            }
        }
    }
}

void execute(instruction* instruction, stations_table* stations_table, buffers_table* buffers_table) {
    for(int i = 0; i < buffers_table->buffers; i++) {
        load_buffer* l_b = buffers_table->buffers[i];

        if(l_b->busy == 'y') {
            if(l_b->time > 0) {
                l_b->time--;
            }
        }
    }

    
    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if(r_s->busy == 'y') {
            if(r_s->qj == NULL && r_s->qk == NULL) {
                if(r_s->time > 0) {
                    r_s->time--;
                } else {
                    write_result(r_s, stations_table, buffers_table);
                }
            }
        }
    }
}

void write_result(reservation_station* reservation_station, stations_table* stations_table, buffers_table* buffers_table) {
    instruction* instruction = reservation_station->op;

    instruction->pending_station = NULL;
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
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

    execute(stations_table, buffers_table);
}

void execute(stations_table* stations_table, buffers_table* buffers_table) {
    for(int i = 0; i < buffers_table->buffers; i++) {
        load_buffer* l_b = buffers_table->buffers[i];

        if(l_b->busy == 'y') {
            if(l_b->target->l_b_fu == NULL && l_b->target->r_s_fu == NULL) {
                if(l_b->time > 0) {
                    l_b->time--;
                } else {
                    write_result(l_b->op);
                }
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
                    write_result(r_s->op);
                }
            }
        }
    }
}

void write_result(instruction* instruction) {
    if(strcmp(instruction->opcode, "load")) {
        load_buffer* load_buffer = instruction->pending_buffer;

        instruction->pending_buffer = NULL;
        instruction->rs->l_b_fu = NULL;

        load_operation(instruction);

        load_buffer->busy = 'n';
        load_buffer->address = NULL;
        load_buffer->op = NULL;
        load_buffer->target = NULL;

        refresh_buffers_table(load_buffer->buffers_table);
    } else {
        reservation_station* reservation_station = instruction->pending_station;
        instruction->pending_station = NULL;
        instruction->rs->r_s_fu = NULL;

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

        refresh_stations_table(reservation_station->stations_table);
    }
}

int main() {

}
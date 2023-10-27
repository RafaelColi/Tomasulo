#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cpu.h"
#include "instruction_queue.h"
#include "instructions.h"
#include "tables.h"

void write_result(instruction* instruction, cpu* cpu) {
    if(strcmp(instruction->opcode, "load")) {
        load_buffer* load_buffer = instruction->pending_buffer;

        instruction->pending_buffer = NULL;
        instruction->rs->l_b_fu = NULL;

        load_operation(instruction);

        clear_load_buffer(load_buffer);

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

        clear_reservation_station(reservation_station);

        refresh_stations_table(reservation_station->stations_table);
    }

    instruction->finished = cpu->clock;
    cpu->finished++;

    return;

}

void execute(stations_table* stations_table, buffers_table* buffers_table, cpu* cpu) {
    for(int i = 0; i < buffers_table->buffers; i++) {
        load_buffer* l_b = buffers_table->buffers[i];

        if(l_b->busy == 'y') {
            if(l_b->target->l_b_fu == NULL && l_b->target->r_s_fu == NULL) {
                if(l_b->time > 0) {
                    if(l_b->op->executed == -1) {
                        l_b->op->executed = cpu->clock;
                    }

                    l_b->time--;
                } else {
                    write_result(l_b->op, cpu);
                }
            }
        }
    }

    
    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if(r_s->busy == 'y') {
            if(r_s->qj == NULL && r_s->qk == NULL) {
                if(r_s->time > 0) {
                    if(r_s->op->executed == -1) {
                        r_s->op->executed = cpu->clock;
                    }
                    r_s->time--;
                } else {
                    write_result(r_s->op, cpu);
                }
            }
        }
    }

    return;

}

void issue(instruction_queue* instruction_queue, stations_table* stations_table, buffers_table* buffers_table, cpu* cpu) {
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

    instruction->issued = cpu->clock;

    execute(stations_table, buffers_table, cpu);

    return;

}

void tomasulo(instruction_queue* instruction_queue, stations_table* stations_table, buffers_table* buffers_table, cpu* cpu) {
    int n_instructions = instruction_queue->size;

    while(cpu->finished < n_instructions) {
        if(!instruction_queue_is_empty(instruction_queue)) {
            issue(instruction_queue, stations_table, buffers_table, cpu);
        } else {
            execute(stations_table, buffers_table, cpu);
        }

        next_clock(cpu);
    }

    return;

}

int main() {
    
    int n_registers = 16;
    int n_instructions = 6;

    register_pool* reg_pool = create_register_pool(n_registers);
    instruction_queue* inst_q = create_instruction_queue(n_instructions);
    instruction_queue* instructions = create_instruction_queue(n_instructions);
    stations_table* s_t = create_stations_table(3, 2);
    buffers_table* b_t = create_buffers_table(3);
    cpu* cpu = create_cpu();

    for(int i = 0; i < n_registers; i++) {
        char* id;
        sprintf(id, "f%d", i * 2);
        register_* reg = create_register(id);
        add_register_to_pool(reg_pool, reg);   
    }

    instruction* i1 = create_instruction("load", "f6", "f30", "", reg_pool);
    instruction* i2 = create_instruction("load", "f2", "f28", "", reg_pool);
    instruction* i3 = create_instruction("mult", "f0", "f2", "f4", reg_pool);
    instruction* i4 = create_instruction("sub", "f8", "f2", "f6", reg_pool);
    instruction* i5 = create_instruction("div", "f10", "f0", "f6", reg_pool);
    instruction* i6 = create_instruction("add", "f6", "f8", "f2", reg_pool);

    add_instruction_into_queue(i1, inst_q);
    add_instruction_into_queue(i2, inst_q);
    add_instruction_into_queue(i3, inst_q);
    add_instruction_into_queue(i4, inst_q);
    add_instruction_into_queue(i5, inst_q);
    add_instruction_into_queue(i6, inst_q);

    for(int i = 0; i < inst_q->size; i++) {
        add_instruction_into_queue(inst_q->instructions[i], instructions);
    }

    tomasulo(inst_q, s_t, b_t, cpu);

    for(int i = 0; i < instructions->size; i++) {
        instruction* instruction = instructions->instructions[i];

        printf("Instruction %d -> Issued: %d, Executed: %d, Write Result: %d", i, instruction->issued, instruction->executed, instruction->finished);
    }

    for(int i = 0; i < reg_pool->size; i++) {
        register_* reg = reg_pool->registers[i];

        if(reg != NULL) {
            printf("Register %s -> Value: %f", reg->id, reg->value);
        }
    }

    return 0;
}
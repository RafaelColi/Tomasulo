#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "instruction_queue.h"
#include "instruction.h"
#include "stations.h"
#include "register.h"

void write_result(instruction* instruction, cpu* cpu) {
    instruction->finished = cpu->clock + 1;
    instruction->rs->value = instruction->temp;
    cpu->finished++;

    return;
}

void execute(stations_table* stations_table, buffers_table* buffers_table, cpu* cpu, common_data_bus* cdb) {
    for(int i = 0; i < buffers_table->size; i++) {
        load_buffer* l_b = buffers_table->buffers[i];

        if(l_b->busy == 'y') {
            if((register_is_available(l_b->target, cdb) && register_is_available(l_b->address, cdb)) ||
            (register_busy_with_instruction(l_b->target, l_b->instruction, cdb) && register_busy_with_instruction(l_b->address, l_b->instruction, cdb))) {
                if(l_b->time > 0) {
                        
                    if(l_b->instruction->executed == -1) {
                        l_b->instruction->executed = cpu->clock;
                        begin_operation(l_b->instruction);
                    }
                    
                    l_b->time--;
                } else {
                    write_result(l_b->instruction, cpu);
                    clear_load_buffer(l_b, cdb);
                    refresh_stations_table(stations_table, cdb);
                }
            }
        }
    }
    
    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if(r_s->busy == 'y') {
            if(r_s->qj == NULL && r_s->qk == NULL) {
                if(r_s->time > 0) {
                    if(r_s->instruction->executed == -1) {
                        r_s->instruction->executed = cpu->clock;
                        begin_operation(r_s->instruction);
                    }

                    r_s->time--;
                } else {
                    write_result(r_s->instruction, cpu);
                    clear_reservation_station(r_s, cdb);
                    refresh_stations_table(stations_table, cdb);
                }
            }
        }
    }

    return;

}

void issue(instruction_queue* instruction_queue, stations_table* stations_table, buffers_table* buffers_table, cpu* cpu, common_data_bus* cdb) {
    instruction* instruction = instruction_queue_front(instruction_queue);

    if(!strcmp(instruction->opcode, "load")) {
        for(int i = 0; i < buffers_table->size; i++) {
            load_buffer* l_b = buffers_table->buffers[i];

            if(l_b->busy == 'n') {
                add_instruction_to_load_buffer(l_b, instruction, cdb);
                break;
            }
        }
    }

    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if((!strcmp(instruction->opcode, "add") && !strcmp(r_s->name, "add")) || (!strcmp(instruction->opcode, "sub") && !strcmp(r_s->name, "add")) ||
        (!strcmp(instruction->opcode, "mult") && !strcmp(r_s->name, "mult")) || (!strcmp(instruction->opcode, "div") && !strcmp(r_s->name, "mult"))) {
            if(r_s->busy == 'n') {
                add_instruction_to_reservation_station(r_s, instruction, cdb);
                break;
            }
        }
    }

    instruction->issued = cpu->clock;
    remove_instruction_from_queue(instruction_queue);

    execute(stations_table, buffers_table, cpu, cdb);

    return;

}

void tomasulo(instruction_queue* instruction_queue, stations_table* stations_table, buffers_table* buffers_table, cpu* cpu, common_data_bus* cdb) {
    int n_instructions = instruction_queue->size;

    next_clock(cpu);

    while(cpu->finished < n_instructions) {
        if(!instruction_queue_is_empty(instruction_queue)) {
            issue(instruction_queue, stations_table, buffers_table, cpu, cdb);
        } else {
            execute(stations_table, buffers_table, cpu, cdb);
        }

        next_clock(cpu);
    }

    return;

}

int main() {
    int n_registers = 16;
    int n_instructions = 6;
    
    registers_pool* reg_pool = create_register_pool(n_registers);
    instruction_queue* inst_q = create_instruction_queue(n_instructions);
    instruction_queue* instructions = create_instruction_queue(n_instructions);
    stations_table* s_t = create_stations_table(3, 2);
    buffers_table* b_t = create_buffers_table(3);
    cpu* cpu = create_cpu();

    for(int i = 0; i < n_registers; i++) {
        char* id = (char*) calloc(4, sizeof(char));
        sprintf(id, "f%d", (i * 2));
        add_register_to_pool(reg_pool, create_register(id));
    }

    common_data_bus* cdb = create_common_data_bus(reg_pool);

    reg_pool->registers[15]->value = 2; /* Atribuindo valor inicial para o registrador f30 */
    reg_pool->registers[14]->value = 5; /* Atribuindo valor inicial para o registrador f28 */
    reg_pool->registers[2]->value = 3; /* Atribuindo valor inicial para o registrador f4 */

    instruction* i1 = create_instruction("load", "f6", "f30", "", reg_pool);
    instruction* i2 = create_instruction("load", "f2", "f28", "", reg_pool);
    instruction* i3 = create_instruction("mult", "f0", "f2", "f4", reg_pool);
    instruction* i4 = create_instruction("sub", "f8", "f6", "f2", reg_pool);
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

    tomasulo(inst_q, s_t, b_t, cpu, cdb);

    //system("clear");

    for(int i = 0; i < instructions->size; i++) {
        instruction* instruction = instructions->instructions[i];

        printf("Instruction %d -> Issued: %d, Executed: %d, Write Result: %d\n", i, instruction->issued, instruction->executed, instruction->finished);
    }

    printf("\n\n");

    for(int i = 0; i < reg_pool->size; i++) {
        reg* reg = reg_pool->registers[i];

        if(reg != NULL) {
            printf("Register %s -> Value: %f\n", reg->id, reg->value);
        }
    }

    return 0;
}
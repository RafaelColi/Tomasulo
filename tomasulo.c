#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "instruction_queue.h"
#include "instruction.h"
#include "stations.h"
#include "register.h"


void write_result(stations_table* stations_table, buffers_table* buffers_table, instruction* instruction, cpu* cpu, common_data_bus* cdb) {
    if(!strcmp(instruction->opcode, "load")) {
        load_operation(instruction);

    } else {
        if(!strcmp(instruction->opcode, "add")) {
            add_operation(instruction);
        } else if(!strcmp(instruction->opcode, "sub")) {
            sub_operation(instruction);
        } else if(!strcmp(instruction->opcode, "mult")) {
            mult_operation(instruction);
        } else if(!strcmp(instruction->opcode, "div")) {
            div_operation(instruction);
        }
    }

    instruction->finished = cpu->clock;
    cpu->finished++;

    return;
}

void execute(stations_table* stations_table, buffers_table* buffers_table, cpu* cpu, common_data_bus* cdb) {
    for(int i = 0; i < buffers_table->size; i++) {
        load_buffer* l_b = buffers_table->buffers[i];

        if(l_b->busy == 'y') {
            if(register_is_available(l_b->target, cdb) && register_is_available(l_b->address, cdb)) {
                if(l_b->time > 0) {
                        
                    if(l_b->instruction->executed == -1) {
                        l_b->instruction->executed = cpu->clock;
                    }
                        
                    }
                    l_b->time--;
                } else {
                    write_result(stations_table, buffers_table, l_b->instruction, cpu, cdb);
                    clear_load_buffer(l_b, cdb);
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
                    }
                    r_s->time--;
                } else {
                    write_result(stations_table, buffers_table, r_s->instruction, cpu, cdb);
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
            }
        }
    }

    for(int i = 0; i < stations_table->size; i++) {
        reservation_station* r_s = stations_table->stations[i];

        if((!strcmp(instruction->opcode, "add") && !strcmp(r_s->name, "add")) || (!strcmp(instruction->opcode, "sub") && !strcmp(r_s->name, "add")) ||
        (!strcmp(instruction->opcode, "mult") && !strcmp(r_s->name, "mult")) || (!strcmp(instruction->opcode, "div") && !strcmp(r_s->name, "mult"))) {
            if(r_s->busy == 'n') {
                add_instruction_to_reservation_station(r_s, instruction, cdb);
                remove_instruction_from_queue(instruction_queue);
            }
        }
    }

    instruction->issued = cpu->clock;

    execute(stations_table, buffers_table, cpu, cdb);

    return;

}

void tomasulo(instruction_queue* instruction_queue, stations_table* stations_table, buffers_table* buffers_table, cpu* cpu, common_data_bus* cdb) {
    int n_instructions = instruction_queue->size;

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

    reg* f0 = create_register("f0");
    reg* f2 = create_register("f2");
    reg* f4 = create_register("f4");
    reg* f6 = create_register("f6");
    reg* f8 = create_register("f8");
    reg* f10 = create_register("f10");
    reg* f12 = create_register("f12");
    reg* f14 = create_register("f14");
    reg* f16 = create_register("f16");
    reg* f18 = create_register("f18");
    reg* f20 = create_register("f20");
    reg* f22 = create_register("f22");
    reg* f24 = create_register("f24");
    reg* f26 = create_register("f26");
    reg* f28 = create_register("f28");
    reg* f30 = create_register("f30");

    add_register_to_pool(reg_pool, f0);
    add_register_to_pool(reg_pool, f2);
    add_register_to_pool(reg_pool, f4);
    add_register_to_pool(reg_pool, f6);
    add_register_to_pool(reg_pool, f8);
    add_register_to_pool(reg_pool, f10);
    add_register_to_pool(reg_pool, f12);
    add_register_to_pool(reg_pool, f14);
    add_register_to_pool(reg_pool, f16);
    add_register_to_pool(reg_pool, f18);
    add_register_to_pool(reg_pool, f20);
    add_register_to_pool(reg_pool, f22);
    add_register_to_pool(reg_pool, f24);
    add_register_to_pool(reg_pool, f26);
    add_register_to_pool(reg_pool, f28);
    add_register_to_pool(reg_pool, f30);

    /*for(int i = 0; i < n_registers; i++) {
        char* id = (char*) calloc(4, sizeof(char));
        sprintf(id, "f%d", (i * 2));
        printf("passou");
        add_register_to_pool(reg_pool, create_register(id));
    }*/

    printf("passou");
    common_data_bus* cdb = create_common_data_bus(reg_pool);


    /*instruction* i1 = create_instruction("load", f6, f30, NULL, reg_pool);
    instruction* i2 = create_instruction("load", f2, f28, NULL, reg_pool);
    instruction* i3 = create_instruction("mult", f0, f2, f4, reg_pool);
    instruction* i4 = create_instruction("sub", f8, f2, f6, reg_pool);
    instruction* i5 = create_instruction("div", f10, f0, f6, reg_pool);
    instruction* i6 = create_instruction("add", f6, f8, f2, reg_pool);*/

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

    tomasulo(inst_q, s_t, b_t, cpu, cdb);

    for(int i = 0; i < instructions->size; i++) {
        instruction* instruction = instructions->instructions[i];

        printf("Instruction %d -> Issued: %d, Executed: %d, Write Result: %d", i, instruction->issued, instruction->executed, instruction->finished);
    }

    for(int i = 0; i < reg_pool->size; i++) {
        reg* reg = reg_pool->registers[i];

        if(reg != NULL) {
            printf("Register %s -> Value: %f", reg->id, reg->value);
        }
    }

    return 0;
}
/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct buffers_table buffers_table;
typedef struct cpu cpu;
typedef struct instruction_queue instruction_queue;
typedef struct instruction instruction;
typedef struct load_buffer load_buffer;
typedef struct register_ register_;
typedef struct register_pool register_pool;
typedef struct reservation_station reservation_station;
typedef struct stations_table stations_table;


typedef struct buffers_table {
    load_buffer** buffers;
    int size;
    int cap;
} buffers_table;

buffers_table* create_buffers_table(int size);

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table);

int buffers_table_is_full(buffers_table* buffers_table);

int buffers_table_is_empty(buffers_table* buffers_table);

void refresh_buffers_table(buffers_table* buffers_table);

typedef struct cpu {
    int clock;
    int finished;
} cpu;

cpu* create_cpu();

void next_clock(cpu* cpu);

typedef struct instruction_queue {
    instruction** instructions;
    int size;
    int cap;
} instruction_queue;

instruction_queue* create_instruction_queue(int size);

void add_instruction_into_queue(instruction* instruction, instruction_queue* instruction_queue);

instruction* instruction_queue_front(instruction_queue* instruction_queue);

void remove_instruction_from_queue(instruction_queue* instruction_queue);

int instruction_queue_is_full(instruction_queue* instruction_queue);

int instruction_queue_is_empty(instruction_queue* instruction_queue);

typedef struct instruction{
    char* opcode;
    register_* rs;
    register_* rt;
    register_* rd;
    reservation_station* pending_station;
    load_buffer* pending_buffer;
    int issued;
    int executed;
    int finished;

} instruction;

instruction* create_instruction(char* opcode, char* rs, char* rt, char* rd, register_pool* r_p);

void add_operation(instruction* instruction);

void sub_operation(instruction* instruction);

void mult_operation(instruction* instruction);

void div_operation(instruction* instruction);

void load_operation(instruction* instruction);

typedef struct load_buffer {
    char busy;
    register_* target;
    register_* address;
    int time;
    instruction* op;
    buffers_table* buffers_table;

} load_buffer;

load_buffer* create_load_buffer();

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction);

void clear_load_buffer(load_buffer* load_buffer);

void refresh_load_buffer(load_buffer* load_buffer);

typedef struct register_ {
    char* id;
    double value;
    reservation_station* r_s_fu;
    load_buffer* l_b_fu;
} register_;

typedef struct register_pool {
    register_** registers;
    int size;
    int cap;
} register_pool;


register_* create_register(char* id);

void add_register_to_pool(register_pool* register_pool, register_* reg);

register_pool* create_register_pool(int size);

int register_pool_is_full(register_pool* stations_table);

typedef struct reservation_station {
    int time;
    char* name;
    char busy;
    instruction* op;
    register_* vj;
    register_* vk;
    register_* qj;
    register_* qk;
    stations_table* stations_table;

} reservation_station;


reservation_station* create_reservation_station(char* name);

void add_instruction_to_reservation_station(reservation_station* reservation_station, instruction* instruction);

void refresh_reservation_station(reservation_station* reservation_station);

void clear_reservation_station(reservation_station* reservation_station);

typedef struct stations_table {
    reservation_station** stations;
    int size;
    int cap;
} stations_table;

stations_table* create_stations_table(int add, int mult);

void add_reservation_station(stations_table* stations_table, reservation_station* reservation_station);

int stations_table_is_full(stations_table* stations_table);

int stations_table_is_empty(stations_table* stations_table);

void refresh_stations_table(stations_table* stations_table);

buffers_table* create_buffers_table(int size) {
    buffers_table* new = (buffers_table*) calloc(1, sizeof(buffers_table));

    if(new != NULL) {
        new->buffers = (load_buffer**) calloc(size, sizeof(load_buffer*));

        if(new->buffers != NULL) {
            for(int i = 0; i < size; i++) {
                new->buffers[i] = create_load_buffer();
            }
        }
        new->cap = size;
    }

    return new;
}

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table) {
    if(buffers_table_is_full(buffers_table)) {
        printf("Buffers table is full\n");
        return;
    }

    load_buffer->buffers_table = buffers_table;
    buffers_table->buffers[buffers_table->size] = load_buffer;
    buffers_table->size++;

    return;

}

int buffers_table_is_full(buffers_table* buffers_table) {
    if(buffers_table->size == buffers_table->cap) {
        return 1;
    }

    return 0;
}

int buffers_table_is_empty(buffers_table* buffers_table) {
    if(buffers_table->size == 0) {
        return 1;
    }

    return 1;
}

void refresh_buffers_table(buffers_table* buffers_table) {
    for(int i = 0; i < buffers_table->size; i++) {
        if(buffers_table->buffers[i]->busy == 'y') {
            refresh_load_buffer(buffers_table->buffers[i]);
        }
    }
}

cpu* create_cpu() {
    cpu* new = (cpu*) calloc(1, sizeof(cpu));

    return new;
}

void next_clock(cpu* cpu) {
    cpu->clock++;

    return;
}

instruction_queue* create_instruction_queue(int size) {
    instruction_queue* new = (instruction_queue*) calloc(1, sizeof(instruction_queue));

    if(new != NULL) {
        new->instructions = (instruction**) calloc(size, sizeof(instruction*));
        new->cap = size;
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

instruction* instruction_queue_front(instruction_queue* instruction_queue) {
    return instruction_queue->instructions[0];
}

void remove_instruction_from_queue(instruction_queue* instruction_queue) {
    if(instruction_queue_is_empty(instruction_queue)) {
        printf("Queue is empty\n");
        return;
    }

    instruction* removed = instruction_queue->instructions[0];

    for(int i = 0; i < instruction_queue->size - 1; i++) {
        instruction_queue->instructions[i] = instruction_queue->instructions[i + 1];
    }

    instruction_queue->size--;

    return;
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

instruction* create_instruction(char* opcode, char* rs, char* rt, char* rd, register_pool* r_p) {
    instruction* new = (instruction*) calloc(1, sizeof(instruction));

    if(new != NULL) {
        for(int i = 0; i < r_p->size; i++) {
            register_* r = r_p->registers[i];

            if(strcmp(r->id, rs)) {
                new->rs = r;
            }

            if(strcmp(r->id, rd)) {
                new->rd = r;
            }

            if(strcmp(r->id, rt)) {
                new->rt = r;
            }
        }

        new->issued = -1;
        new->executed = -1;
        new->finished = -1;
    }

    return new;

}

void add_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value + instruction->rd->value;
}

void sub_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value - instruction->rd->value;
}

void mult_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value * instruction->rd->value;
}

void div_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value / instruction->rd->value;
}

void load_operation(instruction* instruction) {
    if(instruction == NULL) {
        printf("Null instruction");
        return;
    }

    instruction->rs->value = instruction->rt->value;
}

load_buffer* create_load_buffer() {
    load_buffer* new = (load_buffer*) calloc(1, sizeof(load_buffer));

    if(new != NULL) {
        new->busy = 'n';
    }

    return new;
}

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction) {
    load_buffer->op = instruction;
    load_buffer->target = instruction->rs;
    load_buffer->address = instruction->rt;
    load_buffer->busy = 'y';
    load_buffer->time = 2;

    instruction->pending_buffer = load_buffer;
    instruction->rs->l_b_fu = load_buffer;

    return;
}

void clear_load_buffer(load_buffer* load_buffer) {
    load_buffer->busy = 'n';
    load_buffer->address = NULL;
    load_buffer->op = NULL;
    load_buffer->target = NULL;

    return;
}


void refresh_load_buffer(load_buffer* load_buffer) {
    instruction* instruction = load_buffer->op;

    instruction->rs->l_b_fu = NULL;
}

register_pool* create_register_pool(int size) {
    register_pool* new = (register_pool*) calloc(1, sizeof(register_pool));

    if(new != NULL) {
        new->registers = (register_**) calloc(size, sizeof(register_*));

        if(new->registers == NULL) {
            return NULL;
        }

        new->size = size;
    }
}

register_* create_register(char* id) {
    register_* new = (register_*) calloc(1, sizeof(register_));

    if(new != NULL) {
        new->id = id;
    }

    return new;
}

void add_register_to_pool(register_pool* register_pool, register_* reg) {
    if(register_pool_is_full(register_pool)) {
        printf("Register pool is full\n");
        return;
    }

    register_pool->registers[register_pool->size] = reg;
    register_pool->size++;

    return;
}

int register_pool_is_full(register_pool* stations_table) {
    if(stations_table->size == stations_table->cap) {
        return 1;
    }

    return 0;
}

int register_pool_is_empty(register_pool* stations_table) {
    if(stations_table->size == 0) {
        return 1;
    }

    return 0;
}

reservation_station* create_reservation_station(char* name) {
    reservation_station* new = (reservation_station*) calloc(1, sizeof(reservation_station));

    if(new != NULL) {
        new->name = name;

        new->busy = 'n';
    }

    return new;
}

void add_instruction_to_reservation_station(reservation_station* reservation_station, instruction* instruction) {
    reservation_station->busy = 'y';
    reservation_station->op = instruction;
    
    if(strcmp(instruction->opcode, "add") || strcmp(instruction->opcode, "sub")) {
        reservation_station->time = 2;
    } else if(strcmp(instruction->opcode, "mult")) {
        reservation_station->time = 10;
    } else if(strcmp(instruction->opcode, "div")) {
        reservation_station->time = 40;
    }

    if(instruction->rs->r_s_fu == NULL || instruction->rs->l_b_fu == NULL) {
        instruction->rs->r_s_fu = reservation_station;
    }

    if(instruction->rt->r_s_fu == NULL || instruction->rt->l_b_fu == NULL) {
        reservation_station->vj = instruction->rt;
    } else {
        reservation_station->qj = instruction->rt;
    }

    if(instruction->rd->r_s_fu == NULL || instruction->rd->l_b_fu == NULL) {
        reservation_station->vk = instruction->rd;
    } else {
        reservation_station->qk = instruction->rd;
    }
    
    instruction->pending_station = reservation_station;

    return;
}

void refresh_reservation_station(reservation_station* reservation_station) {
    if(reservation_station->qj->r_s_fu == NULL) {
        reservation_station->vj = reservation_station->qj;
        reservation_station->qj = NULL;
    }

    if(reservation_station->qk->r_s_fu == NULL) {
        reservation_station->vk = reservation_station->qk;
        reservation_station->qk = NULL;
    }
}

void clear_reservation_station(reservation_station* reservation_station) {
    reservation_station->busy = 'n';
    reservation_station->op = NULL;
    reservation_station->qj = NULL;
    reservation_station->qk = NULL;
    reservation_station->vj = NULL;
    reservation_station->vk = NULL;

    return;
}

stations_table* create_stations_table(int add, int mult) {
    int size = add + mult;

    stations_table* st = (stations_table*) calloc(1, sizeof(stations_table));

    if(st == NULL) {
        printf("Failed to create stations table\n");
        return st;
    }

    st->size = size;
    st->stations = (reservation_station**) calloc(size, sizeof(reservation_station*));

    if(st == NULL) {
        printf("Failed to create array of reservation stations\n");
        return st;
    } 

    for(int i = 0; i < size; i++) {
        if(add > 0) {
            st->stations[i] = create_reservation_station("add");
            add--;
        } else {
            st->stations[i] = create_reservation_station("mult");
        }
    }

    return st;
}

void add_reservation_station(stations_table* stations_table, reservation_station* reservation_station) {
    if(stations_table_is_full(stations_table)) {
        printf("Stations table is full\n");
        return;
    }

    reservation_station->stations_table = stations_table;
    stations_table->stations[stations_table->size];
    stations_table->size++;

    return;
}

int stations_table_is_full(stations_table* stations_table) {
    if(stations_table->size == stations_table->cap) {
        return 1;
    }

    return 0;
}

int stations_table_is_empty(stations_table* stations_table) {
    if(stations_table->size == 0) {
        return 1;
    }

    return 0;
}

void refresh_stations_table(stations_table* stations_table) {
    for(int i = 0; i < stations_table->size; i++) {
        if(stations_table->stations[i]->busy == 'y') {
            refresh_reservation_station(stations_table->stations[i]);
        }
    }

    return;
}

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
    for(int i = 0; i < buffers_table->size; i++) {
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
}*/
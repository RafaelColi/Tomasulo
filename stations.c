#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stations.h"

reservation_station* create_reservation_station(char* name) {
    reservation_station* new = (reservation_station*) calloc(1, sizeof(reservation_station));

    if(new == NULL) {
        printf("Failed to allocate memory for reservation station\n");
        return NULL;
    }

    new->name = name;
    new->busy = 'n';

    return new;
}

void refresh_reservation_station(reservation_station* reservation_station, common_data_bus* cdb) {
    if(register_is_available(reservation_station->qj, cdb)) {
        reservation_station->vj = reservation_station->qj;
        reservation_station->qj = NULL;
    }

    if(register_is_available(reservation_station->qk, cdb)) {
        reservation_station->vk = reservation_station->qk;
        reservation_station->qk = NULL;
    }

    return;
}

void clear_reservation_station(reservation_station* reservation_station, common_data_bus* cdb) {
    clear_common_data_bus(reservation_station->instruction, cdb);

    reservation_station->instruction = NULL;
    reservation_station->busy = 'n';
    reservation_station->qj = NULL;
    reservation_station->qk = NULL;
    reservation_station->vj = NULL;
    reservation_station->vk = NULL;

    return;
}

load_buffer* create_load_buffer() {
    load_buffer* new = (load_buffer*) calloc(1, sizeof(load_buffer));

    if(new != NULL) {
        new->busy = 'n';
    }

    return new;
}

void clear_load_buffer(load_buffer* load_buffer, common_data_bus* cdb) {
    clear_common_data_bus(load_buffer->instruction, cdb);

    load_buffer->instruction = NULL;
    load_buffer->busy = 'n';
    load_buffer->address = NULL;
    load_buffer->target = NULL;

    return;
}

void add_instruction_to_reservation_station(reservation_station* reservation_station, instruction* instruction, common_data_bus* cdb) {
    reservation_station->busy = 'y';
    
    if(!strcmp(instruction->opcode, "add") || !strcmp(instruction->opcode, "sub")) {
        reservation_station->time = 2;
    } else if(!strcmp(instruction->opcode, "mult")) {
        reservation_station->time = 10;
    } else if(!strcmp(instruction->opcode, "div")) {
        reservation_station->time = 40;
    }

    if(register_is_available(instruction->rs, cdb)) {
        write_cdb(instruction->rs, cdb, instruction);
    }  

    if(register_is_available(instruction->rt, cdb)) {
        reservation_station->vj = instruction->rt;
    } else {
        reservation_station->qj = instruction->rt;
    }

    if(register_is_available(instruction->rd, cdb)) {
        reservation_station->vk = instruction->rd;
    } else {
        reservation_station->qk = instruction->rd;
    }

    reservation_station->instruction = instruction;

    return;
}

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction, common_data_bus* cdb) {

    if(register_is_available(instruction->rs, cdb)) {
        write_cdb(instruction->rs, cdb, instruction);
    }  

    load_buffer->target = instruction->rs;
    load_buffer->address = instruction->rt;
    load_buffer->busy = 'y';
    load_buffer->time = 2;

    return;
}

stations_table* create_stations_table(int add, int mult) {
    int size = add + mult;

    stations_table* st = (stations_table*) calloc(1, sizeof(stations_table));

    if(st == NULL) {
        printf("Failed to allocate memory for stations table\n");
        return NULL;
    }

    
    st->stations = (reservation_station**) calloc(size, sizeof(reservation_station*));

    if(st->stations == NULL) {
        printf("Failed to allocate memory for reservation stations array\n");
        return NULL;
    } 

    st->cap = size;

    for(int i = 0; i < st->cap; i++) {
        if(add > 0) {
            add_reservation_station(st, create_reservation_station("add"));
            add--;
        } else {
            add_reservation_station(st, create_reservation_station("mult"));
        }
    }

    return st;
}

void add_reservation_station(stations_table* stations_table, reservation_station* reservation_station) {
    if(stations_table == NULL) {
        printf("NULL pointer to stations table\nadd_reservation_station() cancelled\n");
        return;
    }

    if(reservation_station == NULL) {
        printf("NULL pointer to reservation station\nadd_reservation_station() cancelled\n");
        return;
    }
    
    if(stations_table_is_full(stations_table)) {
        printf("Stations table is full\n");
        return;
    }

    stations_table->stations[stations_table->size] = reservation_station;
    stations_table->size++;

    return;
}

int stations_table_is_full(stations_table* stations_table) {
    if(stations_table == NULL) {
        printf("NULL pointer to stations table\nstations_table_is_full() cancelled\n");
        return -1;
    }
    
    if(stations_table->size == stations_table->cap) {
        return 1;
    }

    return 0;
}

int stations_table_is_empty(stations_table* stations_table) {
    if(stations_table == NULL) {
        printf("NULL pointer to stations table\nstations_table_is_empty() cancelled\n");
        return -1;
    }
    
    if(stations_table->size == 0) {
        return 1;
    }

    return 0;
}

void refresh_stations_table(stations_table* stations_table, common_data_bus* cdb) {
    if(stations_table == NULL) {
        printf("NULL pointer to stations table\nrefresh_stations_table() cancelled\n");
        return;
    }

    if(cdb == NULL) {
        printf("NULL pointer to common data bus\nrefresh_stations_table() cancelled\n");
        return;
    }

    for(int i = 0; i < stations_table->size; i++) {
        if(stations_table->stations[i]->busy == 'y') {
            refresh_reservation_station(stations_table->stations[i], cdb);
        }
    }

    return;
}

buffers_table* create_buffers_table(int size) {
    buffers_table* new = (buffers_table*) calloc(1, sizeof(buffers_table));

    if(new == NULL) {
        printf("Failed to allocate memory for buffers table\n");
        return NULL;
    }

    new->buffers = (load_buffer**) calloc(size, sizeof(load_buffer*));

    if(new->buffers == NULL) {
        printf("Failed to allocate memory for load buffers array\n");
        return NULL;
    }

    new->cap = size;

    for(int i = 0; i < new->cap; i++) {
        new->buffers[i] = create_load_buffer();
    }

    return new;
}

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table) {
    if(load_buffer == NULL) {
        printf("NULL pointer to load buffer\nadd_buffers_to_buffers_table() cancelled\n");
        return;
    }

    if(buffers_table == NULL) {
        printf("NULL pointer to buffers table\nadd_buffers_to_buffers_table() cancelled\n");
        return;
    }
    
    
    if(buffers_table_is_full(buffers_table)) {
        return;
    }

    buffers_table->buffers[buffers_table->size] = load_buffer;
    buffers_table->size++;

    return;

}

int buffers_table_is_full(buffers_table* buffers_table) {
    if(buffers_table == NULL) {
        printf("NULL pointer to buffers table\nbuffers_table_is_full() cancelled\n");
        return -1;
    }
    
    if(buffers_table->size == buffers_table->cap) {
        printf("Buffers table is full\n");
        return 1;
    }

    return 0;
}

int buffers_table_is_empty(buffers_table* buffers_table) {
    if(buffers_table == NULL) {
        printf("NULL pointer to buffers table\nbuffers_table_is_full() cancelled\n");
        return -1;
    }
    
    if(buffers_table->size == 0) {
        printf("Buffers table is empty\n");
        return 1;
    }

    return 0;
}

unit* create_unit(reg* reg) {
    if(reg == NULL) {
        printf("NULL pointer to register\ncreate_unit() cancelled\n");
        return NULL;
    }

    unit* new = (unit*) calloc(1, sizeof(unit));

    if(new == NULL) {
        printf("Failed to allocate memory for unit\n");
        return NULL;
    }

    new->reg = reg;

    return new;
}

common_data_bus* create_common_data_bus(registers_pool* reg_pool) {
    if(reg_pool == NULL) {
        printf("NULL pointer to registers pool\ncreate_common_data_bus() cancelled\n");
        return NULL;
    }
    
    int size = reg_pool->size;
    
    common_data_bus* new = (common_data_bus*) calloc(1, sizeof(common_data_bus));

    if(new == NULL) {
        printf("Failed to allocate memory for common data bus\n");
        return NULL;
    }

    new->units = (unit**) calloc(size, sizeof(unit*));

    if(new->units == NULL) {
        printf("Failed to allocate memory for units array\n");
        return NULL;
    }

    for(int i = 0; i < size; i++) {
        new->units[i] = create_unit(reg_pool->registers[i]);
    }

    new->cap = size;

    return new;
}

int register_is_available(reg* reg, common_data_bus* cdb) {
    if(reg == NULL) {
        printf("NULL pointer to register\nregister_is_available() cancelled\n");
        return -1;
    }

    if(cdb == NULL) {
        printf("NULL pointer to common data bus\nregister_is_available() cancelled\n");
        return -1;
    }
    
    unit* unit;

    for(int i = 0; i < cdb->size; i++) {
        unit = cdb->units[i];

        if(unit->reg == reg) {
            if(unit->instruction == NULL) {
                return 1;
            } else {
                return 0;
            }
        }
    }

    return 0;
}

void write_cdb(reg* reg, common_data_bus* cdb, instruction* instruction) {
    if(reg == NULL) {
        printf("NULL pointer to register\nwrite_cdb() cancelled\n");
        return;
    }

    if(cdb == NULL) {
        printf("NULL pointer to common data bus\nwrite_cdb() cancelled\n");
        return;
    }

    if(instruction == NULL) {
        printf("NULL pointer to instruction\nwrite_cdb() cancelled\n");
        return;
    }
    
    unit* unit;

    for(int i = 0; i < cdb->size; i++) {
        unit = cdb->units[i];

        if(unit->reg == reg) {
            unit->instruction = instruction;
        }
    }

    return;
}

void clear_common_data_bus(instruction* instruction, common_data_bus* cdb) {
    if(instruction == NULL) {
        printf("NULL pointer to instruction\nclear_common_data_bus() cancelled\n");
        return;
    }

    if(cdb == NULL) {
        printf("NULL pointer to common data bus\nclear_common_data_bus() cancelled\n");
        return;
    }
    
    unit* unit;
    
    for(int i = 0; i < cdb->size; i++) {
        unit = cdb->units[i];

        if(unit->instruction == instruction) {
            unit->instruction = NULL;
        }
    }
}
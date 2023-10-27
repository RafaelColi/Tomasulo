#ifndef STATIONS_H
#define STATIONS_H
#include "instructions.h"
#include "tables.h"

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

typedef struct load_buffer {
    char busy;
    register_* target;
    register_* address;
    int time;
    instruction* op;
    buffers_table* buffers_table;

} load_buffer;

reservation_station* create_reservation_station(char* name);

void add_instruction_to_reservation_station(reservation_station* reservation_station, instruction* instruction);

void refresh_reservation_station(reservation_station* reservation_station);

void clear_reservation_station(reservation_station* reservation_station);

load_buffer* create_load_buffer();

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction);

void clear_load_buffer(load_buffer* load_buffer);

#endif
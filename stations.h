#ifndef STATIONS_H
#define STATIONS_H
#include "instruction.h"
#include "register.h"

typedef struct reservation_station {
    int time;
    char* name;
    char busy;
    instruction* instruction;
    reg* vj;
    reg* vk;
    reg* qj;
    reg* qk;
} reservation_station;

typedef struct load_buffer {
    char busy;
    reg* target;
    reg* address;
    instruction* instruction;
    int time;
} load_buffer;

typedef struct buffers_table {
    load_buffer** buffers;
    int size;
    int cap;
} buffers_table;

typedef struct stations_table {
    reservation_station** stations;
    int size;
    int cap;
} stations_table;

typedef struct unit {
    instruction* instruction;
    reg* reg;
} unit;

typedef struct common_data_bus {
    unit** units;
    int size;
    int cap;
} common_data_bus;

reservation_station* create_reservation_station(char* name);

void refresh_reservation_station(reservation_station* reservation_station, common_data_bus* cdb);

void clear_reservation_station(reservation_station* reservation_station, common_data_bus* cdb);

load_buffer* create_load_buffer();

void clear_load_buffer(load_buffer* load_buffer, common_data_bus* cdb);

void add_instruction_to_reservation_station(reservation_station* reservation_station, instruction* instruction, common_data_bus* cdb);

void add_instruction_to_load_buffer(load_buffer* load_buffer, instruction* instruction, common_data_bus* cdb);

buffers_table* create_buffers_table(int size);

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table);

int buffers_table_is_full(buffers_table* buffers_table);

int buffers_table_is_empty(buffers_table* buffers_table);

void refresh_buffers_table(buffers_table* buffers_table);

stations_table* create_stations_table(int add, int mult);

void add_reservation_station(stations_table* stations_table, reservation_station* reservation_station);

int stations_table_is_full(stations_table* stations_table);

int stations_table_is_empty(stations_table* stations_table);

void refresh_stations_table(stations_table* stations_table, common_data_bus* cdb);

unit* create_unit(reg* reg);

common_data_bus* create_common_data_bus(registers_pool* reg_pool);

int register_is_available(reg* reg, common_data_bus* cdb);

void write_cdb(reg* reg, common_data_bus* cdb, instruction* instruction);

void clear_common_data_bus(instruction* instruction, common_data_bus* cdb);

#endif
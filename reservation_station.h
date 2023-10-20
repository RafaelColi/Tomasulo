#ifndef RESERVATION_STATION.H
#define RESERVATION_STATION.H
#include "instruction.h"
#include "register.h"
#include "stations_table.h"

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
#endif
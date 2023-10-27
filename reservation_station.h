#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H
#include "instruction.h"
#include "register.h"
#include "stations_table.h"

typedef struct reservation_station reservation_station;

reservation_station* create_reservation_station(char* name);

void add_instruction_to_reservation_station(reservation_station* reservation_station, instruction* instruction);

void refresh_reservation_station(reservation_station* reservation_station);

void clear_reservation_station(reservation_station* reservation_station);
#endif
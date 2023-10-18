#ifndef STATIONS_TABLE.H
#define STATIONS_TABLE.H
#include "reservation_station.h"

typedef struct stations_table {
    reservation_station** stations;
    int size;
    int cap;
} stations_table;

stations_table* create_stations_table(int add, int mult);

#endif
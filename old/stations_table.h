#ifndef STATIONS_TABLE_H
#define STATIONS_TABLE_H
#include "reservation_station.h"

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

#endif
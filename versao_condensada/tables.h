#ifndef TABLES_H
#define TABLES_H
#include "stations.h"

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

buffers_table* create_buffers_table(int size);

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table);

int buffers_table_is_full(buffers_table* buffers_table);

int buffers_table_is_empty(buffers_table* buffers_table);

void refresh_buffers_table(buffers_table* buffers_table);

stations_table* create_stations_table(int add, int mult);

void add_reservation_station(stations_table* stations_table, reservation_station* reservation_station);

int stations_table_is_full(stations_table* stations_table);

int stations_table_is_empty(stations_table* stations_table);

void refresh_stations_table(stations_table* stations_table);

#endif
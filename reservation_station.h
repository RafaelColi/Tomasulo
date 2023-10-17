#ifndef RESERVATION_STATION.H
#define RESERVATION_STATION.H

typedef struct load_buffer load_buffer;

typedef struct buffers_table buffers_table;

typedef struct reservation_station reservation_station;

typedef struct stations_table stations_table;

stations_table* create_stations_table(int add, int mult);

#endif
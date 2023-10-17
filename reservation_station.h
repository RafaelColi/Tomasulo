#ifndef RESERVATION_STATION.H
#define RESERVATION_STATION.H

typedef struct load_buffer {
    char busy;
    char* address;
} load_buffer;

typedef struct buffers_table {
    load_buffer* buffers;
    int tam;
} buffers_table;

typedef struct reservation_station {
    int time;
    char name;
    char busy;
    char* op;
    char* vj;
    char* vk;
    char* qj;
    char* qk;

} reservation_station;

typedef struct stations_table {
    reservation_station* stations;
    int tam;
} stations_table;

stations_table* create_stations_table(int add, int mult);

#endif
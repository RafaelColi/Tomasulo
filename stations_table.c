#include <stdlib.h>
#include <stdio.h>
#include "stations_table.h"

typedef struct stations_table {
    reservation_station** stations;
    int size;
    int cap;
} stations_table;

stations_table* create_stations_table(int add, int mult) {
    int size = add + mult;

    stations_table* st = (stations_table*) calloc(1, sizeof(stations_table));

    if(st == NULL) {
        printf("Failed to create stations table\n");
        return st;
    }

    st->size = size;
    st->stations = (reservation_station**) calloc(size, sizeof(reservation_station*));

    if(st == NULL) {
        printf("Failed to create array of reservation stations\n");
        return st;
    } 

    for(int i = 0; i < size; i++) {
        if(add > 0) {
            st->stations[i] = create_reservation_station('add');
            add--;
        } else {
            st->stations[i] = create_reservation_station('mult');
        }
    }

    return st;
}

void add_reservation_station(stations_table* stations_table, reservation_station* reservation_station) {
    if(stations_table_is_full(stations_table)) {
        printf("Stations table is full\n");
        return;
    }

    reservation_station->stations_table = stations_table;
    stations_table->stations[stations_table->size];
    stations_table->size++;

    return;
}

int stations_table_is_full(stations_table* stations_table) {
    if(stations_table->size == stations_table->cap) {
        return 1;
    }

    return 0;
}

int stations_table_is_empty(stations_table* stations_table) {
    if(stations_table->size == 0) {
        return 1;
    }

    return 0;
}

void refresh_stations_table(stations_table* stations_table) {
    for(int i = 0; i < stations_table->size; i++) {
        if(stations_table->stations[i]->busy == 'y') {
            refresh_reservation_station(stations_table->stations[i]);
        }
    }

    return;
}
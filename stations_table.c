#include <stdlib.h>
#include <stdio.h>
#include "stations_table.h"

stations_table* create_stations_table(int add, int mult) {
    int size = add + mult;

    stations_table* st = (stations_table*) calloc(1, sizeof(stations_table));

    if(st == NULL) {
        printf("Failed to create stations table");
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
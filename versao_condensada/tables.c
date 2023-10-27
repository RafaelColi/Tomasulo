#include <stdlib.h>
#include <stdio.h>
#include "tables.h"

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

buffers_table* create_buffers_table(int size) {
    buffers_table* new = (buffers_table*) calloc(1, sizeof(buffers_table));

    if(new != NULL) {
        new->buffers = (load_buffer**) calloc(size, sizeof(load_buffer*));

        if(new->buffers != NULL) {
            for(int i = 0; i < size; i++) {
                new->buffers[i] = create_load_buffer();
            }
        }
        new->cap = size;
    }

    return new;
}

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table) {
    if(buffers_table_is_full(buffers_table)) {
        printf("Buffers table is full\n");
        return;
    }

    load_buffer->buffers_table = buffers_table;
    buffers_table->buffers[buffers_table->size] = load_buffer;
    buffers_table->size++;

    return;

}

int buffers_table_is_full(buffers_table* buffers_table) {
    if(buffers_table->size == buffers_table->cap) {
        return 1;
    }

    return 0;
}

int buffers_table_is_empty(buffers_table* buffers_table) {
    if(buffers_table->size == 0) {
        return 1;
    }

    return 1;
}

void refresh_buffers_table(buffers_table* buffers_table) {
    for(int i = 0; i < buffers_table->size; i++) {
        if(buffers_table->buffers[i]->busy == 'y') {
            refresh_load_buffer(buffers_table->buffers[i]);
        }
    }
}
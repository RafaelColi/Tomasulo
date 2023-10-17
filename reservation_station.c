#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"

stations_table* create_stations_table(int add, int mult) {
    int tam = add + mult;

    stations_table* st = (stations_table*) calloc(1, sizeof(reservation_station));

    if(st == NULL) {
        printf("Failed to create stations table");
        return st;
    }

    st->tam = tam;
    st->stations = (reservation_station*) calloc(tam, sizeof(reservation_station));

    if(st == NULL) {
        printf("Failed to create array of reservation stations\n");
        return st;
    } 

    for(int i = 0; i < tam; i++) {
        if(add > 0) {
            st->stations[i].name = 'a';
            add--;
        } else {
            st->stations[i].name = 'm';
        }

        st->stations[i].busy = 'n';
        st->stations[i].op = (char*) calloc(6, sizeof(char));
        st->stations[i].vj = (char*) calloc(6, sizeof(char));
        st->stations[i].vk = (char*) calloc(6, sizeof(char));
        st->stations[i].qj = (char*) calloc(6, sizeof(char));
        st->stations[i].qk = (char*) calloc(6, sizeof(char));
    }

    return st;
}
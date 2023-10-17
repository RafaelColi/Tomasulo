#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char busy;
    char* address;
} load_buffer;

typedef struct {
    load_buffer* buffers;
    int tam;
} buffers_table;

typedef struct {
    int time;
    char name;
    char busy;
    char* op;
    char* vj;
    char* vk;
    char* qj;
    char* qk;

} reservation_station;

typedef struct {
    reservation_station* stations;
    int tam;
} stations_table;

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
#ifndef RESERVATION_STATION.H
#define RESERVATION_STATION.H
#include "functional_unit.h"

typedef struct reservation_station {
    int time;
    char* name;
    char busy;
    char* op;
    char* vj;
    char* vk;
    char* qj;
    char* qk;

} reservation_station;

reservation_station* create_reservation_station(char* name);

#endif
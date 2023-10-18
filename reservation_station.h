#ifndef RESERVATION_STATION.H
#define RESERVATION_STATION.H
#include "instruction.h"
#include "functional_unit.h"
#include "register.h"

typedef struct reservation_station {
    int time;
    char* name;
    char busy;
    instruction* op;
    register_* vj;
    register_* vk;
    register_* qj;
    register_* qk;

} reservation_station;

reservation_station* create_reservation_station(char* name);

#endif
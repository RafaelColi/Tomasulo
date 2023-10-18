#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"

reservation_station* create_reservation_station(char* name) {
    reservation_station* new = (reservation_station*) calloc(1, sizeof(reservation_station));

    if(new != NULL) {
        new->name = name;

        new->busy = 'n';
    }

    return new;
}

void add_instruction_to_reservation_station(reservation_station* reservation_station, instruction* instruction) {
    reservation_station->busy = 'y';
    reservation_station->op = instruction;
    
    if(instruction->rs->fu == NULL) {
        instruction->rs->fu = reservation_station;
    }

    if(instruction->rt->fu == NULL) {
        reservation_station->vj = instruction->rt;
    } else {
        reservation_station->qj = instruction->rt;
    }

    if(instruction->rd->fu == NULL) {
        reservation_station->vk = instruction->rd;
    } else {
        reservation_station->qk = instruction->rd;
    }

    return;
}
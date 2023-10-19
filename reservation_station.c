#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"
#include <string.h>

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
    
    if(strcmp(instruction->opcode, "add") || strcmp(instruction->opcode, "sub")) {
        reservation_station->time = 2;
    } else if(strcmp(instruction->opcode, "mult")) {
        reservation_station->time = 10;
    } else if(strcmp(instruction->opcode, "div")) {
        reservation_station->time = 40;
    }

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

    instruction->pending_station = reservation_station;

    return;
}

void refresh_reservation_station(reservation_station* reservation_station) {
    if(reservation_station->qj->fu == NULL) {
        reservation_station->vj = reservation_station->qj;
        reservation_station->qj = NULL;
    }

    if(reservation_station->qk->fu == NULL) {
        reservation_station->vk = reservation_station->qk;
        reservation_station->qk = NULL;
    }
}
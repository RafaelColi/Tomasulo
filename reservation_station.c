#include <stdlib.h>
#include <stdio.h>
#include "reservation_station.h"

reservation_station* create_reservation_station(char* name) {
    reservation_station* new = (reservation_station*) calloc(1, sizeof(reservation_station));

    if(new != NULL) {
        new->name = name;

        new->busy = 'n';
        new->op = (char*) calloc(6, sizeof(char));
        new->vj = (char*) calloc(6, sizeof(char));
        new->vk = (char*) calloc(6, sizeof(char));
        new->qj = (char*) calloc(6, sizeof(char));
        new->qk = (char*) calloc(6, sizeof(char));
    }

    return new;
}
#ifndef REGISTER.H
#define REGISTER.H
#include "reservation_station.h"

typedef struct register_ {
    double value;
    reservation_station* fu;
} register_;

typedef struct register_pool {
    register_** registers;
    int size;
    int cap;
} register_pool;

register_pool* create_register_pool(int size);

#endif
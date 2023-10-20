#ifndef REGISTER.H
#define REGISTER.H
#include "reservation_station.h"
#include "load_buffer.h"

typedef struct register_ {
    double value;
    reservation_station* r_s_fu;
    load_buffer* l_b_fu;
} register_;

typedef struct register_pool {
    register_** registers;
    int size;
    int cap;
} register_pool;

register_pool* create_register_pool(int size);

#endif
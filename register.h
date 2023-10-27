#ifndef REGISTER_H
#define REGISTER_H
#include "reservation_station.h"
#include "load_buffer.h"

typedef struct register_ register_;

typedef struct register_pool register_pool;

register_* create_register(char* id);

void add_register_to_pool(register_pool* register_pool, register_* reg);

register_pool* create_register_pool(int size);

#endif
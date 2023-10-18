#ifndef BUFFER_TABLE.H
#define BUFFER_TABLE.H
#include "load_buffer.h"

typedef struct buffers_table {
    load_buffer** buffers;
    int size;
    int cap;
} buffers_table;

#endif
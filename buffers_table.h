#ifndef BUFFER_TABLE.H
#define BUFFER_TABLE.H
#include "load_buffer.h"

typedef struct buffers_table {
    load_buffer** buffers;
    int size;
    int cap;
} buffers_table;

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table);

int buffers_table_is_full(buffers_table* buffers_table);

int buffers_table_is_empty(buffers_table* buffers_table);

void refresh_buffers_table(buffers_table* buffers_table);

#endif
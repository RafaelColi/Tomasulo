#ifndef BUFFERS_TABLE_H
#define BUFFERS_TABLE_H
#include "load_buffer.h"

typedef struct buffers_table buffers_table;

buffers_table* create_buffers_table(int size);

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table);

int buffers_table_is_full(buffers_table* buffers_table);

int buffers_table_is_empty(buffers_table* buffers_table);

void refresh_buffers_table(buffers_table* buffers_table);

#endif
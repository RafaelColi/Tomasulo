#include <stdlib.h>
#include <stdio.h>
#include "buffers_table.h"

typedef struct buffers_table {
    load_buffer** buffers;
    int size;
    int cap;
} buffers_table;

buffers_table* create_buffers_table(int size) {
    buffers_table* new = (buffers_table*) calloc(1, sizeof(buffers_table));

    if(new != NULL) {
        new->buffers = (load_buffer**) calloc(size, sizeof(load_buffer*));

        if(new->buffers != NULL) {
            for(int i = 0; i < size; i++) {
                new->buffers[i] = create_load_buffer();
            }
        }
        new->cap = size;
    }

    return new;
}

void add_buffers_to_buffers_table(load_buffer* load_buffer, buffers_table* buffers_table) {
    if(buffers_table_is_full(buffers_table)) {
        printf("Buffers table is full\n");
        return;
    }

    load_buffer->buffers_table = buffers_table;
    buffers_table->buffers[buffers_table->size] = load_buffer;
    buffers_table->size++;

    return;

}

int buffers_table_is_full(buffers_table* buffers_table) {
    if(buffers_table->size == buffers_table->cap) {
        return 1;
    }

    return 0;
}

int buffers_table_is_empty(buffers_table* buffers_table) {
    if(buffers_table->size == 0) {
        return 1;
    }

    return 1;
}

void refresh_buffers_table(buffers_table* buffers_table) {
    for(int i = 0; i < buffers_table->size; i++) {
        if(buffers_table->buffers[i]->busy == 'y') {
            refresh_load_buffer(buffers_table->buffers[i]);
        }
    }
}
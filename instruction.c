#include <stdlib.h>
#include <stdio.h>

typedef struct register_ {
    char name[2];
    double value;
} register_;

typedef struct {
    char* opcode;
    register_* rs;
    register_* rt;
    register_* rd;

} instruction_r;

void load() {

}

void add(instruction_r* i) {
    if(i == NULL) {
        printf("Null instruction");
        return;
    }

    i->rs->value = i->rt->value + i->rd->value;
}

void sub(instruction_r* i) {
    if(i == NULL) {
        printf("Null instruction");
        return;
    }

    i->rs->value = i->rt->value - i->rd->value;
}

void mult(instruction_r* i) {
    if(i == NULL) {
        printf("Null instruction");
        return;
    }

    i->rs->value = i->rt->value * i->rd->value;
}

void div(instruction_r* i) {
    if(i == NULL) {
        printf("Null instruction");
        return;
    }

    i->rs->value = i->rt->value / i->rd->value;
}



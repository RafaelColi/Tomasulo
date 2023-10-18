#ifndef INSTRUCTION.H
#define INSTRUCTION.H
#include "register.h"

typedef struct {
    char* opcode;
    register_* rs;
    register_* rt;
    register_* rd;
    reservation_station* pending;

} instruction;

#endif
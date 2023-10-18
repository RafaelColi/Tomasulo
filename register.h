#ifndef REGISTER.H
#define REGISTER.H

typedef struct register_ {
    char name[2];
    double value;
    f_u* fu;
} register_;

#endif
#ifndef RANDOM_H
#define RANDOM_H

#include <math.h>

static int seed = 10;

inline 
int myrandom(){
    return abs(100000*sin(seed+=42));
}

#endif

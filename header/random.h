#ifndef RANDOM_H
#define RANDOM_H

#include <math.h>

static int seed = 10;

int myrandom(){
    return abs(100000*sin(seed+=42));
    return rand();
}


#endif

#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>

using namespace std;

long seed;

void enterseed(){
    cout << "Enter Seed: " << flush;
    cin >> seed;
}

long long myrandom(){
    //tbd
    return rand();
}

#endif

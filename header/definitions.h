#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <array>

#define HIGH 60
#define WIDTH 60
#define NUMBEROFLOWWALLS 25
#define NUMBEROFPOWERUPS 20
#define PACMANDETECTIONRANGE 10
#define NUMBEROFENEMYS 10
#define SHOTRANGE 10

//colorIDs
#define WALL 1
#define LOWERWALL 0
#define ROAD 3
#define ROADWITHCOIN 2
#define POWERUP 4

//"textures"
#define ENEMY "\033[48;5;7;38;5;9m۩ "

template<typename T> using fieldtyp = std::array<std::array<T, HIGH>, WIDTH>;

#endif

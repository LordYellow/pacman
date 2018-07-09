#ifndef DRAW_H
#define DRAW_H

#include "definitions.h"
#include <array>

using namespace std;

void draw(uint8_t x, uint8_t y, string stuffToDraw){
    cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(y+1) << ";" << to_string(2*x+1) << "H" << stuffToDraw << flush << "\033[48;5;8;38;5;4m" << "\033[" << to_string(HIGH+1) << ";" << "0" << "H" << "\033[0m";
}

void drawWithTexture(uint8_t x, uint8_t y, array<string, 8> *colors, uint8_t colorID){
    draw(x, y, (*colors)[colorID]);
}

void drawWholeField(fieldtyp<uint8_t> *field, array<string, 8> *colors){
     for(uint8_t y = 0; y < HIGH; y++){
        for(uint8_t x = 0; x < WIDTH; x++){
            drawWithTexture(x, y, colors, (*field)[y][x]);
        }
    }
}

void setcolors(array<string, 8> *colors){
    (*colors)[WALL] = "\033[48;5;236m  ";
    (*colors)[LOWERWALL] = "\033[48;5;244m  ";
    (*colors)[ROAD] = "\033[48;5;7m  ";
    (*colors)[ROADWITHCOIN] = "\033[48;5;7;38;5;2m$ ";
    (*colors)[POWERUP] = "\033[48;5;7;38;5;5m⏻ ";
}

#endif

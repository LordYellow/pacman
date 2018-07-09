#ifndef SHOT_H
#define SHOT_H

#include <vector>
#include <math.h>
#include "definitions.h"
#include "draw.h"
#include <array>

using namespace std;

class shot{
public:
    shot(uint8_t y, uint8_t x, uint8_t targetY, uint8_t targetX, array<string, 8> *thecolors);
    
    fieldtyp<uint8_t> *field;
    bool viableShot = true;
    uint8_t y, x, targetY, targetX, baseDelay = 5, delayCounter = 0, lastfield = ROAD;
    array<string, 8> *colors;
    
    void move();
};

shot::shot(uint8_t y, uint8_t x, uint8_t targetY, uint8_t targetX, array<string, 8> *thecolors){
    this->y = y;
    this->x = x;
    this->targetY = targetY;
    this->targetX = targetX;
    this->colors = thecolors;
}

void shot::move(){ //will rewrite it tomorrow 
    if(this->delayCounter == this->baseDelay){
        this->delayCounter = 0;
        drawWithTexture(x, y, this->colors, (*this->field)[y][x]);
        this->x-= (this->x-this->targetX)/sqrt(pow(this->y-this->targetY, 2) + pow(this->x-this->targetX, 2));
        this->y-= (this->y-this->targetY)/sqrt(pow(this->y-this->targetY, 2) + pow(this->x-this->targetX, 2));
        if((*this->field)[y][x] == WALL){this->viableShot = false; return;}
        draw(x, y, "\033[48;5;13m* ");
    }else{
        this->delayCounter++;
    }
}

#endif 

#ifndef SHOT_H
#define SHOT_H

#include <vector>
#include <math.h>
#include "field.h"
#include "definitions.h"

using namespace std;

class shot{
public:
    shot(uint8_t y, uint8_t x, uint8_t targetY, uint8_t targetX);
    
    static field *Field;
    bool viableShot = true;
    uint8_t y, x, targetY, targetX, baseDelay = 5, delayCounter = 0, lastfield = ROAD;
    double unitVectorX, unitVectorY;
    
    bool move();
};

shot::shot(uint8_t y, uint8_t x, uint8_t targetY, uint8_t targetX){
    this->y = y;
    this->x = x;
    this->targetY = targetY;
    this->targetX = targetX;
    this->unitVectorY = (this->targetY-this->y)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2));
    this->unitVectorX = (this->targetX-this->x)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2));
    this->y += this->unitVectorY;
    this->x += this->unitVectorX;
    this->lastfield = Field->getFieldValue(this->y, this->x);
}

bool shot::move(){
    if(this->delayCounter == this->baseDelay){
        this->delayCounter = 0;
        
        Field->changeFieldValue(this->y, this->x, this->lastfield);
        this->y += this->unitVectorY;
        this->x += this->unitVectorX;
        this->lastfield = Field->getFieldValue(this->y, this->x);
        if(this->lastfield == SHOT){this->lastfield = ROAD; this->viableShot = false; return false;}
        if(this->lastfield == WALL || this->lastfield == ENEMY){this->viableShot = false; return false;}
        if(this->lastfield == PACMAN){return true;}
        Field->changeFieldValue(this->y, this->x, SHOT);
    }else{
        this->delayCounter++;
    }
    return false;
}

#endif 

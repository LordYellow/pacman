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
    shot(uint8_t y, uint8_t x, uint8_t targetY, uint8_t targetX, array<string, 8> *thecolors,fieldtyp<uint8_t> *thefield);
    
    fieldtyp<uint8_t> *field;
    bool viableShot = true;
    uint8_t y, x;
    uint8_t targetY, targetX, baseDelay = 5, delayCounter = 0, lastfield = ROAD;
    array<string, 8> *colors;
    vector<array<uint8_t, 2>> pointVector;
    
    void move();
    
    void getShotFields();
};

shot::shot(uint8_t y, uint8_t x, uint8_t targetY, uint8_t targetX, array<string, 8> *thecolors, fieldtyp<uint8_t> *thefield){
    this->y = y;
    this->x = x;
    this->targetY = targetY;
    this->targetX = targetX;
    this->colors = thecolors;
    this->getShotFields();
    this->field = thefield;
}

/*
void shot::getShotFields(){
    double unitVectorY = (this->targetY-this->y)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2)), unitVectorX = (this->targetX-this->x)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2));
    for(uint8_t i = 0;; i++){
        if(round(this->y + unitVectorY*i) == this->targetY && round(this->x + unitVectorX*i) == this->targetX) break;
        this->pointVector.push_back({(uint8_t)round(this->y + unitVectorY*i), (uint8_t)round(this->x + unitVectorX*i)});
    }
}
*/

void shot::getShotFields(){
    double unitVectorY = (this->targetY-this->y)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2)), unitVectorX = (this->targetX-this->x)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2));
    for(uint8_t i = 0; i < SHOTRANGE; i++){
        this->pointVector.push_back({(uint8_t)round(this->y + unitVectorY*i), (uint8_t)round(this->x + unitVectorX*i)});
    }
}


void shot::move(){ //will rewrite it tomorrow 
    if(this->delayCounter == this->baseDelay){
        this->delayCounter = 0;
        drawWithTexture(this->pointVector[0][1], this->pointVector[0][0], this->colors, (*this->field)[this->pointVector[0][0]][this->pointVector[0][1]]); // for some reason this will cause a segmentation fault
        pointVector.erase(pointVector.begin());
        if((*this->field)[this->pointVector[0][1]][this->pointVector[0][0]] == WALL || this->y > HIGH || this->x > WIDTH || pointVector.size() == 0){this->viableShot = false; return;}
        draw(this->pointVector[0][1], this->pointVector[0][0], "\033[48;5;13m* ");
    }else{
        this->delayCounter++;
    }
}

#endif 

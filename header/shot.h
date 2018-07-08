#ifndef SHOT_H
#define SHOT_H

#include <vector>
#include "point.h"
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
    vector<point> pointVector;
    
    void isShotViable();
    
    bool move();
};

shot::shot(uint8_t y, uint8_t x, uint8_t targetY, uint8_t targetX){
    this->y = y;
    this->x = x;
    this->targetY = targetY;
    this->targetX = targetX;
    this->isShotViable();
}

void shot::isShotViable(){
    double unitVectorY = (this->targetY-this->y)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2)), unitVectorX = (this->targetX-this->x)/sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2));
    //for(uint8_t i = 0; i < round(sqrt(pow(this->targetY-this->y, 2) + pow(this->targetX-this->x, 2))/sqrt(pow(unitVectorY,2) + pow(unitVectorX,2))); i++){
    for(uint8_t i = 0;; i++){
        //cout << (int)i << endl << unitVectorY << " " << unitVectorX << endl;
        if(round(this->y + unitVectorY*i) == this->targetY && round(this->x + unitVectorX*i) == this->targetX) break;
        //cout << "Target Y: " << (int)this->targetY << " Target X: " << (int)this->targetX << endl << "Rounded Y: " << (int)round(this->y + unitVectorY*i) << " Rounded X: " << (int)round(this->x + unitVectorX*i) << endl << endl;
        this->pointVector.push_back(point(round(this->y + unitVectorY*i), round(this->x + unitVectorX*i)));
    }
    for(uint8_t i = 0; i < this->pointVector.size(); i++){
        if(this->Field->getFieldValue(pointVector[i].y, pointVector[i].x) == WALL) this->viableShot = false;
    }
}

bool shot::move(){
    if(this->delayCounter == this->baseDelay){
        this->delayCounter = 0;
        Field->changeFieldValue(this->pointVector[0].y, this->pointVector[0].x, this->lastfield);
        this->lastfield = Field->getFieldValue(this->pointVector[0].y, this->pointVector[0].x);
        this->pointVector.erase(this->pointVector.begin());
        Field->changeFieldValue(this->pointVector[0].y, this->pointVector[0].x, SHOT);
    }else{
        this->delayCounter++;
    }
    return false;
}

#endif 

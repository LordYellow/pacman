#ifndef ENEMY_H
#define ENEMY_H

#include <array>
#include <math.h>
#include "definitions.h"

using namespace std;

class enemy {
public:
    enemy(array<array<uint8_t, WIDTH>, HIGH> *field, uint8_t pacmanY, uint8_t pacmanX);
    uint8_t posX= 0, posY = 0, randomDirection = rand() % 4, lastfield = ROADWITHCOIN, baseDelay = 10, delayCounter = 0;
    bool alive = true;
    bool move(array<array<uint8_t, WIDTH>, HIGH> *field){
        if((*field)[this->posY][this->posX] != ENEMY){this->alive = false; return false;}
        if(this->delayCounter == this->baseDelay){
            this->delayCounter = 0;
            (*field)[this->posY][this->posX] = this->lastfield;
            for(uint8_t i = 0; i < 4; i++){
                switch(this->randomDirection){
                    case 0: this->posY--; break;
                    case 1: this->posX++; break;
                    case 2: this->posY++; break;
                    case 3: this->posX--; break;
                }
                if((*field)[this->posY][this->posX] != WALL){
                    if((*field)[this->posY][this->posX] == PACMAN){(*field)[this->posY][this->posX] = ENEMY; return true;}
                    this->lastfield = (*field)[this->posY][this->posX];
                    if(this->lastfield == ENEMY) this->lastfield = ROAD;
                    (*field)[this->posY][this->posX] = ENEMY;
                    return false;
                }else{
                    switch(this->randomDirection){
                        case 2: this->posY--; break;
                        case 3: this->posX++; break;
                        case 0: this->posY++; break;
                        case 1: this->posX--; break;
                    }
                    this->randomDirection = rand() % 4;
                }
            }
        }else{
            this->delayCounter++;
        }
        return false;
    }
};

enemy::enemy(array<array<uint8_t, WIDTH>, HIGH> *field, uint8_t pacmanY, uint8_t pacmanX){
    srand(time(NULL));
    for(;;){
        uint8_t y = rand() % HIGH, x = rand() % WIDTH;
        if((*field)[y][x] == ROADWITHCOIN){
            if(sqrt(pow((y-pacmanY),2)+pow((x-pacmanX),2)) > 5){
                (*field)[y][x] = ENEMY;
                this->posX = x;
                this->posY = y;
                break;
            }
        }
    }
}

#endif

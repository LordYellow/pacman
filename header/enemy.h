#ifndef ENEMY_H
#define ENEMY_H

#include <array>
#include "definitions.h"

using namespace std;

class enemy {
public:
    enemy(array<array<uint8_t, WIDTH>, HIGH> *field);
    uint8_t posX= 0, posY = 0, randomDirection = rand() % 4, lastfield = ROADWITHCOIN;
    bool move(array<array<uint8_t, WIDTH>, HIGH> *field){
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
        return false;
    }
};

enemy::enemy(array<array<uint8_t, WIDTH>, HIGH> *field){
    srand(time(NULL));
    for(;;){
        uint8_t y = rand() % HIGH, x = rand() % WIDTH;
        if((*field)[y][x] == ROADWITHCOIN){
            (*field)[y][x] = ENEMY;
            this->posX = x;
            this->posY = y;
            break;
        }
    }
}

#endif

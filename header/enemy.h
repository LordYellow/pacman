#ifndef ENEMY_H
#define ENEMY_H

#include <array>
#include <math.h>
#include "definitions.h"
#include "pathfinder.h"
#include <vector>
#include "draw.h"

#include "player.h"

using namespace std;

class enemy {
public:
    enemy(uint8_t pacmanY, uint8_t pacmanX);
    uint8_t posX= 0, posY = 0, randomDirection = rand() % 4, lastfield = ROADWITHCOIN, baseDelay = 10, delayCounter = 0;
    bool alive = true;
    static array<array<uint8_t, WIDTH>, HIGH> *field;
    
    bool youSeePacman();
    bool youDontSeePacman();
    /**
     * @brief moves the enemy
     */
    bool move(uint8_t pacmanY, uint8_t pacmanX);
};

enemy::enemy(uint8_t pacmanY, uint8_t pacmanX){
    srand(time(NULL));
    for(;;){
        uint8_t y = rand() % HIGH, x = rand() % WIDTH;
        if((*this->field)[y][x] == ROADWITHCOIN){
            if(sqrt(pow((y-pacmanY),2)+pow((x-pacmanX),2)) > 5){
                (*this->field)[y][x] = ENEMY;
                this->posX = x;
                this->posY = y;
                break;
            }
        }
    }
}

bool enemy::move(uint8_t pacmanY, uint8_t pacmanX){
    if((*this->field)[this->posY][this->posX] != ENEMY){this->alive = false; return false;} //I dont know why i need this, but i think i will keep it for now
        if(this->delayCounter == this->baseDelay){
            this->delayCounter = 0;
            if(sqrt(pow((this->posY-pacmanY),2)+pow((this->posX-pacmanX),2)) > 20){
                return this->youDontSeePacman();
            }else{
                return this->youSeePacman();
            }
        }else{
            this->delayCounter++;
            return false;
        }
}

bool enemy::youDontSeePacman(){
    (*this->field)[this->posY][this->posX] = this->lastfield;
            for(uint8_t i = 0; i < 4; i++){
                switch(this->randomDirection){
                    case 0: this->posY--; break;
                    case 1: this->posX++; break;
                    case 2: this->posY++; break;
                    case 3: this->posX--; break;
                }
                if((*this->field)[this->posY][this->posX] != WALL){
                    if((*this->field)[this->posY][this->posX] == PACMAN){(*field)[this->posY][this->posX] = ENEMY; return true;}
                    this->lastfield = (*this->field)[this->posY][this->posX];
                    if(this->lastfield == ENEMY) this->lastfield = ROAD;
                    (*this->field)[this->posY][this->posX] = ENEMY;
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

bool enemy::youSeePacman(){
    if((*this->field)[this->posY+1][this->posX] == PACMAN){return true;}
    if((*this->field)[this->posY-1][this->posX] == PACMAN){return true;}
        if((*this->field)[this->posY][this->posX+1] == PACMAN){return true;}
        if((*this->field)[this->posY][this->posX-1] == PACMAN){return true;}
        
        vector<pathfinder> pathVector1, pathVector2;
        (*this->field)[this->posY][this->posX] = this->lastfield;
        array<array<uint8_t, WIDTH>, HIGH> originalfield = *field;
        (*this->field)[this->posY][this->posX] = WALL;
        if((*this->field)[this->posY+1][this->posX] != WALL){pathVector1.push_back(pathfinder(this->posY+1, this->posX, this->field));}
        if((*this->field)[this->posY-1][this->posX] != WALL){pathVector1.push_back(pathfinder(this->posY-1, this->posX, this->field));}
        if((*this->field)[this->posY][this->posX+1] != WALL){pathVector1.push_back(pathfinder(this->posY, this->posX+1, this->field));}
        if((*this->field)[this->posY][this->posX-1] != WALL){pathVector1.push_back(pathfinder(this->posY, this->posX-1, this->field));}
        player pm(this->field);
        for(;;){
            for(uint8_t i = 0; i < pathVector1.size(); i++){
                if(pathVector1[i].pacmanIsNear){
                    this->posY = pathVector1[i].originalY;
                    this->posX = pathVector1[i].originalX;
                    (*this->field) = originalfield;
                    (*this->field)[this->posY][this->posX] = ENEMY;
                    return false;
                }
                if(pathVector1[i].connections == 0){
                    pathVector1.erase(pathVector1.begin()+i);
                }
                for(uint8_t a = 0; a < pathVector1[i].connections; a++){
                    pathfinder path = pathVector1[i].findaWay();
                    if(path != pathVector1[i]){
                        pathVector2.push_back(path);
                    }
                }
            }
            pathVector1 = pathVector2;
            pathVector2.clear();
        }
}

#endif

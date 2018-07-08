#ifndef ENEMY_H
#define ENEMY_H

#include <array>
#include <math.h>
#include "definitions.h"
#include "pathfinder.h"
#include <vector>
#include "draw.h"
#include "field.h"

#include "player.h"

using namespace std;

class enemy {
public:
    enemy(uint8_t pacmanY, uint8_t pacmanX);
    uint8_t posX= 0, posY = 0, randomDirection = rand() % 4, lastfield = ROADWITHCOIN, baseDelay = 10, delayCounter = 0, shotDelay = 10, shotDelayCounter = 10;
    bool alive = true;
    static field *Field;
    
    /**
     * @brief moves the enemy if you see Pacman
     * 
     * @return true if pacman gets killed
     */
    bool youSeePacman();
    
    /**
     * @brief moves the enemy if Pacman is not in Range
     * 
     * @return true if pacman gets killed
     */
    bool youDontSeePacman();
    
    /**
     * @brief moves the enemy
     * 
     * @param pacmanY is the Y coordinate of pacman 
     * @param pacmanX is the X coordinate of pacman
     * 
     * @return true if pacman gets killed
     */
    bool move(uint8_t pacmanY, uint8_t pacmanX);
    
    /**
     * @brief checks if the Enemy can shot
     * 
     * @return true if the Enemy is able to shot
     */
    bool shot(uint8_t pacmanY, uint8_t pacmanX);
};

enemy::enemy(uint8_t pacmanY, uint8_t pacmanX){
    srand(time(NULL));
    for(;;){
        uint8_t y = rand() % HIGH, x = rand() % WIDTH;
        if(this->Field->getFieldValue(y,x) == ROADWITHCOIN){
            if(sqrt(pow((y-pacmanY),2)+pow((x-pacmanX),2)) > 5){
                this->Field->changeFieldValue(y, x, ENEMY);
                this->posX = x;
                this->posY = y;
                break;
            }
        }
    }
}

bool enemy::move(uint8_t pacmanY, uint8_t pacmanX){
    if(this->Field->getFieldValue(this->posY, this->posX) != ENEMY){this->alive = false; return false;} //I dont know why i need this, but i think i will keep it for now
        if(this->delayCounter == this->baseDelay){
            this->delayCounter = 0;
            if(this->shotDelayCounter < this->shotDelay) this->shotDelayCounter++;
            if(sqrt(pow((this->posY-pacmanY),2)+pow((this->posX-pacmanX),2)) > PACMANDETECTIONRANGE){
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
    this->Field->changeFieldValue(this->posY, this->posX, this->lastfield);
            for(uint8_t i = 0; i < 4; i++){
                switch(this->randomDirection){
                    case 0: this->posY--; break;
                    case 1: this->posX++; break;
                    case 2: this->posY++; break;
                    case 3: this->posX--; break;
                }
                if(this->Field->getFieldValue(this->posY, this->posX) != WALL && this->Field->getFieldValue(this->posY, this->posX) != LOWERWALL){
                    if(this->Field->getFieldValue(this->posY, this->posX) == PACMAN){this->Field->changeFieldValue(this->posY, this->posX, ENEMY); return true;}
                    this->lastfield = this->Field->getFieldValue(this->posY, this->posX);
                    if(this->lastfield == ENEMY) this->lastfield = ROAD;
                    this->Field->changeFieldValue(this->posY, this->posX, ENEMY);
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
    //this will check if pacman is near. if thats the case it will kill it 
    if(this->Field->getFieldValue(this->posY+1, this->posX) == PACMAN){return true;}
    if(this->Field->getFieldValue(this->posY-1, this->posX) == PACMAN){return true;}
    if(this->Field->getFieldValue(this->posY, this->posX+1) == PACMAN){return true;}
    if(this->Field->getFieldValue(this->posY, this->posX-1) == PACMAN){return true;}
    
    vector<pathfinder> pathVector1, pathVector2;
    array<array<uint8_t, WIDTH>, HIGH> originalfield = this->Field->Field; //saves the Field, because the enemys will change it
    this->Field->changeFieldValue(this->posY, this->posX, WALL);
    //create pathfinders 
    if(this->Field->getFieldValue(this->posY+1, this->posX) != WALL && this->Field->getFieldValue(this->posY+1, this->posX) != LOWERWALL){pathVector1.push_back(pathfinder(this->posY+1, this->posX, &originalfield));}
    if(this->Field->getFieldValue(this->posY-1, this->posX) != WALL && this->Field->getFieldValue(this->posY-1, this->posX) != LOWERWALL){pathVector1.push_back(pathfinder(this->posY-1, this->posX, &originalfield));}
    if(this->Field->getFieldValue(this->posY, this->posX+1) != WALL && this->Field->getFieldValue(this->posY, this->posX+1) != LOWERWALL){pathVector1.push_back(pathfinder(this->posY, this->posX+1, &originalfield));}
    if(this->Field->getFieldValue(this->posY, this->posX-1) != WALL && this->Field->getFieldValue(this->posY, this->posX-1) != LOWERWALL){pathVector1.push_back(pathfinder(this->posY, this->posX-1, &originalfield));}
    for(;;){
        for(uint8_t i = 0; i < pathVector1.size(); i++){
            if(pathVector1[i].pacmanIsNear){
                // here the enemy will use the shortest way to pacman
                this->Field->changeFieldValue(this->posY, this->posX, this->lastfield);
                this->posY = pathVector1[i].originalY;
                this->posX = pathVector1[i].originalX;
                this->lastfield = this->Field->getFieldValue(this->posY, this->posX);
                this->Field->changeFieldValue(this->posY, this->posX, ENEMY);
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

bool enemy::shot(uint8_t pacmanY, uint8_t pacmanX){
    if(this->shotDelayCounter != this->shotDelay) return false;
    if(sqrt(pow((this->posY-pacmanY),2)+pow((this->posX-pacmanX),2)) > PACMANDETECTIONRANGE){
        this->shotDelayCounter = 0;
        return true;
    }else{
        return false;
    }
}

#endif

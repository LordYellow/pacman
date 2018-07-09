#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <array>
#include "definitions.h"

using namespace std;

#define USEDWAY 20
#define PACMAN 10

class pathfinder{
public:
    pathfinder(uint8_t x, uint8_t y, array<array<uint8_t, WIDTH>, HIGH> *wField);
    pathfinder(pathfinder* oldpath, uint8_t x, uint8_t y);
    bool emptyway = true, pacmanIsNear = false;
    uint8_t posX, posY, connections, originalX, originalY;
    array<array<uint8_t, WIDTH>, HIGH> *field;
    
    /**
     * @brief returns a new pathfinder connected to this one. you have to call this function for the number of connections to get enough pathfinders. if you already called it that many times this function will return itself
     * 
     * @return one connected pathfinder
     */
    pathfinder findaWay();
    
    /**
     * @brief calculates the number of possible connections 
     * 
     * @return the number of possible connections
     */
    uint8_t numberOfConnections();
};

pathfinder::pathfinder(uint8_t y, uint8_t x, array<array<uint8_t, WIDTH>, HIGH> *wField){
    this->posX = x;
    this->posY = y;
    this->field = wField;
    this->connections = this->numberOfConnections();
    (*this->field)[this->posY][this->posX] = USEDWAY;
    this->originalX = x;
    this->originalY = y;
}

pathfinder::pathfinder(pathfinder* oldpath, uint8_t y, uint8_t x){
    this->posX = x;
    this->posY = y;
    this->field = oldpath->field;
    this->connections = this->numberOfConnections();
    (*this->field)[this->posY][this->posX] = USEDWAY;
    this->originalX = oldpath->originalX;
    this->originalY = oldpath->originalY;
}

uint8_t pathfinder::numberOfConnections(){
    uint8_t conns = 0;
    if((*this->field)[this->posY+1][this->posX] != WALL && (*this->field)[this->posY+1][this->posX] != USEDWAY && (*this->field)[this->posY+1][this->posX] != LOWERWALL){if((*this->field)[this->posY+1][this->posX] == PACMAN){this->pacmanIsNear = true; conns++;}else{conns++;}}
    if((*this->field)[this->posY-1][this->posX] != WALL && (*this->field)[this->posY-1][this->posX] != USEDWAY && (*this->field)[this->posY-1][this->posX] != LOWERWALL){if((*this->field)[this->posY-1][this->posX] == PACMAN){this->pacmanIsNear = true; conns++;}else{conns++;}}
    if((*this->field)[this->posY][this->posX+1] != WALL && (*this->field)[this->posY][this->posX+1] != USEDWAY && (*this->field)[this->posY][this->posX+1] != LOWERWALL){if((*this->field)[this->posY][this->posX+1] == PACMAN){this->pacmanIsNear = true; conns++;}else{conns++;}}
    if((*this->field)[this->posY][this->posX-1] != WALL && (*this->field)[this->posY][this->posX-1] != USEDWAY && (*this->field)[this->posY][this->posX-1] != LOWERWALL){if((*this->field)[this->posY][this->posX-1] == PACMAN){this->pacmanIsNear = true; conns++;}else{conns++;}}
    return conns;
}

pathfinder pathfinder::findaWay(){
    if((*this->field)[this->posY+1][this->posX] != WALL && (*this->field)[this->posY+1][this->posX] != USEDWAY && (*this->field)[this->posY+1][this->posX] != LOWERWALL){if((*this->field)[this->posY+1][this->posX] == PACMAN){this->pacmanIsNear = true;}else{return pathfinder(this, this->posY+1, this->posX);}}
    if((*this->field)[this->posY-1][this->posX] != WALL && (*this->field)[this->posY-1][this->posX] != USEDWAY && (*this->field)[this->posY-1][this->posX] != LOWERWALL){if((*this->field)[this->posY-1][this->posX] == PACMAN){this->pacmanIsNear = true;}else{return pathfinder(this, this->posY-1, this->posX);}}
    if((*this->field)[this->posY][this->posX+1] != WALL && (*this->field)[this->posY][this->posX+1] != USEDWAY && (*this->field)[this->posY][this->posX+1] != LOWERWALL){if((*this->field)[this->posY][this->posX+1] == PACMAN){this->pacmanIsNear = true;}else{return pathfinder(this, this->posY, this->posX+1);}}
    if((*this->field)[this->posY][this->posX-1] != WALL && (*this->field)[this->posY][this->posX-1] != USEDWAY && (*this->field)[this->posY][this->posX-1] != LOWERWALL){if((*this->field)[this->posY][this->posX-1] == PACMAN){this->pacmanIsNear = true;}else{return pathfinder(this, this->posY, this->posX-1);}}
    
    return *this; //this should never happen, but i dislike the compiler warning. if it happes (at the moment i am not sure if thats the case) it will not be pushed into the seccond vector
}

inline bool operator!=(const pathfinder &lhs, const pathfinder &rhs){ return !(lhs.posX == rhs.posX && lhs.posY == rhs.posY); }

#endif

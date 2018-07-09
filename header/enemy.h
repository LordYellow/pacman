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
    enemy(fieldtyp<uint8_t> *thefield,array<string, 8> *colors, player *pacman);
    uint8_t posX= 0, posY = 0, randomDirection = myrandom() % 4, baseDelay = 10, delayCounter = 0, shotDelay = 10, shotDelayCounter = 10;
    bool visibility = false;
    fieldtyp<uint8_t> *field;
    array<string, 8> *colors;
    player *pacman; 
    
    /**
     * @brief moves the enemy if you see Pacman
     * 
     * @return true if pacman gets killed
     */
    void youSeePacman();
    
    /**
     * @brief moves the enemy if Pacman is not in Range
     * 
     * @return true if pacman gets killed
     */
    void youDontSeePacman();
    
    /**
     * @brief moves the enemy
     * 
     * @param pacmanY is the Y coordinate of pacman 
     * @param pacmanX is the X coordinate of pacman
     * 
     * @return true if pacman gets killed
     */
    void move();
    
    void checkvisibility(player *pacman);
    
    bool shot();
};

enemy::enemy(fieldtyp<uint8_t> *thefield, array<string, 8> *colors, player *pacman){
    this->field = thefield;
    this->colors = colors;
    this->pacman = pacman;
    for(;;){
        uint8_t y = myrandom() % HIGH, x = myrandom() % WIDTH;
        if((*this->field)[y][x] == ROADWITHCOIN){
            if(sqrt(pow((y-pacman->posY),2)+pow((x-pacman->posX),2)) > 5){
                this->posX = x;
                this->posY = y;
                if(this->visibility) draw(this->posX, this->posY, ENEMY);
                break;
            }
        }
    }
}

void enemy::move(){
        if(this->delayCounter == this->baseDelay){
            this->delayCounter = 0;
            drawWithTexture(this->posX, this->posY, this->colors, (*this->field)[this->posY][this->posX]);
            if(this->shotDelayCounter < this->shotDelay) this->shotDelayCounter++;
            if(sqrt(pow((this->posY-pacman->posY),2)+pow((this->posX-pacman->posX),2)) > PACMANDETECTIONRANGE){
                this->youDontSeePacman();
            }else{
                this->youSeePacman();
            }
        }else{
            this->delayCounter++;
        }
}

void enemy::youDontSeePacman(){
    for(uint8_t i = 0; i < 4; i++){
        switch(this->randomDirection){
            case 0: this->posY--; break;
            case 1: this->posX++; break;
            case 2: this->posY++; break;
            case 3: this->posX--; break;
        }
        if((*this->field)[this->posY][this->posX] != WALL && (*this->field)[this->posY][this->posX] != LOWERWALL){
            if(this->visibility) draw(this->posX, this->posY, ENEMY);
            return;
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
}

void enemy::youSeePacman(){
    //this will check if pacman is near. if thats the case it will kill it 
    if(this->posY+1 == this->pacman->posY && this->posX == this->pacman->posX){this->posY+=1; draw(this->posX, this->posY, ENEMY); return;}
    if(this->posY-1 == this->pacman->posY && this->posX == this->pacman->posX){this->posY-=1; draw(this->posX, this->posY, ENEMY); return;}
    if(this->posY == this->pacman->posY && this->posX+1 == this->pacman->posX){this->posX+=1; draw(this->posX, this->posY, ENEMY); return;}
    if(this->posY == this->pacman->posY && this->posX-1 == this->pacman->posX){this->posX-=1; draw(this->posX, this->posY, ENEMY); return;}
    
    vector<pathfinder> pathVector1, pathVector2;
    fieldtyp<uint8_t> pathfinderField = *this->field;
    pathfinderField[pacman->posY][pacman->posX] = 10; //Pathfinder needs that to find pacman
    //create pathfinders 
    if((*this->field)[this->posY+1][this->posX] != WALL && (*this->field)[this->posY+1][this->posX] != LOWERWALL){pathVector1.push_back(pathfinder(this->posY+1, this->posX, &pathfinderField));}
    if((*this->field)[this->posY-1][this->posX] != WALL && (*this->field)[this->posY-1][this->posX] != LOWERWALL){pathVector1.push_back(pathfinder(this->posY-1, this->posX, &pathfinderField));}
    if((*this->field)[this->posY][this->posX+1] != WALL && (*this->field)[this->posY][this->posX+1] != LOWERWALL){pathVector1.push_back(pathfinder(this->posY, this->posX+1, &pathfinderField));}
    if((*this->field)[this->posY][this->posX-1] != WALL && (*this->field)[this->posY][this->posX-1] != LOWERWALL){pathVector1.push_back(pathfinder(this->posY, this->posX-1, &pathfinderField));}
    for(;;){
        for(uint8_t i = 0; i < pathVector1.size(); i++){
            if(pathVector1[i].pacmanIsNear){
                // here the enemy will use the shortest way to pacman
                drawWithTexture(this->posX, this->posY, this->colors, (*this->field)[this->posY][this->posX]);
                this->posY = pathVector1[i].originalY;
                this->posX = pathVector1[i].originalX;
                if(this->visibility) draw(this->posX, this->posY, ENEMY);
                return;
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

void enemy::checkvisibility(player *pacman){
    double unitVectorY = (pacman->posY-this->posY)/sqrt(pow(pacman->posY-this->posY, 2) + pow(pacman->posX-this->posX, 2));
    double unitVectorX = (pacman->posX-this->posX)/sqrt(pow(pacman->posY-this->posY, 2) + pow(pacman->posX-this->posX, 2));
    int x = this->posX, y = this->posY;
    this->visibility = true;
    for(int i = 0; i < sqrt(pow((this->posY-pacman->posY),2)+pow((this->posX-pacman->posX),2)); i++){
        if(pacman->posX == (int)(x + unitVectorX*i) && pacman->posY == (int)(y + unitVectorY*i)) return;
        if((*this->field)[(int)(y + unitVectorY*i)][(int)(x + unitVectorX*i)] ==  WALL){this->visibility = false; return;}
    }
    //cin.ignore().get();
}

bool enemy::shot(){
    if(this->shotDelayCounter != this->shotDelay || this->visibility == false) return false;
    if(sqrt(pow((this->posY-pacman->posY),2)+pow((this->posX-pacman->posX),2)) < PACMANDETECTIONRANGE){
        this->shotDelayCounter = 0;
        return true;
    }else{
        return false;
    }
}

#endif

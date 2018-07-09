#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "definitions.h"
#include "random.h"
#include "draw.h"
#include "stuffididnotwrite.h"

using namespace std;

class player {
public:
    player(fieldtyp<uint8_t> *thefield, array<string, 8> *colors);
    uint8_t direction = 0, posX= 0, posY = 0, coins = 0, baseDelay = 10, delayCounter = 0, crushWalls = 0;
    int alive = 1;
    bool getpowerup = false, symbol = false;
    fieldtyp<uint8_t> *field;
    array<string, 8> *colors;
    string getsymbol();
    
    /**
     * @brief makes the screen red if you die
     */
    void deathAnimation();
    
    /**
     * @brief moves the player
     * 
     * @param field is a pointer to the field you play on. this will be removed later
     */
    void move();
    
    void changeDirection();
    
    void showStats();
};

player::player(fieldtyp<uint8_t> *thefield, array<string, 8> *colors){
    this->field = thefield;
    for(;;){
        uint8_t y = myrandom() % HIGH, x = myrandom() % WIDTH;
        if((*this->field)[y][x] == ROADWITHCOIN){
            this->posY = y;
            this->posX = x;
            break;
        }
    }
    this->colors = colors;
}

void player::move(){
    if(this->delayCounter == this->baseDelay){
        this->delayCounter = 0;
        this->symbol = !this->symbol;
        drawWithTexture(this->posX, this->posY, this->colors, (*this->field)[this->posY][this->posX]);
        switch(this -> direction){
            case 0: this->posY--; break;
            case 1: this->posX++; break;
            case 2: this->posY++; break;
            case 3: this->posX--; break;
        }
        if(crushWalls && ((*this->field)[this->posY][this->posX] == WALL || (*this->field)[this->posY][this->posX] == LOWERWALL)){
            if((*this->field)[this->posY][this->posX] == ROADWITHCOIN){this->coins++; (*this->field)[this->posY][this->posX] = ROAD;}
            if((*this->field)[this->posY][this->posX] == POWERUP) {this->getpowerup = true; (*this->field)[this->posY][this->posX] = ROAD;}
            draw(this->posX, this->posY, this->getsymbol());
            (*this->field)[this->posY][this->posX] = ROAD;
            this->crushWalls--;
        }else{
            if((*this->field)[this->posY][this->posX] != WALL && (*this->field)[this->posY][this->posX] != LOWERWALL){
                if((*this->field)[this->posY][this->posX] == ROADWITHCOIN){this->coins++; (*this->field)[this->posY][this->posX] = ROAD;}
                if((*this->field)[this->posY][this->posX] == POWERUP) {this->getpowerup = true; (*this->field)[this->posY][this->posX] = ROAD;}
                draw(this->posX, this->posY, this->getsymbol());
            }else{
                switch(this -> direction){
                    case 2: this->posY--; break;
                    case 3: this->posX++; break;
                    case 0: this->posY++; break;
                    case 1: this->posX--; break;
                }
            draw(this->posX, this->posY, this->getsymbol());
            }
        }
    }else{
        this->delayCounter++;
    }
}

string player::getsymbol(){
    if(!this->alive) return "\033[48;5;7;38;5;9m☠ "; 
    if(this->symbol){return "\033[48;5;7;38;5;3m○ ";}
    switch(direction){
        case 0: return "\033[48;5;7;38;5;3mᗢ ";
        case 1: return "\033[48;5;7;38;5;3mᗧ ";
        case 2: return "\033[48;5;7;38;5;3mᗣ ";
        case 3: return "\033[48;5;7;38;5;3mᗤ ";
        default: return "somthing went wrong";
    }
}

void player::changeDirection(){
    char c = '!';
    if(_kbhit()){
        c = getchar();
    }
    switch(c) {
        case 'w': this->direction = 0; break; // up
        case 's': this->direction = 2; break; // down
        case 'd': this->direction = 1; break; // right
        case 'a': this->direction = 3; break; // left
        default: break;
    }
}

void player::showStats(){
    cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(HIGH+1) << ";" << "0" << "H" << "\033[0m";
    cout << "SCORE: " << (int)this->coins << endl;
    cout << "LIVES: " << (int)this->alive << endl;
    cout << "ABILITY TO CRUSH WALLS: " << (int)this->crushWalls << endl;
}

#endif 

#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "definitions.h"
#include <iostream>
#include <chrono>
#include <thread>

class player {
public:
    player(array<array<uint8_t, WIDTH>, HIGH> *field);
    uint8_t direction = 0, posX= 0, posY = 0, coins = 0, baseDelay = 10, delayCounter = 0, alive =1, crushWalls = 0;
    bool getpowerup = false, symbol = false;
    array<array<uint8_t, WIDTH>, HIGH> *field;
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
};

player::player(array<array<uint8_t, WIDTH>, HIGH> *thefield){
    this->field = thefield;
    for(uint8_t y = 0; y < HIGH; y++){
      for(uint8_t x = 0; x < WIDTH; x++){
          if((*thefield)[y][x] == PACMAN){
              this -> posX = x;
              this -> posY = y;
            }
        }
    }
}

void player::move(){
    if(this->delayCounter == this->baseDelay){
        this->delayCounter = 0;
        this->symbol = !this->symbol;
        (*this->field)[this->posY][this->posX] = ROAD;
        switch(this -> direction){
            case 0: this->posY--; break;
            case 1: this->posX++; break;
            case 2: this->posY++; break;
            case 3: this->posX--; break;
        }
        if(crushWalls && (*this->field)[this->posY][this->posX] == WALL){
            if((*this->field)[this->posY][this->posX] == ROADWITHCOIN) this->coins++;
            if((*this->field)[this->posY][this->posX] == POWERUP) this->getpowerup = true;
            if((*this->field)[this->posY][this->posX] == ENEMY){
                this->alive--;
                this->deathAnimation();
            }
            (*this->field)[this->posY][this->posX] = PACMAN;
            this->crushWalls--;
        }else{
            if((*this->field)[this->posY][this->posX] != WALL){
                if((*this->field)[this->posY][this->posX] == ROADWITHCOIN) this->coins++;
                if((*this->field)[this->posY][this->posX] == POWERUP) this->getpowerup = true;
                if((*this->field)[this->posY][this->posX] == ENEMY){
                    this->alive--;
                    this->deathAnimation();
                }
                (*this->field)[this->posY][this->posX] = PACMAN;
            }else{
                switch(this -> direction){
                    case 2: this->posY--; break;
                    case 3: this->posX++; break;
                    case 0: this->posY++; break;
                    case 1: this->posX--; break;
                }
            (*this->field)[this->posY][this->posX] = PACMAN;
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
    
void player::deathAnimation(){
    system("clear");
    for(int i = 0; i < HIGH; i++){
            for(int a = 0; a < WIDTH; a++){
                cout << "\033[48;5;9m  " << "\033[0m";
            }
            cout << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(120));
}
#endif 

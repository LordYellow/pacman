#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "definitions.h"
#include <iostream>

//tried to put this into the class, but for some reason it does not work :(
//bool symbol = false;

class player {
public:
    player(array<array<uint8_t, WIDTH>, HIGH> field);
    uint8_t direction = 0, posX= 0, posY = 0, coins = 0;
    
    
    bool symbol = false;
    string getsymbol(){
        if(this->symbol){this->symbol = false; return "\033[48;5;7;38;5;3m○ ";}
        this->symbol = true;
        switch(direction){
            case 0: return "\033[48;5;7;38;5;3mᗢ ";
            case 1: return "\033[48;5;7;38;5;3mᗧ ";
            case 2: return "\033[48;5;7;38;5;3mᗣ ";
            case 3: return "\033[48;5;7;38;5;3mᗤ ";
            default: return "somthing went wrong";
        }
    }
    
    
    bool alive = true;
    void move(array<array<uint8_t, WIDTH>, HIGH> *field){
        (*field)[this->posY][this->posX] = ROAD;
        switch(this -> direction){
            case 0: this->posY--; break;
            case 1: this->posX++; break;
            case 2: this->posY++; break;
            case 3: this->posX--; break;
        }
        if((*field)[this->posY][this->posX] != WALL){
            if((*field)[this->posY][this->posX] == ROADWITHCOIN) this->coins++;
            if((*field)[this->posY][this->posX] == ENEMY){this->alive = false;}else{(*field)[this->posY][this->posX] = PACMAN;}
        }else{
            switch(this -> direction){
                case 2: this->posY--; break;
                case 3: this->posX++; break;
                case 0: this->posY++; break;
                case 1: this->posX--; break;
            }
            (*field)[this->posY][this->posX] = PACMAN;
        }
        
    };
};

player::player(array<array<uint8_t, WIDTH>, HIGH> field){
  for(uint8_t y = 0; y < HIGH; y++){
      for(uint8_t x = 0; x < WIDTH; x++){
          if(field[y][x] == PACMAN){
              this -> posX = x;
              this -> posY = y;
            }
        }
    }
}

#endif 

#ifndef DRAW_H
#define DRAW_H

#include <map>
#include <iostream>
#include "field.h"

using namespace std;

map<int, string> fieldTextures;

/**
 * @brief fills fieldTextures with Textures
 */
void getColors(){
        fieldTextures[ROADWITHCOIN] = "\033[48;5;7;38;5;2m$ ";
        fieldTextures[ROAD] = "\033[48;5;7m  ";
        fieldTextures[WALL] = "\033[48;5;236m  ";
        fieldTextures[PACMAN] =  "\033[48;5;7;38;5;3mᗤ ";
        fieldTextures[ENEMY] =  "\033[48;5;7;38;5;9m۩ ";
        fieldTextures[PACMANSEARCH] = "\033[48;5;8;38;5;3m+ ";
        fieldTextures[POWERUP] = "\033[48;5;7;38;5;5m⏻ ";
        fieldTextures[USEDWAY] = "\033[48;5;2m  ";
        fieldTextures[LOWERWALL] = "\033[48;5;244m  ";
        fieldTextures[SHOT] = "\033[48;5;13m* ";
}

/**
 * @brief draws the field
 * 
 * @param field is the field you wanna draw
 * @param pacman is your playable caracter
 */
void draw(array<array<uint8_t, WIDTH>, HIGH> field, player *pacman){
        system("clear");
        for(int i = 0; i < HIGH; i++){
                for(int a = 0; a < WIDTH; a++){
                        if(field[i][a] == PACMAN){
                             cout << pacman->getsymbol() << "\033[0m";
                        }else{cout << fieldTextures[field[i][a]] << "\033[0m";}
                }
                cout << endl;
        }
        cout << "SCORE: " << (int)pacman->coins << endl << "LIVES: " << (int)pacman->alive << endl << "ABILITY TO CRUSH WALLS: " << (int)pacman->crushWalls << endl;
}

void drawOnlyNewStuff(field Field, player *pacman){
    for(uint8_t y = 0; y < HIGH; y++){
        for(uint8_t x = 0; x < WIDTH; x++){
            if(Field.bField[y][x]){
                cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(y+1) << ";" << to_string(2*x+1) << "H";
                if(Field.getFieldValue(y,x) == PACMAN){
                    cout << pacman->getsymbol() << "\033[0m";
                }else{cout << fieldTextures[Field.getFieldValue(y,x)] << "\033[0m";}
            }
        }
    }
    cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(HIGH+1) << ";" << "0" << "H" << "\033[0m";
    cout << "SCORE: " << (int)pacman->coins << endl << "LIVES: " << (int)pacman->alive << endl << "ABILITY TO CRUSH WALLS: " << (int)pacman->crushWalls << endl;
    cout << flush;
}

#endif

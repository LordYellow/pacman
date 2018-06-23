#include <iostream>
#include "header/map.h"
#include "header/definitions.h"
#include "header/player.h"
#include "header/stuffididnotwrite.h"
#include "header/random.h"
#include "header/enemy.h"
#include <array>
#include <map>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>

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
        fieldTextures[PACMANSEARCH] = "\033[48;5;30m  ";
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
        cout << "SCORE: " << (int)pacman->coins << endl;
}

array<array<uint8_t, WIDTH>, HIGH> locatepacman(array<array<uint8_t, WIDTH>, HIGH> field){
        for(int y = 0; y < HIGH; y++){
                for(int x = 0; x< WIDTH; x++){
                        if(field[y][x] == PACMAN){
                                for(int i = 0; i < HIGH; i++){
                                        field[i][x] = PACMANSEARCH;
                                }
                                for(int i = 0; i < WIDTH; i++){
                                        field[y][i] = PACMANSEARCH;
                                }
                                field[y][x] = PACMAN;
                                return field;
                        }
                }
        }
        return field;
}

/**
 * @brief gets the commands from the player
 * 
 * @param pacman is a pointer pointing to your playable caracter
 */
void eingabe(player *pacman){
        char c = '!';
        if(_kbhit()){
                c = getchar();
        }
        switch(c) {
                case 'w': (*pacman).direction = 0; break; // up
                case 's': (*pacman).direction = 2; break; // down
                case 'd': (*pacman).direction = 1; break; // right
                case 'a': (*pacman).direction = 3; break; // left
                default: break;
        }
}

int main() {
        //pacman tbd
        //enterseed();
        getColors();
        array<array<uint8_t, WIDTH>, HIGH> field = generateField();
        player pacman(field);
        array<array<uint8_t, WIDTH>, HIGH> *fieldpointer =  &field;
        vector<enemy> enemyvector;
        for(uint8_t i = 0; i < NUMBEROFENEMYS; i++){
                enemyvector.push_back(enemy(fieldpointer));
        }
        draw(locatepacman(field), &pacman);
        for(;;){if(_kbhit()) break;}
        while(pacman.alive){
                draw(field, &pacman);
                cout << (int)pacman.symbol << endl;
                this_thread::sleep_for(chrono::milliseconds(300));
                for(uint8_t i = 0; i < enemyvector.size(); i++){
                        if(enemyvector[i].move(fieldpointer)) pacman.alive = false;
                }
                eingabe((&pacman));
                pacman.move(fieldpointer);
                
        }
        draw(field, &pacman);
        cout << "GAME OVER" << endl;
        return 0;
}

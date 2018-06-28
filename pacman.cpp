#include <iostream>
#include "header/map.h"
#include "header/definitions.h"
#include "header/player.h"
#include "header/stuffididnotwrite.h"
#include "header/random.h"
#include "header/enemy.h"
#include "header/powerup.h"
#include "header/pathfinder.h"
#include "header/draw.h"
#include <array>
#include <map>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

array<array<uint8_t, WIDTH>, HIGH>* enemy::field;
array<array<uint8_t, WIDTH>, HIGH>* pathfinder::field;



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
        player pacman(&field);
        enemy::field = &field;
        pathfinder::field = &field;
        vector<enemy> enemyvector;
        for(uint8_t i = 0; i < NUMBEROFENEMYS; i++){
                enemyvector.push_back(enemy(pacman.posY, pacman.posX));
        }
        draw(locatepacman(field), &pacman);
        for(;;){if(_kbhit()) break;}
        while(pacman.alive){
                draw(field, &pacman);
                if(pacman.getpowerup){
                        givePowerup(&pacman);
                        pacman.getpowerup = false;
                }
                this_thread::sleep_for(chrono::milliseconds(30));
                for(uint8_t i = 0; i < enemyvector.size(); i++){
                        if(enemyvector[i].alive){
                                if(enemyvector[i].move(pacman.posY, pacman.posX)){
                                        pacman.deathAnimation();
                                        enemyvector[i].alive = false;
                                        pacman.alive--;
                                }
                        }
                }
                eingabe((&pacman));
                pacman.move();
        }
        field[pacman.posY][pacman.posX] = PACMAN;
        draw(field, &pacman);
        cout << "GAME OVER" << endl;
        return 0;
}

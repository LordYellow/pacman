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
#include "header/menue.h"
#include "header/field.h"
#include "header/shot.h"
#include <array>
#include <map>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

field* enemy::Field;
field* shot::Field;
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
        while(true){
                if(menue()){return 0;}else{loadingscreen();}
                getColors();
                field field(generateField());
                player pacman(&field);
                enemy::Field = &field;
                shot::Field = &field;
                pathfinder::field = &(field.Field);
                vector<enemy> enemyvector;
                vector<shot> shotvector;
                for(uint8_t i = 0; i < NUMBEROFENEMYS; i++){
                        enemyvector.push_back(enemy(pacman.posY, pacman.posX));
                }
                draw(locatepacman(field.Field), &pacman);
                for(;;){if(_kbhit()) break;}
                draw(field.Field, &pacman);
                while(pacman.alive){
                        drawOnlyNewStuff(field, &pacman);
                        cout << shotvector.size() << endl;
                        field.resetbField();
                        if(pacman.getpowerup){
                                givePowerup(&pacman);
                                pacman.getpowerup = false;
                                draw(field.Field, &pacman);
                        }
                        this_thread::sleep_for(chrono::milliseconds(30));
                        for(uint8_t i = 0; i < enemyvector.size(); i++){
                                if(enemyvector[i].alive){
                                        if(enemyvector[i].move(pacman.posY, pacman.posX)){
                                                pacman.deathAnimation();
                                                draw(field.Field, &pacman);
                                                enemyvector[i].alive = false;
                                                pacman.alive--;
                                        }
                                        if(enemyvector[i].shot(pacman.posY, pacman.posX)){
                                                shotvector.push_back(shot(enemyvector[i].posY, enemyvector[i].posX, pacman.posY, pacman.posX));
                                        }
                                }else{
                                        enemyvector[i].alive = true;
                                        enemyvector[i].posX = WIDTH/2;
                                        enemyvector[i].posY = HIGH/2;
                                        field.changeFieldValue(HIGH/2, WIDTH/2, ENEMY);
                                }
                        }
                        for(uint8_t i = 0; i < shotvector.size(); i++){
                                if(shotvector[i].viableShot){
                                        if(shotvector[i].move()){
                                                pacman.deathAnimation();
                                                draw(field.Field, &pacman);
                                                shotvector[i].viableShot = false;
                                                pacman.alive--;
                                        }
                                }else{
                                        //shotvector.erase(shotvector.begin()+i);
                                }
                        }
                        eingabe((&pacman));
                        pacman.move();
                }
                field.changeFieldValue(pacman.posY, pacman.posX, PACMAN);
                draw(field.Field, &pacman);
                gameover(&pacman);
        }
}

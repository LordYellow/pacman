#include <iostream>
#include "header/map.h"
#include "header/draw.h"
#include "header/player.h"
#include "header/enemy.h"
#include "header/menue.h"
#include "header/powerup.h"
#include "header/shot.h"
#include <array>
#include <chrono>
#include <thread>
#include <vector>

#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <sys/ioctl.h>

using namespace std;

void createShots(player *pacman, vector<shot> *shotVector, vector<enemy> *enemyVector, array<string, 8> *colors){
        for(uint8_t i = 0; i < NUMBEROFENEMYS; i++){
                if((*enemyVector)[i].shot()){
                        (*shotVector).push_back(shot((*enemyVector)[i].posY, (*enemyVector)[i].posX, pacman->posY, pacman->posX, colors));
                }
        }
}

void didIdie(player *pacman, vector<enemy> *enemyVector){
        for(uint8_t i = 0; i < NUMBEROFENEMYS; i++){
                if(pacman->posY == (*enemyVector)[i].posY && pacman->posX == (*enemyVector)[i].posX){
                        pacman->alive--;
                        (*enemyVector)[i].posY = HIGH/2;
                        (*enemyVector)[i].posX = WIDTH/2;
                        cout << "you died :(" << endl;
                }
        }
}

void locatepacman(player *pacman){
        for(int i = 0; i < HIGH; i++){
                draw(pacman->posX, i, "\033[48;5;8;38;5;3m+ ");
        }
        for(int i = 0; i < WIDTH; i++){
                draw(i, pacman->posY, "\033[48;5;8;38;5;3m+ ");
        }
        draw(pacman->posX, pacman->posY, pacman->getsymbol());
}

int main() {
        
        //i dont know what this is. it does not work like i want, but without it its worse
        static const int STDIN = 0;
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        
        menue();
        
        system("clear");
        
        // this is the field you play on. Its just a map, it will not show the position of enemys
        fieldtyp<uint8_t> field = generateField();
        
        //this array contains the textures of everything, except for pacman
        array<string, 8> colors;
        setcolors(&colors);
        
        //a new pacman will be born 
        player pacman(&field, &colors);
        
        vector<enemy> enemyVector; // i wanted to use an array here, but it was different...
        for(uint8_t i = 0; i < NUMBEROFENEMYS; i++){enemyVector.push_back(enemy(&field, &colors, &pacman));}
        
        vector<shot> shotVector;
        
        //locates pacman
        locatepacman(&pacman);
        
        //waits until you are ready
        cin.ignore().get();
        
        //at the beginning the whole field will be drawn
        drawWholeField(&field, &colors);
        
        while(pacman.alive){
                
                //you can change the direction of pacman with this
                pacman.changeDirection();
                
                //pacman will be moved
                pacman.move();
                
                //gives pacman a power up, if he deserves it
                if(pacman.getpowerup){
                        pacman.getpowerup = false;
                        givePowerup(&pacman);
                        drawWholeField(&field, &colors);
                        
                }
                
                //moves the enemys
                for(uint8_t i = 0; i < NUMBEROFENEMYS; i++){enemyVector[i].checkvisibility(&pacman); enemyVector[i].move();}
                
                //creates shots
                createShots(&pacman, &shotVector, &enemyVector, &colors);
                
                for(uint8_t i = 0; i < shotVector.size(); i++){shotVector[i].move();}
                
                for(uint8_t i = 0; i < shotVector.size(); i++){if(!shotVector[i].viableShot) shotVector.erase(shotVector.begin()+i);}
                
                //checks if you are dead
                didIdie(&pacman, &enemyVector);
                
                //pacman will show you his stats 
                pacman.showStats();
                
                //just a little break
                this_thread::sleep_for(chrono::milliseconds(30));
                
        }
        gameover(&pacman);
}

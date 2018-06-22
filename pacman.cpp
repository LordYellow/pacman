#include <iostream>
#include "header/map.h"
#include "header/definitions.h"
#include "header/player.h"
#include "header/stuffididnotwrite.h"
#include <array>
#include <map>
#include <unistd.h>
#include <chrono>
#include <thread>

using namespace std;

map<int, string> fieldTextures;

void getColors(){
        fieldTextures[ROADWITHCOIN] = "\033[48;5;7;38;5;2m$ ";
        fieldTextures[ROAD] = "\033[48;5;7m  ";
        fieldTextures[WALL] = "\033[48;5;236m  ";
        fieldTextures[PACMAN] =  "\033[48;5;7;38;5;3mᗤ ";
}

void draw(array<array<uint8_t, WIDTH>, HIGH> field, player pacman){
        system("clear");
        for(int i = 0; i < HIGH; i++){
                for(int a = 0; a < WIDTH; a++){
                        if(field[i][a] == PACMAN){
                             cout << pacman.getsymbol() << "\033[0m";
                        }else{cout << fieldTextures[field[i][a]] << "\033[0m";}
                }
                cout << endl;
        }
}

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
        getColors();
        array<array<uint8_t, WIDTH>, HIGH> field = generateField();
        player pacman(field);
        array<array<uint8_t, WIDTH>, HIGH> *fieldpointer =  &field;
        while(pacman.alive == true){
                draw(field, pacman);
                this_thread::sleep_for(chrono::milliseconds(300));
                eingabe((&pacman));
                pacman.move(fieldpointer);
                
        }
        cout << "GAME OVER" << endl;
        cout << endl << "Score: " << (int)pacman.coins << endl;
        return 0;
}

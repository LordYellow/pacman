#ifndef POWERUP_H
#define POWERUP_H

#include "player.h"
#include <string>
#include "stuffididnotwrite.h"

void powerUpNotification(string effect){
    cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(HIGH/2-1) << ";" << to_string(WIDTH-(effect.length())/2) << "H";
    cout << "╒";
    for(uint8_t i = 0; i < effect.length()+2; i++){cout << "═";}
    cout << "╕" << "\033[0m" << endl;
    cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(HIGH/2) << ";" << to_string(WIDTH-(effect.length())/2) << "H";
    cout << "│ " << effect << " │" << "\033[0m" << endl;
    cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(HIGH/2+1) << ";" << to_string(WIDTH-(effect.length())/2) << "H";
    cout << "╘";
    for(uint8_t i = 0; i < effect.length()+2; i++){cout << "═";}
    cout << "╛" << "\033[0m" << endl;
    while(!_kbhit()){}
}

void giveLife(player *pacman){
    pacman->alive++;
    powerUpNotification("+1 Life!");
}

void giveMovementSpeed(player *pacman){
    if(pacman->baseDelay > 1){
        pacman->baseDelay--;
        powerUpNotification("Movement Speed increased!");
    }else{
        powerUpNotification("Your are as fast as the light!");
    }
}

void giveWallCrushing(player *pacman){
    pacman->crushWalls+=10;
    powerUpNotification("With this Tunfischproteinshake you can Crush this Walls!");
}

void givePowerup(player *pacman){
    switch(rand() % 3){
        case 0: giveLife(pacman); break;
        case 1: giveMovementSpeed(pacman); break;
        case 2: giveWallCrushing(pacman); break;
        default: powerUpNotification("Nothing :("); break; //this will never happen, but just in case...
    }
}

#endif

#ifndef MENUE_H
#define MENUE_H

#include <array>
#include "stuffididnotwrite.h"
#include <thread>

using namespace std;

void loadingscreen(){
    system("clear");
    cout << "\033[38;5;1m";
    cout << "\033[11;20H" << "╒═══════════════════════════╕" << endl;
    cout << "\033[12;20H" << "│  " << "         LOADING       " << "  │" << endl;
    cout << "\033[13;20H" << "╘═══════════════════════════╛" << "\033[0m" << endl;
}


void drawmenue(int Highlighted){
    system("clear");
    array<string, 3> colors = {"\033[38;5;1m","\033[38;5;1m","\033[38;5;1m"};
    colors[Highlighted] = "\033[48;5;7;38;5;1m";
    cout << "\033[10;20H" << "╒═══════════════════════════╕" << "\033[0m" << endl;
    cout << "\033[11;20H" << "│  " << colors[0] << "          PLAY         " << "\033[0m" << "  │" << endl;
    cout << "\033[12;20H" << "│  " << colors[1] << "       HIGHSCORES      " << "\033[0m" << "  │" << endl;
    cout << "\033[13;20H" << "│  " << colors[2] << "          END          " << "\033[0m" << "  │" << endl;
    cout << "\033[14;20H" << "╘═══════════════════════════╛" << "\033[0m" << endl;
}

bool selection(int *Highlighted){
        char c = '!';
        if(_kbhit()){ 
                c = getchar();
        }
        
        switch(c) {
                case 'w': (*Highlighted)--; break; // up
                case 's': (*Highlighted)++; break; // down
                case ' ': return true;
                default: break;
        }
        
        if(*Highlighted == 3){*Highlighted = 0;}
        if(*Highlighted == -1){*Highlighted = 2;}
        return false;
}

bool menue(){
    int Highlighted = 0;
    for(;;){
        drawmenue(Highlighted);
        if(selection(&Highlighted)){
            switch(Highlighted){
                case 0: return false;
                case 1: break; //tbd
                case 2: return true;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(30));
    }
}

#endif

#ifndef MENUE_H
#define MENUE_H

#include <array>
#include "stuffididnotwrite.h"
#include <thread>
#include <fstream>
#include "highscore.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "random.h"

using namespace std;

void gameover(player *pacman){
    cout << "\033[48;5;8;38;5;4m" << "\033[" << to_string(HIGH+5) << ";" << "0" << "H" << "\033[0m" << endl;
    ofstream setHighscore((string(get_current_dir_name()).append("/safefile")), ios::app);
    cout << "GAMEOVER" << endl;
    string name;
    cout << "ENTER YOUR NAME: " << flush;
    getline(cin, name);
    setHighscore << name << endl << (int)pacman->coins << endl;
    setHighscore.close();
}

vector<highscore> getHighscoreVector(ifstream *readHighscores){
    vector<highscore> highscorevector;
    while((*readHighscores).peek() != EOF){
        string name, score; // I think this bad, but i dont habe a better solution at the moment 
        getline(*readHighscores, name);
        getline(*readHighscores, score);
        highscorevector.push_back(highscore(name, (uint)stoi(score)));
    }
    sort(highscorevector.begin(), highscorevector.end());
    reverse(highscorevector.begin(), highscorevector.end()); // I know that this is not the most efficent solution
    return highscorevector;
}

void showHighscores(){
    ifstream readHighscores;
    readHighscores.open((string(get_current_dir_name()).append("/safefile")));
    if(readHighscores.is_open()){
        vector<highscore> scores = getHighscoreVector(&readHighscores);
        system("clear");
        for(uint8_t i = 0; i < scores.size() && i < 5; i++){
            cout << scores[i] << endl;
        }
        cin.get();
        
    }else{
        cout << "You dont Have a Highscore right now. Play the Game!" << endl;
        cin.get();
    }
    readHighscores.close();
}

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
    cout << "\033[13;20H" << "│  " << colors[2] << "      CHANGE SEED      " << "\033[0m" << "  │" << endl;
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

void changeseed(){
    string seedstring;
    cout << "ENTER THE SEED: " << flush;
    getline(cin, seedstring);
    seed = stoi(seedstring);
    
}

void menue(){
    int Highlighted = 0;
    for(;;){
        drawmenue(Highlighted);
        if(selection(&Highlighted)){
            switch(Highlighted){
                case 0: return;
                case 1: showHighscores(); break;
                case 2: changeseed(); break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(30));
    }
}

#endif

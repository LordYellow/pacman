#include <iostream>
#include "header/map.h"
#include "header/definitions.h"
#include "header/player.h"
#include <array>
#include <map>

using namespace std;

map<int, string> fieldTextures;


void getColors(){
  fieldTextures[ROADWITHCOIN] = "\033[48;5;7m##";
  fieldTextures[ROAD] = "\033[48;5;7m  ";
  fieldTextures[WALL] = "\033[48;5;236m  ";
  fieldTextures[PACMAN] =  "\033[48;5;7;38;5;3mᗤ ";
}

void draw(array<array<uint8_t, WIDTH>, HIGH> field){
  for(int i = 0; i < HIGH; i++){
    for(int a = 0; a < WIDTH; a++){
      cout << fieldTextures[field[i][a]] << "\033[0m";
    }
    cout << endl;
  }
}

int main() {
  //pacman tbd
  getColors();
  array<array<uint8_t, WIDTH>, HIGH> field = generateField();
  player pacman(field);
  array<array<uint8_t, WIDTH>, HIGH> *fieldpointer =  &field;
  while(pacman.alive == true){
        draw(field);
  }
  cout << "GAME OVER" << endl;
  cout << endl << "Score: " << (int)pacman.coins << endl;
  return 0;
}

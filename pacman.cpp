#include <iostream>
#include "header/map.h"
#include "header/definitions.h"
#include <array>
#include <map>

using namespace std;

map<int, string> fieldTextures;

void getColors(){
  fieldTextures[ROAD] = "\033[48;5;94m  ";
  fieldTextures[WALL] = "\033[48;5;2m  ";
}

void draw(array<array<uint8_t, WIDTH>, HIGH> field){
  for(int i = 0; i < HIGH; i++){
    for(int a = 0; a < WIDTH; a++){
      cout << fieldTextures[field[i][a]] << "\033[0m";
    }
    cout << endl;
  }
}

int main(int argc, char const *argv[]) {
  //pacman tbd
  getColors();
  array<array<uint8_t, WIDTH>, HIGH> field = generateField();
  draw(field);
  return 0;
}

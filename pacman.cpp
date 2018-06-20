#include <iostream>
#include "header/map.h"
#include "header/definitions.h"
#include <array>
#include <map>

using namespace std;

void draw(array<array<int, WIDTH>, HIGH> field){
  map<int, string> fieldTextures;
  fieldTextures[1] = "\033[48;5;16m  ";
  fieldTextures[2] = "\033[48;5;32m  ";
  for(int i = 0; i < HIGH; i++){
    for(int a = 0; a < WIDTH; a++){
      cout << fieldTextures[field[i][a]];
    }
    cout << endl;
  }
}

int main(int argc, char const *argv[]) {
  //pacman tbd
  array<array<int, WIDTH>, HIGH> field = generateField();
  draw(field);
  return 0;
}

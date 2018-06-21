#ifndef MAP_H
#define MAP_H

#include "definitions.h"
#include <array>
#include <iostream>

using namespace std;

bool possibleParts[12][3][3] = {{{0,1,0},{1,1,0},{0,0,0}},  {{0,1,0},{0,1,1},{0,0,0}},  {{0,0,0},{1,1,0},{0,1,0}},  {{0,0,0},{0,1,1},{0,1,0}},  {{0,1,0},{0,1,0},{0,1,0}},  {{0,0,0},{1,1,1},{0,0,0}},  {{0,1,0},{1,1,0},{0,1,0}},  {{0,1,0},{0,1,1},{0,1,0}},  {{0,1,0},{1,1,1},{0,0,0}},  {{0,0,0},{1,1,1},{0,1,0}},  {{0,1,0},{1,1,1},{0,1,0}}, {{0,0,0},{0,0,0},{0,0,0}}};

void drawfieldparts(array<array<int, WIDTH/3+2>, HIGH/3+2> field){
  for(int i = 0; i < HIGH/3+2; i++){
    for(int a = 0; a < WIDTH/3+2; a++){
      cout << field[i][a] << " ";
    }
    cout << endl;
  }
}


bool partIsPossible(int partNumber, int fieldTop, int fieldLeft, int fieldBottom, int fieldRight){
  if(fieldTop != 12){
    if(!(possibleParts[fieldTop][2][1] == possibleParts[partNumber][0][1])) return false;
  }
  if(fieldLeft != 12){
    if(!(possibleParts[fieldLeft][1][2] == possibleParts[partNumber][1][0])) return false;
  }
  if(fieldBottom != 12){
    if(!(possibleParts[fieldBottom][0][1] == possibleParts[partNumber][2][1])) return false;
  }
  if(fieldRight != 12){
    if(!(possibleParts[fieldRight][1][0] == possibleParts[partNumber][1][2])) return false;
  }
  return true;
}

array<array<int, WIDTH>, HIGH> theFinalField(array<array<int, WIDTH/3+2>, HIGH/3+2> fieldParts){
  array<array<int, WIDTH>, HIGH> field;

  for(int i = 0; i < HIGH; i++){
    for(int a = 0; a < WIDTH; a++){
      field[i][a] = possibleParts[fieldParts[i/3+1][a/3+1]][i % 3][a % 3]+1;
    }
  }

  return field;
}

bool MatchingPartExists(array<array<int, WIDTH/3+2>, HIGH/3+2> fieldParts, int y, int x){
  for(int i = 0; i < 11; i++){
    if(partIsPossible(i, fieldParts[y-1][x], fieldParts[y][x-1], fieldParts[y+1][x], fieldParts[y][x+1])) return true;
  }
  return false;
}

array<array<int, WIDTH>, HIGH> generateField(){
  array<array<int, WIDTH/3+2>, HIGH/3+2> fieldParts;
  srand(time(NULL));

  //clear field
  for(int i = 0; i < HIGH/3+2; i++){
    for(int a = 0; a < WIDTH/3+2; a++){
      fieldParts[i][a] = 12;
    }
  }

  //rand for fieldParts
  for(int i = 0; i < HIGH/3+2; i++){
    fieldParts[i][0] = 11;
    fieldParts[i][WIDTH/3+1] = 11;
  }
  for(int i = 0; i < WIDTH/3+2; i++){
    fieldParts[0][i] = 11;
    fieldParts[HIGH/3+1][i] = 11;
  }

  for(int y = 1; y < HIGH/3+1; y++){
    for(int x = 1; x < WIDTH/3+1; x++){
      int partNumber;
      if(MatchingPartExists(fieldParts, y, x)){
        for(;;){
          partNumber = rand() % 11;
          if(partIsPossible(partNumber, fieldParts[y-1][x], fieldParts[y][x-1], fieldParts[y+1][x], fieldParts[y][x+1])) break;
        }
        fieldParts[y][x] = partNumber;
      }else{
        fieldParts[y][x] = 11;
      }
    }
  }

  drawfieldparts(fieldParts);
  return theFinalField(fieldParts);
}

#endif

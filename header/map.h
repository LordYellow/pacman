#ifndef MAP_H
#define MAP_H

#include "definitions.h"
#include <array>
#include <iostream>

using namespace std;

bool possibleParts[12][3][3] = {{{0,1,0},{1,1,0},{0,0,0}},  {{0,1,0},{0,1,1},{0,0,0}},  {{0,0,0},{1,1,0},{0,1,0}},  {{0,0,0},{0,1,1},{0,1,0}},  {{0,1,0},{0,1,0},{0,1,0}},  {{0,0,0},{1,1,1},{0,0,0}},  {{0,1,0},{1,1,0},{0,1,0}},  {{0,1,0},{0,1,1},{0,1,0}},  {{0,1,0},{1,1,1},{0,0,0}},  {{0,0,0},{1,1,1},{0,1,0}},  {{0,1,0},{1,1,1},{0,1,0}}, {{0,0,0},{0,0,0},{0,0,0}}};

bool roadIsLeft(array<array<int, WIDTH>, HIGH> field){
  for(int y = 0; y < HIGH; y++){
    for(int x = 0; x < WIDTH; x++){
      if(field[y][x] == ROAD) return true;
    }
  }
  return false;
}

bool FieldIsViable(array<array<int, WIDTH>, HIGH> field){

  for(int y = 0; y < HIGH; y++){
    for(int x = 0; x < WIDTH; x++){
      if(field[y][x] == ROAD){
        int neighbourRoadCounter = 0;
        if(field[y+1][x] == 2) neighbourRoadCounter++;
        if(field[y-1][x] == 2) neighbourRoadCounter++;
        if(field[y][x+1] == 2) neighbourRoadCounter++;
        if(field[y][x-1] == 2) neighbourRoadCounter++;
        if(neighbourRoadCounter == 1) return false;
      };
    }
  }

  for(;;){
    int a = rand() % HIGH, b = rand() % WIDTH;
    if(field[a][b] == ROAD){
      field[a][b] = ROAD+1;
      break;
    }
  }

  array<array<int, WIDTH>, HIGH> oldfield = field;
  for(;;){
    oldfield = field;
    for(int y = 0; y < HIGH; y++){
      for(int x = 0; x < WIDTH; x++){
        if(field[y][x] == ROAD+1){
          if(field[y-1][x] == ROAD) field[y-1][x] = ROAD+1;
          if(field[y+1][x] == ROAD) field[y+1][x] = ROAD+1;
          if(field[y][x-1] == ROAD) field[y][x-1] = ROAD+1;
          if(field[y][x+1] == ROAD) field[y][x+1] = ROAD+1;
        }
      }
    }
    if(field == oldfield){
      if(roadIsLeft(field)){return false;}else{return true;}
    };
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
  for(;;){
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

    array<array<int, WIDTH>, HIGH> field = theFinalField(fieldParts);
    if(FieldIsViable(field)) return field;
  }
}

#endif

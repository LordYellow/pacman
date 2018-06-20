#ifndef MAP_H
#define MAP_H

#include "definitions.h"
#include <array>
#include <iostream>

using namespace std;

array<array<int, WIDTH>, HIGH> generateField(){
  array<array<int, WIDTH>, HIGH> field;
  srand(time(NULL));

  //clear field
  for(int i = 0; i < HIGH; i++){
    for(int a = 0; a < WIDTH; a++){
      field[i][a] = 0;
    }
  }

  //add center
  for(int i = HIGH/2-3; i < HIGH/2+3; i++){
    field[i][WIDTH/2-3] = 2;
    field [i][WIDTH/2+3] = 2;
  }
  for(int i = WIDTH/2-3; i < WIDTH/2+3; i++){
    field[HIGH/2-3][i] = 2;
    field [HIGH/2+3][i] = 2;
  }

  //add rand
  for(int i = 0; i < HIGH; i++){
    field[i][0] = 1;
    field [i][WIDTH-1] = 1;
  }
  for(int i = 0; i < WIDTH; i++){
    field[0][i] = 1;
    field [HIGH-1][i] = 1;
  }

  //path
  for(int i = 1; i < HIGH-1; i++){
    for(int a = 1; a < WIDTH-1; a++){
      //count surroundings
      if(field[i+1][a+1] != 2 && field[i-1][a-1] != 2 && field[i+1][a-1] != 2 && field[i-1][a+1] != 2 && field[i][a] == 0){
        int neighbourWallCounter = 0;

        if(field[i+1][a] == 2) neighbourWallCounter++;
        if(field[i-1][a] == 2) neighbourWallCounter++;
        if(field[i][a+1] == 2) neighbourWallCounter++;
        if(field[i][a-1] == 2) neighbourWallCounter++;

        int chance;
        switch (neighbourWallCounter) {
          case 0: chance = 0;
          case 1: chance = 50;
          case 2: chance = 80;
          case 3: chance = 60;
          case 4: chance = 50;
        }
        if((rand() % 100) > chance){
          field[i][a] = 2;
        }else{
          field[i][a] = 1;
        }

      }else{
        field[i][a] = 1;
      }

    }
  }

  //add rand
  for(int i = 0; i < HIGH; i++){
    field[i][0] = 2;
    field [i][WIDTH-1] = 2;
  }
  for(int i = 0; i < WIDTH; i++){
    field[0][i] = 2;
    field [HIGH-1][i] = 2;
  }

  return field;
}

#endif

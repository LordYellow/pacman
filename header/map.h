#ifndef MAP_H
#define MAP_H

#include "definitions.h"
#include "random.h"
#include <array>
#include <iostream>

using namespace std;

bool possibleParts[17][3][3] = {{{0,1,0},{1,1,0},{0,0,0}},  {{0,1,0},{0,1,1},{0,0,0}},  {{0,0,0},{1,1,0},{0,1,0}},  {{0,0,0},{0,1,1},{0,1,0}},  {{0,1,0},{0,1,0},{0,1,0}},  {{0,0,0},{1,1,1},{0,0,0}},  {{0,1,0},{1,1,0},{0,1,0}},  {{0,1,0},{0,1,1},{0,1,0}},  {{0,1,0},{1,1,1},{0,0,0}},  {{0,0,0},{1,1,1},{0,1,0}},  {{0,1,0},{1,1,1},{0,1,0}}, {{0,0,0},{0,0,0},{0,0,0}}, {{0,1,0},{0,1,1},{0,1,1}},  {{0,1,0},{1,1,0},{1,1,0}},  {{0,1,1},{0,1,1},{0,0,0}},  {{1,1,0},{1,1,0},{0,0,0}}, {{1,1,1},{1,1,1},{1,1,1}}};

/**
 * @brief checks if there is a road tile in the field
 * 
 * @param field is the field you wann search for road tiles
 * 
 * @returns true if there is at least 1 road tile
 */
bool roadIsLeft(array<array<uint8_t, WIDTH>, HIGH> field){
  for(uint8_t y = 0; y < HIGH; y++){
    for(uint8_t x = 0; x < WIDTH; x++){
      if(field[y][x] == ROADWITHCOIN) return true;
    }
  }
  return false;
}

/**
 * @brief checks if the field is a viable field
 * 
 * @param field is the field you wanna check
 * 
 * @returns true if the field is viable 
 */
bool FieldIsViable(array<array<uint8_t, WIDTH>, HIGH> field){

  for(uint8_t y = 0; y < HIGH; y++){
    for(uint8_t x = 0; x < WIDTH; x++){
      if(field[y][x] == ROADWITHCOIN){
        uint8_t neighbourRoadCounter = 0;
        if(field[y+1][x] == 2) neighbourRoadCounter++;
        if(field[y-1][x] == 2) neighbourRoadCounter++;
        if(field[y][x+1] == 2) neighbourRoadCounter++;
        if(field[y][x-1] == 2) neighbourRoadCounter++;
        if(neighbourRoadCounter == 1) return false;
      };
    }
  }

  for(;;){
    uint8_t a = myrandom() % HIGH, b = myrandom() % WIDTH;
    if(field[a][b] == ROADWITHCOIN){
      field[a][b] = ROADWITHCOIN+1;
      break;
    }
  }

  array<array<uint8_t, WIDTH>, HIGH> oldfield = field;
  for(;;){
    oldfield = field;
    for(uint8_t y = 0; y < HIGH; y++){
      for(uint8_t x = 0; x < WIDTH; x++){
        if(field[y][x] == ROADWITHCOIN+1){
          if(field[y-1][x] == ROADWITHCOIN) field[y-1][x] = ROADWITHCOIN+1;
          if(field[y+1][x] == ROADWITHCOIN) field[y+1][x] = ROADWITHCOIN+1;
          if(field[y][x-1] == ROADWITHCOIN) field[y][x-1] = ROADWITHCOIN+1;
          if(field[y][x+1] == ROADWITHCOIN) field[y][x+1] = ROADWITHCOIN+1;
        }
      }
    }
    if(field == oldfield){
      if(roadIsLeft(field)){return false;}else{return true;}
    };
  }
}

/**
 * @brief checks if the part is a viable part for the field in the given position 
 * 
 * @param partNumber is the Id of the part
 * @param fieldTop is the Id of the part over the Part you wanna check
 * @param fieldLeft is the Id of the part Left to the Part you wanna check
 * @param fieldRight is the Id of the part Right to the Part you wanna check
 * @param fieldBottom is the Id of the part under the Part you wanna check
 * 
 * @returns true if the part is possible 
 */
bool partIsPossible(uint8_t partNumber, uint8_t fieldTop, uint8_t fieldLeft, uint8_t fieldBottom, uint8_t fieldRight){
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

array<array<uint8_t, WIDTH>, HIGH> theFinalField(array<array<uint8_t, WIDTH/3+2>, HIGH/3+2> fieldParts){
  array<array<uint8_t, WIDTH>, HIGH> field;

  for(uint8_t i = 0; i < HIGH; i++){
    for(uint8_t a = 0; a < WIDTH; a++){
      field[i][a] = possibleParts[fieldParts[i/3+1][a/3+1]][i % 3][a % 3]+1;
    }
  }

  return field;
}

/**
 * @brief checks if there is a Possible part
 * 
 * @param fieldParts is the field of the parts from the field you play on
 * @param y is the y coordinate
 * @param x is the x coordinate
 * 
 * @returns true if there is a possible part
 */
bool MatchingPartExists(array<array<uint8_t, WIDTH/3+2>, HIGH/3+2> fieldParts, uint8_t y, uint8_t x){
  for(uint8_t i = 0; i < 11; i++){
    if(partIsPossible(i, fieldParts[y-1][x], fieldParts[y][x-1], fieldParts[y+1][x], fieldParts[y][x+1])) return true;
  }
  return false;
}

/**
 * @brief generates a field
 * 
 * @returns a field you can play on
 */
array<array<uint8_t, WIDTH>, HIGH> generateField(){
  for(;;){
    array<array<uint8_t, WIDTH/3+2>, HIGH/3+2> fieldParts;
    srand(time(NULL));

    //clear field
    for(uint8_t i = 0; i < HIGH/3+2; i++){
      for(uint8_t a = 0; a < WIDTH/3+2; a++){
        fieldParts[i][a] = 12; //for some reason this must be 12 
      }
    }

    //rand for fieldParts
    for(uint8_t i = 0; i < HIGH/3+2; i++){
      fieldParts[i][0] = 11;
      fieldParts[i][WIDTH/3+1] = 11;
    }
    for(uint8_t i = 0; i < WIDTH/3+2; i++){
      fieldParts[0][i] = 11;
      fieldParts[HIGH/3+1][i] = 11;
    }
    


    for(uint8_t y = 1; y < HIGH/3+1; y++){
      for(uint8_t x = 1; x < WIDTH/3+1; x++){
        uint8_t partNumber;
        if(MatchingPartExists(fieldParts, y, x)){
          for(;;){
            partNumber = myrandom() % 11;
            if(partIsPossible(partNumber, fieldParts[y-1][x], fieldParts[y][x-1], fieldParts[y+1][x], fieldParts[y][x+1])) break;
          }
          fieldParts[y][x] = partNumber;
        }else{
          fieldParts[y][x] = 11;
        }
      }
    }

    fieldParts[(HIGH/3+2)/2-1][(WIDTH/3+2)/2-1] = 16;
    fieldParts[(HIGH/3+2)/2-1][(WIDTH/3+2)/2] = 16;
    fieldParts[(HIGH/3+2)/2][(WIDTH/3+2)/2-1] = 16;
    fieldParts[(HIGH/3+2)/2][(WIDTH/3+2)/2] = 16;
        
    array<array<uint8_t, WIDTH>, HIGH> field = theFinalField(fieldParts);
    if(FieldIsViable(field)){
        for(;;){
            int y = myrandom() % HIGH, x = myrandom() % WIDTH;
            if(field[y][x] == ROADWITHCOIN){
                field[y][x] = PACMAN;
                
                break;
            }
        }
        return field;
    }
  }
}

#endif

#ifndef FIELD_H
#define FIELD_H

#include "definitions.h"
#include <array>

using namespace std;

class field{
public:
    field(array<array<uint8_t, WIDTH>, HIGH> field);
    array<array<uint8_t, WIDTH>, HIGH> Field;
    array<array<bool, WIDTH>, HIGH> bField;
    
    uint8_t getFieldValue(uint8_t y, uint8_t x){return this->Field[y][x];}
    void changeFieldValue(uint8_t y, uint8_t x, uint8_t newValue);
    void resetbField();
};

field::field(array<array<uint8_t, WIDTH>, HIGH> field){
    this->Field = field;
    for(int i = 0; i < HIGH; i++){
                for(int a = 0; a < WIDTH; a++){
                        bField[i][a] = 0;
                }
        }
}

void field::changeFieldValue(uint8_t y, uint8_t x, uint8_t newValue){
    this->bField[y][x] = true;
    this->Field[y][x] = newValue;
}

void field::resetbField(){
    for(int i = 0; i < HIGH; i++){
        for(int a = 0; a < WIDTH; a++){
            bField[i][a] = 0;
        }
    }
}

#endif

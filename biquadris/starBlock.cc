#include "starBlock.h"
#include <iostream>
using namespace std;

starBlock::starBlock() {
    currentRotation = 0;
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", "*"},
        {" ", " ", " ", " "}
        
    };
}

starBlock::~starBlock() {}

void starBlock::clockwise() {};

void starBlock:: counterclockwise() {};

void starBlock::print(){
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 4; ++j){
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> starBlock::getBlock() {
    return this->v;
}

string starBlock::getType() {
    return blockType;
}

starBlock* starBlock::copyBlock() {
    return new starBlock (*this);
}

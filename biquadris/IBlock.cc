#include "IBlock.h"
using namespace std;

IBlock::IBlock() {
    currentRotation = 0;
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {"I", "I", "I", "I"},
        {" ", " ", " ", " "}
    }; 
}

IBlock::~IBlock() {}

void IBlock::clockwise() {
    if (currentRotation == 0) {
        v = {
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {" ", " ", " ", " "}
        };
        currentRotation = 1;
    } else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"I", "I", "I", "I"},
            {" ", " ", " ", " "}
        };
        currentRotation = 0;
    }
}

void  IBlock::counterclockwise() {
   if (currentRotation == 1) {
        v = {
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {"I", " ", " ", " "},
            {" ", " ", " ", " "}
        };
        currentRotation = 0;
    } else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"I", "I", "I", "I"},
            {" ", " ", " ", " "}
        };
        currentRotation = 1;
    } 
}

void IBlock::print() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j){
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> IBlock::getBlock() {
    return this->v;
}

string IBlock::getType() {
    return blockType;
}

IBlock* IBlock::copyBlock() {
    return new IBlock(*this);
}

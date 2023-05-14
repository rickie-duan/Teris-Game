#include "SBlock.h"
using namespace std;


SBlock::SBlock() {
    currentRotation = 0;
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", "S", "S", " "},
        {"S", "S", " ", " "}
    };
}

SBlock::~SBlock() {}

void SBlock::clockwise() {
    if (currentRotation == 0) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"S", " ", " ", " "},
            {"S", "S", " ", " "},
            {" ", "S", " ", " "}
        };
        currentRotation = 1;
    } else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", "S", "S", " "},
            {"S", "S", " ", " "}
        };
        currentRotation = 0;
    }
}

void SBlock::counterclockwise() {
    clockwise();
    clockwise();
    clockwise();
}

void SBlock::print() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> SBlock::getBlock() {
    return this->v;
}

string SBlock::getType() {
    return blockType;
}

SBlock* SBlock::copyBlock() {
    return new SBlock(*this);
}

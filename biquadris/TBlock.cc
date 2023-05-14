#include "TBlock.h"
using namespace std;

TBlock::TBlock() {
    currentRotation = 0;
    v.resize(5);
    for (int i = 0; i < 4; ++i) {
        v.resize(4);
    }
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {"T", "T", "T", " "},
        {" ", "T", " ", " "}
    };
}

TBlock::~TBlock() {}

void TBlock::clockwise() {
    if (currentRotation == 0) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", "T", " ", " "},
            {"T", "T", " ", " "},
            {" ", "T", " ", " "}
        };
        currentRotation = 1;
    } else if (currentRotation == 1) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", "T", " ", " "},
            {"T", "T", "T", " "}
        };
        currentRotation = 2;
    } else if (currentRotation == 2) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"T", " ", " ", " "},
            {"T", "T", " ", " "},
            {"T", " ", " ", " "}
        };
        currentRotation = 3;
    } else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"T", "T", "T", " "},
            {" ", "T", " ", " "}
        };
        currentRotation = 0;
    }
}

void TBlock:: counterclockwise() {
    clockwise();
    clockwise();
    clockwise();
}

void TBlock::print() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> TBlock::getBlock() {
    return this->v;
}

string TBlock::getType() {
    return blockType;
}

TBlock* TBlock::copyBlock() {
    return new TBlock(*this);
}

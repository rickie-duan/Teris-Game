#include "LBlock.h"
using namespace std;

LBlock::LBlock() {
    currentRotation = 0;
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", "L", " "},
        {"L", "L", "L", " "}
    };
}

LBlock::~LBlock() {}

void LBlock::clockwise() {
    if (currentRotation == 0) {
        v = {
                {" ", " ", " ", " "},
                {" ", " ", " ", " "},
                {"L", " ", " ", " "},
                {"L", " ", " ", " "},
                {"L", "L", " ", " "}
            };
        currentRotation = 1;
    } else if (currentRotation == 1) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"L", "L", "L", " "},
            {"L", " ", " ", " "}
        };
        currentRotation = 2;
    } else if (currentRotation == 2) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"L", "L", " ", " "},
            {" ", "L", " ", " "},
            {" ", "L", " ", " "}
        };
        currentRotation = 3;
    } else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", "L", " "},
            {"L", "L", "L", " "}
        };
        currentRotation = 0;
    }
}

void LBlock:: counterclockwise() {
    clockwise();
    clockwise();
    clockwise();
}

void LBlock::print() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> LBlock::getBlock() {
    return this->v;
}

string LBlock::getType() {
    return blockType;
}

LBlock* LBlock::copyBlock() {
    return new LBlock(*this);
}

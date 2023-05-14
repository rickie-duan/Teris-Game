#include "ZBlock.h"
using namespace std;

ZBlock::ZBlock() {
    currentRotation = 0;
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {"Z", "Z", " ", " "},
        {" ", "Z", "Z", " "}
    };
}

ZBlock::~ZBlock() {}

void ZBlock::clockwise() {
    if (currentRotation == 0) {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", "Z", " ", " "},
            {"Z", "Z", " ", " "},
            {"Z", " ", " ", " "}
        };
        currentRotation = 1;
    } else {
        v = {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"Z", "Z", " ", " "},
            {" ", "Z", "Z", " "}
        };
        currentRotation = 0;
    }
}

void ZBlock::counterclockwise() {
    clockwise();
    clockwise();
    clockwise();
}

void ZBlock::print() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> ZBlock::getBlock() {
    return this->v;
}

string ZBlock::getType() {
    return blockType;
}

ZBlock* ZBlock::copyBlock() {
    return new ZBlock(*this);
}

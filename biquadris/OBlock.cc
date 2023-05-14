#include "OBlock.h"
using namespace std;

OBlock::OBlock() {
    currentRotation= 0;
    v.resize(5);
    for (int i = 0; i < 4; ++i) {
        v.resize(4);
    }
    v = {
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {" ", " ", " ", " "},
        {"O", "O", " ", " "},
        {"O", "O", " ", " "}
    };
}

OBlock::~OBlock() {}

void OBlock::clockwise() {}

void OBlock:: counterclockwise() {}

void OBlock::print() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

vector<vector <string>> OBlock::getBlock() {
    return this->v;
}

string OBlock::getType() {
    return blockType;
}

OBlock* OBlock::copyBlock() {
    return new OBlock(*this);
}

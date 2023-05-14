#include "Level0.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
using namespace std;

extern string seqName1;
extern string seqName2;
extern int seedn;

Level0::Level0() {
    level = 0;
    ifstream f1{seqName1};
    ifstream f2{seqName2};
    string s;
    while (f1 >> s) {
        List1.emplace_back(s);
    }
    string ss;
    while (f2 >> ss) {
        List2.emplace_back(ss);
    }
    index1 = 0;
    index2 = 0;
}

Level0::~Level0() {}

shared_ptr<Block> Level0::generate_Block(std::shared_ptr<Player> p) {
    shared_ptr<Block> nextblock = nullptr;
    char c;
    if (p->id == 1) {
        if (index1 > List1.size() - 1) {
            index1 = 0;
        }
        c = List1[index1][0];
        ++index1;
    } else {
        if (index2 > List2.size() - 1) {
            index2 = 0;
        }
        c = List2[index2][0];
        ++index2;
    }
    switch(c) {
        case 'I' : nextblock = make_shared<IBlock>();break;
        case 'J' : nextblock = make_shared<JBlock>();break;
        case 'L' : nextblock = make_shared<LBlock>();break;
        case 'O' : nextblock = make_shared<OBlock>();break;
        case 'S' : nextblock = make_shared<SBlock>();break;
        case 'Z' : nextblock = make_shared<ZBlock>();break;
        case 'T' : nextblock = make_shared<TBlock>();break;
            
    }
    return nextblock;
}

void Level0::AddSeqFile(std::string filename,int id) {}

void Level0::setRandom(int id) {}

#include "Level2.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

Level2::Level2() {
    level = 2;
    index1 = 0;
    index2 = 0;
    srand(seedn);
    for (int i = 0 ; i < 4 ; i++ ) {
        List1.emplace_back(rand() % 7 + 1);
    }
    for (int i = 0 ; i < 4 ; i++ ) {
        List2.emplace_back(rand() % 7 + 1);
    }
}

Level2::~Level2() {};

shared_ptr<Block> Level2::generate_Block(std::shared_ptr<Player> pler) {
    shared_ptr<Block> nextblock = nullptr;
    int rm = 1;

    if (pler->id == 1) {
        if (index1 > List1.size() - 1) {
            index1 = 0;
        }
        rm = List1[index1];
        ++index1;
    } else {
        if (index2 > List2.size() - 1) {
            index2 = 0;
        }
        rm = List2[index2];
        ++index2;
    }
    switch (rm) {
        case 1: nextblock = make_shared<IBlock>(); break;
        case 2: nextblock = make_shared<JBlock>(); break;
        case 3: nextblock = make_shared<LBlock>(); break;
        case 4: nextblock = make_shared<OBlock>(); break;
        case 5: nextblock = make_shared<SBlock>(); break;
        case 6: nextblock = make_shared<ZBlock>(); break;
        case 7: nextblock = make_shared<TBlock>(); break;
    }
    return nextblock;
}

void Level2::AddSeqFile(std::string filename,int id) {}

void Level2::setRandom(int id) {}

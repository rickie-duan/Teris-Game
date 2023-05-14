#include "Level4.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
using namespace std;

Level4::Level4() {
    level = 4;
    player1_random = true;
    player2_random = true;
    index1 = 0;
    index2 = 0;
    srand(seedn);
}

Level4::~Level4() {};

void Level4::AddSeqFile(std::string filename, int id) {
    string s;
    if (id == 1) {
        ifstream f1{filename};
        while (f1 >> s) {
            List1.emplace_back(s);
        }
        player1_random = false;
    } else {
        ifstream f2{filename};
        while (f2 >> s) {
            List2.emplace_back(s);
        }
        player2_random = false;
    }
}

shared_ptr<Block> Level4::generate_Block(std::shared_ptr<Player> pler) {
    shared_ptr<Block> nextblock = nullptr;
    bool random = false;
    if ((pler->id == 1) && player1_random) {
        random = true;
    } 
    if ((pler->id == 2) && player2_random) {
        random = true;
    }
    if (random) {
        int r = 1 + rand() % 9;
        if (r == 1 || r == 2) {
            nextblock = make_shared<SBlock>();
        } else if (r == 3 || r == 4) {
            nextblock = make_shared<ZBlock>();
        } else if (r == 5) {
            nextblock = make_shared<IBlock>();
        } else if (r == 6) {
            nextblock = make_shared<JBlock>();
        } else if (r == 7) {
            nextblock = make_shared<LBlock>();
        } else if (r == 8) {
            nextblock = make_shared<OBlock>();
        } else if (r == 9) {
            nextblock = make_shared<TBlock>();
        }
    } else {
        char c;
        if (pler->id == 1) {
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
            case 'J' : nextblock = make_shared<JBlock>(); break;
            case 'O' : nextblock = make_shared<OBlock>(); break;
            case 'L' : nextblock = make_shared<LBlock>(); break;
            case 'I' : nextblock = make_shared<IBlock>(); break;
            case 'S' : nextblock = make_shared<SBlock>(); break;
            case 'Z' : nextblock = make_shared<ZBlock>(); break;
            case 'T' : nextblock = make_shared<TBlock>(); break;
        }
    }
    return nextblock;
}

void Level4::setRandom(int id) {
    if (id == 1) {
        player1_random = true;
    } else if (id == 2) {
        player2_random = true;
    }
}

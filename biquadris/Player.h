#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Block.h"
#include "Grid.h"
#include "GameLevel.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "subject.h"

struct Player: public Subject {
    
    std::vector <std::vector <Grid>> Field;
    int id;
    int score;
    int curLev;
    int row, col;
    bool lPossible = true;
    bool rPossible = true;
    bool dPossible = true;
    bool clockPossible;
    bool counterCPossible;
    int downImpossible;
    std::unique_ptr<GameLevel> levptr;
    std::shared_ptr<Block> curBlock;
    std::shared_ptr<Block> nextBlock;
    
    bool Active;
    
    // keep track for Heavy
    bool heavy;
    
    // Tracker for lvl 4
    int notclear = 0;
    bool starblock = false;
    void notifyObservers() override {
        for (auto &ob : observers) {
        ob->notify(std::shared_ptr<Player>(this));
        }
    }
};

#endif

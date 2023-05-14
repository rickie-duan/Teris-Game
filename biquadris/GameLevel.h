#ifndef __GAMELEVEL_H__
#define __GAMELEVEL_H__
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "Block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"
#include "starBlock.h"

struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedn;

class GameLevel {

public:
    int level;
    virtual std::shared_ptr<Block> generate_Block(std::shared_ptr<Player>) = 0;
    virtual ~GameLevel() = 0;
    virtual void AddSeqFile(std::string,int) = 0;
    virtual void setRandom(int) = 0;

};

#endif

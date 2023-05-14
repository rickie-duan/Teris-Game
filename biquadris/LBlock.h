#ifndef __LBLOCK_H__
#define __LBLOCK_H__
#include "Block.h"

class LBlock : public Block {

    std::string blockType = "L";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;

public:
    LBlock();
    ~LBlock();
    void clockwise() override;
    void counterclockwise() override;
    void print () override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType () override;
    LBlock* copyBlock () override;
    
};

#endif

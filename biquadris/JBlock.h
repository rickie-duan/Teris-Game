#ifndef __JBLOCK_H__
#define __JBLOCK_H__
#include "Block.h"

class JBlock : public Block {

    std::string blockType = "J";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;

public:
    JBlock();
    ~JBlock();
    void clockwise() override;
    void counterclockwise() override;
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType() override;
    JBlock* copyBlock() override;
    
};

#endif

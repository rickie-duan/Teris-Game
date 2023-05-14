#ifndef __STARBLOCK_H__
#define __STARBLOCK_H__
#include "Block.h"

class starBlock : public Block{

    std::string blockType = "*";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;
    
public:
    starBlock();
    ~starBlock();
    void clockwise() override;
    void counterclockwise() override;
    void print () override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType () override;
    starBlock* copyBlock() override;

};

#endif

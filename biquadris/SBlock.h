#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include "Block.h"

class SBlock: public Block {

    std::string blockType = "S";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;
    
public:
    SBlock();
    ~SBlock();
    void clockwise() override;
    void counterclockwise() override;
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType() override;
    SBlock* copyBlock() override;
    
};

#endif 

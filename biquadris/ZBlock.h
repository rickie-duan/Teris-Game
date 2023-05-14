#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include "Block.h"

class ZBlock: public Block {

    std::string blockType = "Z";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;
    
public:
    ZBlock();
    ~ZBlock();
    void clockwise() override;
    void counterclockwise() override;
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType () override;
    ZBlock* copyBlock() override;

};

#endif

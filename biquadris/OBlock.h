#ifndef __OBLOCK_H__
#define __OBLOCK_H__
#include "Block.h"

class OBlock : public Block {

    std::string blockType = "O";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;
    
public:
    OBlock();
    ~OBlock();
    void clockwise() override;
    void  counterclockwise() override;
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType() override;
    OBlock* copyBlock() override;
    
};

#endif

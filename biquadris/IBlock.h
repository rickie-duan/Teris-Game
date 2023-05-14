#ifndef __IBLOCK_H__
#define __IBLOCK_H__
#include "Block.h"


class IBlock : public Block{
    
    std::string blockType = "I";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;

public:
    IBlock();
    ~IBlock();
    void clockwise() override;
    void counterclockwise() override;
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType() override;
    IBlock* copyBlock() override;

};

#endif

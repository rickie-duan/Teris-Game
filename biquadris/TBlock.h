#ifndef __TBLOCK_H__
#define __TBLOCK_H__
#include "Block.h"

class TBlock : public Block{

    std::string blockType = "T";
    int currentRotation;

protected:
    std::vector<std::vector <std::string>> v;

public:
    TBlock();
    ~TBlock();
    void clockwise() override;
    void counterclockwise() override;
    void print() override;
    std::vector<std::vector <std::string>> getBlock() override;
    std::string getType () override;
    TBlock* copyBlock() override;

};

#endif

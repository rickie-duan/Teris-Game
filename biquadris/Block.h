#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <string>
#include <vector>
#include <memory>
#include <iostream>


class Block {
protected:
    std::vector<std::vector <std::string>> v;

public:
    bool unmodified = true;
    Block();
    Block(const Block& b);
    Block &operator=(const Block& b);
    virtual ~Block();
    virtual void clockwise() = 0;
    virtual void counterclockwise() = 0;
    virtual void print() = 0;
    virtual std::vector<std::vector <std::string>> getBlock() = 0;
    virtual std::string getType() = 0;
    virtual Block* copyBlock() = 0;
    std::shared_ptr<Block> blockCopy();
    
};

#endif

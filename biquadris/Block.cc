#include "Block.h"
using namespace std;

Block::Block () {}

Block::Block(const Block& b) {
    v = b.v;
}

Block &Block::operator=(const Block& other) {
    if (this == &other) {
        return *this;
    } else {
        v = other.v;
        return *this;
    }
}

shared_ptr<Block> Block::blockCopy() {
    return std::shared_ptr<Block> (this->copyBlock());
}

Block::~Block() {}

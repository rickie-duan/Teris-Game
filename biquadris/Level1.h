#ifndef __LEVEL1_H__
#define __LEVEL1_H__
#include "GameLevel.h"

struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedn;

class Level1 : public GameLevel {
    size_t index1;
    size_t index2;
    std::vector<int> List1;
    std::vector<int> List2;
    
public:
    Level1();
    std::shared_ptr<Block> generate_Block(std::shared_ptr<Player>) override;
    ~Level1();
    void AddSeqFile(std::string,int) override;
    void setRandom(int) override;
};

#endif 

#ifndef __LEVEL2_H__
#define __LEVEL2_H__
#include "GameLevel.h"

struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedn;

class Level2 : public GameLevel {
    size_t index1;
    size_t index2;
    std::vector<int> List1;
    std::vector<int> List2;
    
public:
    Level2();
    ~Level2();
    std::shared_ptr<Block> generate_Block(std::shared_ptr<Player>) override;
    void AddSeqFile(std::string,int) override;
    void setRandom(int) override;

};

#endif 

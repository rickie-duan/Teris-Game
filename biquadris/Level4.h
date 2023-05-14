#ifndef __LEVEL4_H__
#define __LEVEL4_H__
#include "GameLevel.h"

struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedn;

class Level4 : public GameLevel {
    
    size_t index1;
    size_t index2;
    bool player1_random;
    bool player2_random;
    std::vector<std::string> List1;
    std::vector<std::string> List2;

public:
    Level4();
    std::shared_ptr<Block> generate_Block(std::shared_ptr<Player>) override;
    ~Level4();
    void AddSeqFile(std::string,int) override;
    void setRandom(int) override;

};

#endif 

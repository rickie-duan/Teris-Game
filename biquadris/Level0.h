#ifndef __LEVEL0_H__
#define __LEVEL0_H__
#include "GameLevel.h"

struct Player;
extern std::string seqName1;
extern std::string seqName2;
extern int seedn;

class Level0 : public GameLevel{

    size_t index1;
    size_t index2;
    std::vector<std::string> List1;
    std::vector<std::string> List2;
    
public:
    Level0();
    ~Level0();
    std::shared_ptr<Block> generate_Block(std::shared_ptr<Player>) override;
    void AddSeqFile(std::string,int) override;
    void setRandom(int) override;

};

#endif 

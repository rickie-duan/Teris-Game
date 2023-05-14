#ifndef __BOARD_H__
#define __BOARD_H__
#include "Player.h"
#include "Grid.h"
#include "Window.h"
#include "Block.h"
#include "subject.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

struct Player;

class Board : public Subject {

    std::shared_ptr <Player> player1;
    std::shared_ptr <Player> player2;

public:
    Board ();
    ~Board ();
    int hi = 0;
    void setPlayer(std::shared_ptr <Player>& player, int id,int level);
    std::shared_ptr <Player>& getPlayer1();
    std::shared_ptr <Player>& getPlayer2();
    int getScore(std::shared_ptr <Player>& player);
    void notifyObservers() override;
    
    // method
    bool availableGrid(std::shared_ptr <Player>& player, int x, int y);
    bool turn = true;
    std::shared_ptr <Player>& curPlayer();
    std::shared_ptr <Player>& nextPlayer();
    void switchPlayer();

    void left(std::shared_ptr <Player>& player);
    void right(std::shared_ptr <Player>& player);
    void down(std::shared_ptr <Player>& player);
    void drop(std::shared_ptr <Player>& player);
    void rotateCW(std::shared_ptr <Player>& player);
    void rotateCCW(std::shared_ptr <Player>& player);
    void updatePossible(std::shared_ptr <Player>& player);
    
    int recalculate(std::shared_ptr <Player>& player);
    void destroyLine(std::shared_ptr <Player>& player, std::vector<int> &clean_row);
    void levelUp(std::shared_ptr <Player>& player);
    void levelDown(std::shared_ptr <Player>& player);
    void deadGrid(std::shared_ptr <Player>& player);
    void levelHeavy(std::shared_ptr <Player>& player);
    void blockheavy(std::shared_ptr <Player>& player);
    void blind(std::shared_ptr <Player>& player);
    bool gameOver(std::shared_ptr <Player>& player);
    void restart(std::shared_ptr <Player>& player1, std::shared_ptr <Player>& player2);
};

#endif

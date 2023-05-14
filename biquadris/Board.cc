#include "Board.h"
#include "Player.h"
#include "subject.h"
#include <iostream>
#include <sstream>
#include <string>

extern bool specialOn;
using namespace std;

Board::Board () {
    player1 = shared_ptr <Player> (new Player);
    player2 = shared_ptr <Player> (new Player);
    hi = 0;
}

Board::~Board() {}

void Board::setPlayer(shared_ptr <Player> &player, int id,int curLev) {
    player->Field.resize(15);
    for (int row = 0; row < 15; row++) {
        player->Field[row].resize(11);
        for (int col = 0; col < 11; col++) {
            player->Field[row][col] = Grid();
        }
    }
    if (curLev == 0) {
        player->levptr = unique_ptr <GameLevel> (new Level0);
    } 
    if (curLev == 1) {
        player->levptr = unique_ptr <GameLevel> (new Level1);
    }
    if (curLev == 2) {
        player->levptr= unique_ptr <GameLevel> (new Level2);
    }
    if (curLev == 3) {
        player->levptr= unique_ptr <GameLevel> (new Level3);
    }
    if (curLev == 4) {
        player->levptr= unique_ptr <GameLevel> (new Level4);
    } 
    
    player->id = id;
    player->rPossible = true;
    player->dPossible = true;
    player->lPossible = true;
    player->heavy = false; 
    player->Active = true;
    player->clockPossible = true;
    player->counterCPossible = true;

    player->curBlock = nullptr;
    player->nextBlock = nullptr;

    player->curLev = curLev;

    player->col = 0;
    player->row = 0;
    player->score= 0;
    player->downImpossible = 0;

}

int Board::getScore(shared_ptr <Player>& player) {
    return player->score;
}

shared_ptr <Player>& Board::getPlayer2() {
    return player2;
}

shared_ptr <Player>& Board::getPlayer1() {
    return player1;
    
}

void Board::notifyObservers() {
    for (auto &ob : observers) {
        ob->notify(*this);
    }
}

shared_ptr <Player>& Board::curPlayer() {
    if (turn) {
        return player1;
    }else{
        return player2;
    }
}

shared_ptr <Player>& Board::nextPlayer() {
    if (turn) {
        return player2;
    } else {
        return player1;
    }
}

void Board::switchPlayer() {
    turn = !turn;
}

// command left
void Board::left(shared_ptr <Player>& player) {
    int pc = player->col;
    if ((pc > 0) && (player->lPossible)) {
        player->rPossible = true;
        player->dPossible = true;
        player->col -= 1;
    }
    else {
        player->dPossible = true;
        player->lPossible = true;
        player->rPossible = true;
    }
    player->clockPossible = true;
    player->counterCPossible = true;
}


// command right
void Board::right(shared_ptr <Player>& player) {
    int pc = player->col;
    int rc = 0;
    int bc = 11;
    for (int row = 0; row < 5; ++ row) {
        for (int col = 0; col < 4; ++col) {
            vector <vector <string>> v = player->curBlock->getBlock();
            if ((v[row][col] != " ")&&(col > rc)) {
                rc = col;
            }
        }
    }
    
    if ((pc + rc + 2 <= bc) && (player->rPossible)) {
        player->col += 1;
        player->lPossible = true;
        player->dPossible = true;
    }
    else if (!player->rPossible) {
        player->rPossible = true;
        player->lPossible = true;
        player->dPossible = true;
    }
    player->clockPossible = true;
    player->counterCPossible = true;
}


// command down
void Board::down(shared_ptr <Player>& player) {
    int player_row = player->row;
    if (!player->dPossible) {
        ++player->notclear;//
        //  cout << "can't down" << endl;
        player->downImpossible += 1;
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 11; ++j) {
                player->Field[i][j].NotBlind();
            }
        }
    }
    
    if ((player_row < 15)&&(player->dPossible)) {
        player->row += 1;
        player->rPossible = true;
        player->lPossible = true;
    } else {
        player->rPossible = true;
        player->lPossible = true;
        player->dPossible = true;
    }
    player->clockPossible = true;
    player->counterCPossible = true;
}


// drop
void Board::drop(shared_ptr <Player>& player) {
    while (player->downImpossible == 0) {
        updatePossible(player);
        down(player);
        updatePossible(player);
    }
}


// clockwise rotate
void Board::rotateCW(shared_ptr <Player>& player) {
    int x = player->row;
    int y = player->col;
    int b_row = 5;
    int b_col = 4;
    int board_row = 15;
    int bc = 11;
    shared_ptr<Block>copy = player->curBlock->blockCopy();
    copy->clockwise();
    string blockType = copy->getType();
    
    for (int row = 0; row < b_row; ++ row) {
        for (int col = 0; col < b_col; ++ col) {
            
            int new_row = row + x;
            int new_col = col + y;
            if ((new_col >= 11) && (blockType == "I")) {
                player->clockPossible = false;
                break;
            }
            if ((new_col > 11) && (blockType != "I")) {
                player->clockPossible = false;
                break;
            }
            vector <vector <string>> v_copy = copy->getBlock();
            string cwcolor = v_copy[row][col];
            if ((new_col >= bc)||(new_row >= board_row)||(cwcolor == " ")) {
                continue;
            }

            if (player->Field[new_row][new_col].GetColor() != " ") {
                player->clockPossible = false;
                break;
            }
        }
    }
}


// counterclockwise rotation
void Board::rotateCCW(shared_ptr <Player>& player) {
    int x = player->row;
    int y = player->col;
    int b_row = 5;
    int b_col = 4;
    int board_row = 15;
    int bc = 11;
    shared_ptr<Block>copy = player->curBlock->blockCopy();
    copy->counterclockwise();
    string blockType = copy->getType();
    
    for (int row = 0; row < b_row; ++ row) {
        for (int col = 0; col < b_col; ++ col) {
            int new_row = row + x;
            int new_col = col + y;
            if ((new_col >= 11) && (blockType == "I")) {
                player->counterCPossible = false;
                break;
            }
            if ((new_col > 11) && (blockType != "I")) {
                player->counterCPossible = false;
                break;
            }
            
            vector <vector <string>> v_copy = copy->getBlock();
            string cwcolor = v_copy[row][col];
            
            if ((new_col >= bc)||(new_row >= board_row)||(cwcolor == " ")) {
                continue;
            }
            
            if (player->Field[new_row][new_col].GetColor() != " ") {
                player->counterCPossible = false;
                break;
            }
        }
    }
}




void Board::updatePossible(shared_ptr <Player>& player) {
    int x = player->row;
    int y = player->col;
    int b_row = 5;
    int b_col = 4;
    int board_row = 15;
    int bc = 11;
    int check_row = 0;
    vector <vector <string>> v = player->curBlock->getBlock();
    
    for (int row = 0; row < b_row; ++ row) {
        check_row = 0;
        for (int col = 0; col < b_col; ++ col) {
            int new_row = row + x;
            int new_col = col + y;
            string color = v[row][col];
            if ((new_col >= bc)||(new_row >= board_row)||(color == " ")) {
                continue;
            } else {
                if ((new_col+1 > 10)||(player->Field[new_row][new_col+1].GetColor() != " ")) {
                    player->rPossible = false;
                }
                if (check_row == 0) {
                    check_row += 1;
                    if ((new_col -1 < 0)|| (player->Field[new_row][new_col-1].GetColor() != " ")) {
                        player->lPossible = false;
                    }
                }
                if ((new_row+1 >= 15) || (player->Field[new_row+1][new_col].GetColor() != " ")) {
                    player->dPossible = false;
                }                
            }
        }
    }
    rotateCW(player);
    rotateCCW(player);
}

// checking if lines are filled
int Board::recalculate(shared_ptr <Player>& player) {
    vector < int > clean_row;
    for (int row = 14; row > 0 ; row--) {
        int num_dead_grid = 0;
        for (int col = 0; col < 11; ++col) {
            if (player->Field[row][col].GetColor() == " ") {
                continue;
            }
            else if ((!(player->Field[row][col].GetColor() == " "))&&(!player->Field[row][col].isActive())) {
                num_dead_grid += 1;
            }
            if (num_dead_grid == 11) {
                clean_row.push_back(row);
            }
        }
    }
    // score
    int a = clean_row.size();
    if (clean_row.size() != 0) {
        destroyLine(player, clean_row);
    }
    return a;
}


// adding score and destroying lines
void Board::destroyLine(shared_ptr <Player>& player,  vector< int > & clean_row) {
    vector < vector <Grid> > new_Field;
    int num_clean_row = clean_row.size();
    int x = 0;
    new_Field.resize(15);
    
    for (int row = 0; row < num_clean_row; row++) {
        new_Field[row].resize(11);
        for (int col = 0; col < 11; col++) {
            new_Field[row][col] = Grid();
            
        }
    }
    
    for (int row = 0; row < 15; row++) {
        if (row + x >= 15) {
            break;
        }
        if (clean_row.back() == row) {
            clean_row.pop_back();
            x += 1;
            continue;
        } else {
            new_Field[row + num_clean_row - x].resize(11);            
            for (int col = 0; col < 11; col++) {
                new_Field[row + num_clean_row - x][col] = player->Field[row][col];
            }
        }
    }
    
    int add_score = (num_clean_row + player->curLev)*(num_clean_row + player->curLev);
    cout << num_clean_row << endl;
    cout << player->curLev << endl;
    
    player->Field = new_Field;
    player->score += add_score;
    if (player->score > hi) {
        hi = player->score;
    }
}

// leveling up and down
void Board::levelUp(shared_ptr <Player>& player) {
    int le = player->curLev + 1;
    if (le == 1) {
        player->levptr= unique_ptr <GameLevel> (new Level1);
        player->curLev = 1;
        player->starblock = false;
    } else if (le == 2) {
        player->levptr= unique_ptr <GameLevel> (new Level2);
        player->curLev = 2;
        player->starblock = false;
    } else if (le == 3) {
        player->levptr= unique_ptr <GameLevel> (new Level3);
        player->curLev = 3;
        player->starblock = false;
    } else if (le == 4) {
        player->levptr= unique_ptr <GameLevel> (new Level4);
        player->curLev = 4;
        player->starblock = true;
    }
}

void Board::levelDown(shared_ptr <Player>& player) {
    int le = player->curLev - 1;
    if (le == 1) {
        player->levptr= unique_ptr <GameLevel> (new Level1);
        player->curLev = 1;
        player->starblock = false;
    } else if (le == 2) {
        player->levptr= unique_ptr <GameLevel> (new Level2);
        player->curLev = 2;
        player->starblock = false;  
    } else if (le == 3) {
        player->levptr= unique_ptr <GameLevel> (new Level3);
        player->curLev = 3;
        player->starblock = false;
    }  else if (le == 4) {
        player->levptr= unique_ptr <GameLevel> (new Level4);
        player->curLev = 4;
        player->starblock = true;
    } else if (le == 0) {
        player->levptr= unique_ptr <GameLevel> (new Level0);
        player->curLev = 0;
        player->starblock = false;
    }
}

void Board::deadGrid(shared_ptr <Player>& player) {
    for (int row = 0; row < 15; ++row){
        for (int col = 0; col < 11; ++col){
            Grid cur = player->Field[row][col];
            if (cur.isActive()){
                player->Field[row][col].Deactivate(" ");
            }
        }
    }
}

// Heavy
void Board::levelHeavy(shared_ptr <Player>& player) {
    if ((player->curBlock->unmodified == false) && (player->downImpossible == 0) && (player->curLev >= 3)) {
        updatePossible(player);
        down(player);
        updatePossible(player);
    }
}

void Board::blockheavy(shared_ptr <Player>& player) {
    for (int i = 0; i < 2; ++i) {
        if ((player->downImpossible == 0)&&(player->heavy)) {
            updatePossible(player);
            down(player);
            updatePossible(player);
        }
    }
}

// game over
bool Board::gameOver(shared_ptr <Player>& player) {
    string check0 = player->Field[3][0].GetColor(); 
    string check1 = player->Field[3][1].GetColor();
    string check2 = player->Field[3][2].GetColor();
    string check3 = player->Field[3][3].GetColor();
    string checkone0 = player->Field[4][0].GetColor();
    string checkone1 = player->Field[4][1].GetColor();
    string checkone2 = player->Field[4][2].GetColor();
    string checkone3 = player->Field[4][3].GetColor();
    bool check0bool = player->Field[3][0].isActive();
    bool check1bool = player->Field[3][1].isActive();
    bool check2bool = player->Field[3][2].isActive();
    bool check3bool = player->Field[3][3].isActive();
    bool checkone0bool = player->Field[4][0].isActive();
    bool checkone1bool = player->Field[4][1].isActive();
    bool checkone2bool = player->Field[4][2].isActive();
    
   if ((player->nextBlock->getType() == "I")&&
        (((check0 != " ") && (!check0bool)) || ((check1 != " ") && (!check1bool)) || ((check2 != " ") && (!check2bool)) || ((check3 != " ") && (!check3bool)))) {
        return false;
    }
    if ((player->nextBlock->getType() == "O")&&
        (((check0 != " ") && (!check0bool))||((check1 != " ") && (!check1bool))||((checkone0 != " ") && (!checkone0bool))||((checkone1 != " ") && (!checkone1bool)))) {
        return false;
    }
    if ((player->nextBlock->getType() == "T")&&(((check1 != " ") && (!check1bool)) || ((checkone0 != " ") && (!checkone0bool)) || ((checkone1 != " ") && (!checkone1bool)) || ((checkone2 != " ") && (!checkone2bool)))) {
        return false;
    }
    if ((player->nextBlock->getType() == "L")&&(((check3 != " ") && (!check3bool))||((checkone0 != " ") && (!checkone0bool))||((checkone1 != " ") && (!checkone1bool))||((checkone2 != " ") && (!checkone2bool)))) {
        return false;
    }
    if ((player->nextBlock->getType() == "J")&&(((check0 != " ") && (!check0bool))||((checkone0 != " ") && (!checkone0bool))||((checkone1 != " ") && (!checkone1bool))||((checkone2 != " ") && (!checkone2bool)))) {
        return false;
    }
    if ((player->nextBlock->getType() == "Z") &&(((check0 != " ") && (!check0bool))||((check1 != " ") && (!check1bool))||((checkone1 != " ") && (!checkone1bool))||((checkone2 != " ") && (!checkone2bool)))) {
        return false;
    }
    if ((player->nextBlock->getType() == "S") &&(((check1 != " ") && (!check1bool))||((check2 != " ") && (!check2bool))||((checkone0 != " ") && (!checkone0bool))||((checkone1 != " ") && (!checkone1bool)))) {
        return false;
    }
    return true;
}

//To restart the game
void Board::restart(shared_ptr <Player>& player1, shared_ptr <Player>& player2) {
    setPlayer(player1, 1, 0);
    setPlayer(player2, 2, 0);
}

// blind
void Board::blind(shared_ptr <Player>& player) {
    for (int i = 2; i < 12; ++i) {
        for (int j = 2; j < 9; ++j) {
            player->Field[i][j].TurnBlind();
        }
    }
}

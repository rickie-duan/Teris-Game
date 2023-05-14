#include <iostream>
#include "textdisplay.h"
using namespace std;

void TextDisplay::notify(Board& whoNotified) {
    std::shared_ptr <Player> player1 = whoNotified.getPlayer1();
    std::shared_ptr <Player> player2 = whoNotified.getPlayer2();
    cout << endl;
    cout << "Level:    " << player1->curLev << "     " << "Level:    " << player2->curLev << endl;
    cout << "Score:    " << player1->score << "     " << "Score:    " << player2->score << endl;
    cout << "-----------     -----------" << endl;
    for (int row = 0; row < 15; row++) {
        for (int col1 = 0; col1 < 11; col1++) {
            cout << player1->Field[row][col1];
        }
        cout << "     ";
        for (int col2 = 0; col2 < 11; col2++) {
            cout << player2->Field[row][col2];
        }
        cout << endl;
    }
    cout << "-----------     -----------" << endl;
    cout << "Next:           Next:      " << endl;
    shared_ptr<Block> p1 = player1->nextBlock;
    shared_ptr<Block> p2 = player2->nextBlock;
    vector<vector<string>> b1 = p1->getBlock();
    vector<vector<string>> b2 = p2->getBlock();
    
    for (int i = 2; i < 5; ++i){
        for (int j = 0; j < 4; ++j){
            cout << b1[i][j];
        }
        cout << "            ";
        for (int j = 0; j < 4; ++j){
            cout << b2[i][j];
        }
        cout << endl;
    }
    cout << "Type in your next move!" << endl;
}

// check is down is possible
static bool checkaval(shared_ptr <Player>& player, int x, int y) {
    int b_row = 5;
    int b_col = 4;
    int board_row = 15;
    int bc = 11;
    vector <vector <string>> v = player->curBlock->getBlock();
    for (int row = 0; row < b_row; ++ row) {
        for (int col = 0; col < b_col; ++ col) {
            int new_row = row + x;
            int new_col = col + y;
            string color = v[row][col];
            if ((new_col >= bc)||(new_row >= board_row)||(color == " ")) {
                continue;
            }
            else if (player->Field[new_row][new_col].GetColor() != " "){
                return false;
                break;
            }
        }
    }
    return true;
}

bool TextDisplay::notify(shared_ptr <Player> whoNotified) {
    shared_ptr <Player> player = whoNotified;
    int x = player->row;
    int y = player->col;
    int b_row = 5;
    int b_col = 4;
    int board_row = 15;
    int bc = 11;
    bool ava = checkaval(player, x, y);
    vector <vector <string>> v = player->curBlock->getBlock();
    
    for (int row = 0; row < b_row; ++ row) {
        for (int col = 0; col < b_col; ++ col) {
            int new_row = row + x;
            int new_col = col + y;
            string color = v[row][col];
            if ((new_col >= bc)||(new_row >= board_row)||(color == " ")) {
                continue;
            }
            else {
                if (player->downImpossible == 1) {
                    player->Field[new_row][new_col].Deactivate(color);
                    continue;
                }
                if (ava){
                    player->Field[new_row][new_col].Activate(color);
                }
            }
        }
    }

    if (player->downImpossible == 1) {
        player->downImpossible = 0;
        player->col = 0;
        player->row = 0;
        player->curBlock = player->nextBlock;
        player->rPossible = true;
        player->lPossible = true;
        player->dPossible = true;
        player->clockPossible = true;
        player->counterCPossible = true;
        return true;
    }
    return false;
}

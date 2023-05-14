#include <memory>
#include "graphicdisplay.h"
#include <string>
#include "Window.h"
#include <sstream>
#include <iostream>
using namespace std;
   

GraphicDisplay::GraphicDisplay(shared_ptr<Xwindow> g):
    graphic{g} {}

string IntToString(int num) {
    ostringstream oss;
    oss << num;
    return oss.str();
}

void GraphicDisplay::notify(Board& whoNotified) {
    std::shared_ptr <Player> player1 = whoNotified.getPlayer1();
    std::shared_ptr <Player> player2 = whoNotified.getPlayer2();
    graphic->fillRectangle(0, 0, 600, 50, Xwindow::Magenta);
    graphic->drawString(230, 15, "Biquadris Highest Score:");
    string hisco = IntToString(whoNotified.hi);
    graphic->drawString(385, 15, hisco);
    graphic->drawString(100, 25, "Level:");
    string levelStr1 = IntToString(player1->curLev);
    graphic->drawString(150, 25, levelStr1);
    
    graphic->drawString(100, 45, "Score:");
    string scoreStr1 = IntToString(player1->score);
    graphic->drawString(150, 45, scoreStr1);
    
    graphic->drawString(425, 25, "Level:");
    string levelStr2 = IntToString(player2->curLev);
    graphic->drawString(475, 25, levelStr2);
    
    graphic->drawString(425, 45, "Score:");
    string scoreStr2 = IntToString(player2->score);
    graphic->drawString(475, 45, scoreStr2);
    graphic->drawLine(0, 50, 265, 50);
    graphic->drawLine(350, 50, 600, 50);
    graphic->fillRectangle(0, 17*25, 600, 25, Xwindow::Magenta);
    for (int row = 0; row < 15; row++) {
        for (int col = 0; col < 11; col++) {
            player1->Field[row][col].draw(col, row+2, graphic.get());
        }
        for (int col = 0; col < 11; col++) {
            player2->Field[row][col].draw(col+13, row+2, graphic.get());
        }
    }
    graphic->drawString(5, 440, "Next:");
    graphic->drawString(330, 440, "Next:");
    for (int i = 18; i < 30; ++i) {
        for (int j = 0; j < 24; ++j) {
            graphic->fillRectangle(j*25, i*25, 25, 25, Xwindow::Black);
        }
    }
    shared_ptr<Block> p1 = player1->nextBlock;
    shared_ptr<Block> p2 = player2->nextBlock;
    vector<vector<string>> b1 = p1->getBlock();
    vector<vector<string>> b2 = p2->getBlock();
    
    for (int i = 2; i < 5; ++i){
        for (int j = 0; j < 4; ++j){
            if (b1[i][j] != " ") {
                if (b1[i][j] == "I") {
                    graphic->fillRectangle((3+j)*25, (16+i)*25, 25, 25, Xwindow::Red);
                } else if (b1[i][j] == "J"){
                    graphic->fillRectangle((3+j)*25, (16+i)*25, 25, 25, Xwindow::Green);
                } else if (b1[i][j] == "L"){
                    graphic->fillRectangle((3+j)*25, (16+i)*25, 25, 25, Xwindow::Blue);
                } else if (b1[i][j] == "Z"){
                    graphic->fillRectangle((3+j)*25, (16+i)*25, 25, 25, Xwindow::Pink);
                } else if (b1[i][j] == "S"){
                    graphic->fillRectangle((3+j)*25, (16+i)*25, 25, 25, Xwindow::Yellow);
                } else if (b1[i][j] == "O"){
                    graphic->fillRectangle((3+j)*25, (16+i)*25, 25, 25, Xwindow::Orange);
                } else if (b1[i][j] == "T"){
                    graphic->fillRectangle((3+j)*25, (16+i)*25, 25, 25, Xwindow::Brown);
                }
            }
        }
        for (int j = 0; j < 4; ++j) {
            if (b2[i][j] != " "){
                if (b2[i][j] == "I") {
                    graphic->fillRectangle(25*(j+16), 25*(i+16), 25, 25, Xwindow::Red);
                } else if (b2[i][j] == "J"){
                    graphic->fillRectangle(25*(j+16), 25*(i+16), 25, 25, Xwindow::Green);
                } else if (b2[i][j] == "L"){
                    graphic->fillRectangle(25*(j+16), 25*(i+16), 25, 25, Xwindow::Blue);
                } else if (b2[i][j] == "Z"){
                    graphic->fillRectangle(25*(j+16), 25*(i+16), 25, 25, Xwindow::Pink);
                } else if (b2[i][j] == "S"){
                    graphic->fillRectangle(25*(j+16), 25*(i+16), 25, 25, Xwindow::Yellow);
                } else if (b2[i][j] == "O"){
                    graphic->fillRectangle(25*(j+16), 25*(i+16), 25, 25, Xwindow::Orange);
                } else if (b2[i][j] == "T"){
                    graphic->fillRectangle(25*(j+16), 25*(i+16), 25, 25, Xwindow::Brown);
                }
            }
        }
    }
}

bool GraphicDisplay::notify(std::shared_ptr <Player> whoNotified) {
    return true;
}

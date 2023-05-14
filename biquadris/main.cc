#include <iostream>
#include <string>
#include <sstream>
#include "Board.h"
#include "Grid.h"
#include "Player.h"
#include "GameLevel.h"
#include "starBlock.h"
#include <cmath>
#include <cstdlib>
#include <memory>
#include <fstream>
#include "Window.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
using namespace std;

string seqName1 = "biquadris_sequence1.txt";
string seqName2 = "biquadris_sequence2.txt";
int seedn = 100;
bool specialOn = false;


int main(int argc, const char * argv[]) {
    // initialize a gd->graphic
    int startlevel = 0; 
    int mylevel = 0;
    Board b;
    TextDisplay td;
    bool enablegraph = true;
    if (argc > 1) {
        for (int i = 1 ; i < argc ; i++) {
            string hyphen = argv[i];
            if (hyphen == "-text") {
                cout << "Text Mode!" << endl;
                enablegraph = false;
            }

            if (hyphen == "-scriptfile1") {
                i++;
                if ((i >= argc) || (argv[i][0] == '-')) {
                    cout << "You did not give a filename!" << endl;
                    i--;
                } else {
                    seqName1 = argv[i];
                    cout << "We will use " << seqName1 << " as a source for player 1!" << endl;
                }
            }

            if (hyphen == "-scriptfile2") {
                i++;
                if ((i >= argc) || (argv[i][0] == '-')) {
                    cout << "You did not give a filename!" << endl;
                    i--;
                } else {
                    seqName2 = argv[i];
                    cout << "We will use " << seqName2 << " as a source for player 2!" << endl;
                }
            }

            if (hyphen == "-seed") {
                i++;
                if ((i >= argc) || (argv[i][0] < '0') || (argv[i][0] > '9')) {
                    cout << "You did not give a seed number!" << endl;
                    i--;
                } else {
                    seedn = stoi(argv[i]);
                    cout << "We set seed to " << seedn << "." << endl;
                }
            }

            if (hyphen == "-startlevel") {
                
                i++;
                if ((i >= argc) || (argv[i][0] < '0') || (argv[i][0] > '9')) {
                    cout << "You did not give a number for startlevel!" << endl;
                    i--;
                } else {
                    startlevel = stoi(argv[i]);
                    mylevel = startlevel;
                    cout << "The game starts in level " << startlevel << "!" << endl;
                }
            }
        }
    }

    GraphicDisplay* gd = nullptr;
    if (enablegraph) {
       shared_ptr<Xwindow> board = shared_ptr<Xwindow>(new Xwindow{600, 550});
       gd = new GraphicDisplay{board};
    }
    while (enablegraph) {
        // draw cover
        string s1;
        gd->graphic->fillRectangle( 0 , 0 , 600 , 550 , 0);
        string line1 = "Jackie, Rickie and Ruiqi's Biquadris Game!";
        gd->graphic->drawString(185, 250, line1);
        string c = "Press anykey to start! ";
        gd->graphic->drawString(225, 430, c);
        if(cin >> s1) break;
    }

    // default/initial settings
    // b = new Board();
    string command;
    shared_ptr <Player>& player1 = b.getPlayer1();
    shared_ptr <Player>& player2 = b.getPlayer2();
    b.setPlayer(player1, 1, startlevel);
    b.setPlayer(player2, 2, startlevel);
    player1->curBlock = player1->levptr->generate_Block(player1);
    player1->nextBlock = player1->levptr->generate_Block(player1);
    
    player2->curBlock = player2->levptr->generate_Block(player2);
    player2->nextBlock = player2->levptr->generate_Block(player2);
    
    td.notify(b.curPlayer());
    td.notify(b);
    if (enablegraph) {
        gd->graphic->fillRectangle(0, 0, 600, 550, 0);
        gd->notify(b);
    }

    while (cin >> command) {
        vector<string> CmdList;
        CmdList.emplace_back("mapping");
        if (command == "sequence") {
            string comfile;
            cin >> comfile;
            ifstream comseq{comfile};
            string s;
            while(comseq >> s) {
                cout << s << endl;
                CmdList.emplace_back(s);
            }
        } else {
           CmdList.emplace_back(command);
        }
        int size = CmdList.size();
        int index = 1;
        // command interpreter
        while (index != size) {
            int num = -111;
            int i = 0;
            string cmd = CmdList[index];
            if ((cmd[0] <= '9')&&(cmd[0] >= '0')) num = 0;
            while ((cmd[i] <= '9')&&(cmd[i] >= '0')) {
                num =  num + stoi(string(1,cmd[0])) * pow(10 , i);
                ++i;
            }
            string temp = "";
            int len = cmd.length();
            while (i < len) {
                temp = temp + cmd[i];
                ++i;
            }

            cmd = temp;
        
            b.deadGrid(player1);
            b.deadGrid(player2);
        
            string cont;
            if (!b.gameOver (player1)) {
                cout << "Player1 game over! Player2 win!" << endl;
                cout << "Do you want to restart? Type Yes to restart, exit game otherwise. " << endl;
                cin >> cont;
                if (cont == "yes") {
                    b.restart(b.curPlayer(), b.nextPlayer());
                    b.curPlayer()->curBlock = b.curPlayer()->levptr->generate_Block(player1);
                    b.curPlayer()->nextBlock = b.curPlayer()->levptr->generate_Block(player1);
                    b.nextPlayer()->curBlock = b.nextPlayer()->levptr->generate_Block(player2);
                    b.nextPlayer()->nextBlock = b.nextPlayer()->levptr->generate_Block(player2);
                    cmd = " ";
                } else {
                    exit(0);
                }
            }
            if (!b.gameOver (player2)) {
                cout << "Player2 game over! Player1 win!" << endl;
                cout << "Do you want to restart? Type Yes to restart, exit game otherwise. " << endl;
                cin >> cont;
                if (cont == "yes") {
                    b.restart(b.curPlayer(), b.nextPlayer());
                    b.curPlayer()->curBlock = b.curPlayer()->levptr->generate_Block(player1);
                    b.curPlayer()->nextBlock = b.curPlayer()->levptr->generate_Block(player1);
                    b.nextPlayer()->curBlock = b.nextPlayer()->levptr->generate_Block(player2);
                    b.nextPlayer()->nextBlock = b.nextPlayer()->levptr->generate_Block(player2);
 	            cmd = " ";
                } else {
                    exit(0);
                }
            }

            // blocks
            if (cmd == "I" || cmd == "i") {
                b.curPlayer()->curBlock = make_shared<IBlock>();
            }
            if (cmd == "J" || cmd == "j") {
                b.curPlayer()->curBlock = make_shared<JBlock>();
            }
            if (cmd == "L" || cmd == "l") {
                b.curPlayer()->curBlock = make_shared<LBlock>();
            }
            if (cmd == "O" || cmd == "o") {
                b.curPlayer()->curBlock = make_shared<OBlock>();
            }
            if (cmd == "S" || cmd == "s") {
                b.curPlayer()->curBlock = make_shared<SBlock>();
            }
            if (cmd == "Z" || cmd == "z") {
                b.curPlayer()->curBlock = make_shared<ZBlock>();
            }
            if (cmd == "T" || cmd == "t") {
                b.curPlayer()->curBlock = make_shared<TBlock>();
            }

            // clockwise or counterclockwise
            if (cmd[0] == 'c' || cmd[0] == 'C') {
                if (cmd.length() > 1) {
                    // clockwise
                    if (cmd[1] == 'l'|| cmd[1] == 'L') { 
                        if (num < 0) num = 1;
                        for (;num > 0;num--) {
                            if (b.curPlayer()->clockPossible) {
                                b.curPlayer()->curBlock->clockwise();
                            }
                            // update possibilities
                            b.curPlayer()->curBlock->unmodified = false;
                            b.levelHeavy(b.curPlayer());
                            b.curPlayer()->dPossible = true;
                            b.curPlayer()->lPossible = true;
                            b.curPlayer()->rPossible = true;
                            b.nextPlayer()->dPossible = true;
                            b.nextPlayer()->lPossible = true;
                            b.nextPlayer()->rPossible = true;
                            b.updatePossible(b.curPlayer());
                            
                        }
                    }

                    // counterclockwise
                    if (cmd[1] == 'o' || cmd[1] == 'O') { 
                        if (num < 0) num = 1;
                        for (;num > 0;num--){
                            if (b.curPlayer()->counterCPossible) {
                                b.curPlayer()->curBlock->counterclockwise();
                            }
                            b.curPlayer()->curBlock->unmodified = false;
                            b.levelHeavy(b.curPlayer());
                            b.curPlayer()->dPossible = true;
                            b.curPlayer()->lPossible = true;
                            b.curPlayer()->rPossible = true;
                            b.nextPlayer()->dPossible = true;
                            b.nextPlayer()->lPossible = true;
                            b.nextPlayer()->rPossible = true;
                            b.updatePossible(b.curPlayer());
                            
                        }
                    }
                }
            }

            // down or drop
            if (cmd[0] == 'd' || cmd[0] == 'D') {
                if (cmd.length() > 1) {
                    // down
                    if (cmd[1] == 'o') {
                        if (num < 0) num = 1;
                        for (;num > 0;num--) {
                            b.updatePossible(b.curPlayer());
                            b.down(b.curPlayer());
                            b.updatePossible(b.curPlayer());
                            b.curPlayer()->curBlock->unmodified = false;
                            b.levelHeavy(b.curPlayer());
                        }
                    }
                    // drop
                    if (cmd[1] == 'r' || cmd[1] == 'R') {
                        b.drop(b.curPlayer());
                    }
                    b.curPlayer()->curBlock->unmodified = false;
                }
            }

            // l: left, levelup or leveldown
            if (cmd[0] == 'l'|| cmd[0] == 'L') {
                // left
                if (cmd.length() > 2) {
                    if (cmd[2] == 'f') {
                        if (num < 0) num = 1;
                            while(num != 0) {
                            b.left(b.curPlayer());
                            b.updatePossible(b.curPlayer());
                            b.curPlayer()->curBlock->unmodified = false;
                            b.levelHeavy(b.curPlayer());
                            b.blockheavy(b.curPlayer());
                            num--;
                        }
                    }
                    if (cmd.length() > 5) {
                        // levelup
                        if (cmd[5] == 'u') {
                            if (num < 0) num = 1;
                                while (num != 0){
                                b.levelUp(b.curPlayer());
                                mylevel++;
                                num--;
                            }
                        }
                        // leveldown
                        if (cmd[5] == 'd'|| cmd[5] == 'D') {
                            if (num < 0) num = 1;
                            while (num != 0) {
                                b.levelDown(b.curPlayer());
                                mylevel--;
                                num--;
                            }
                        }
                    }
                }
            }

            // norandom file
            if (cmd[0] == 'n' || cmd[0] == 'N') {
                string noranFile;
                if (cin >> noranFile) {
                    if ((b.curPlayer()->curLev == 0)||(b.curPlayer()->curLev == 1)||(b.curPlayer()->curLev == 2)) {
                        cout << "Only Level 3 and Level 4 can be non-random!!" << endl;
                    } else {
                        cout << "We will use" << noranFile << " for testing!" <<endl;
                        b.curPlayer()->levptr->AddSeqFile(noranFile,b.curPlayer()->id);
                    }
                }
            }

            // random, right or restart
            if (cmd[0] == 'r' || cmd[0] == 'R') {
                if (cmd.length() > 1) {
                    // random
                    if (cmd[1] == 'a'|| cmd[1] == 'A') {
                        if ((b.curPlayer()->curLev == 0)||(b.curPlayer()->curLev == 1)||(b.curPlayer()->curLev == 2)) {
                            cout << "only curLev 3 and curLev 4 can random back!!" << endl;
                        } else {
                            b.curPlayer()->levptr->setRandom(b.curPlayer()->id);
                        }
                    }

                    // restart
                    if (cmd[1] == 'e' || cmd[1] == 'E') {
                        b.restart(b.curPlayer(), b.nextPlayer());
                        b.curPlayer()->curBlock = b.curPlayer()->levptr->generate_Block(player1);
                        b.curPlayer()->nextBlock = b.curPlayer()->levptr->generate_Block(player1);
                        b.nextPlayer()->curBlock = b.nextPlayer()->levptr->generate_Block(player2);
                        b.nextPlayer()->nextBlock = b.nextPlayer()->levptr->generate_Block(player2);
                    }

                    // right
                    if (cmd[1] == 'i'|| cmd[1] == 'I') {
                        if (num < 0) num = 1;
                        while (num != 0) {
                            b.right(b.curPlayer());
                            b.updatePossible(b.curPlayer());
                            b.curPlayer()->curBlock->unmodified = false;
                            b.levelHeavy(b.curPlayer());
                            b.blockheavy(b.curPlayer());
                            num--;
                        }
                        
                    }
                }
            }

            // sequence file
            if (cmd[0] == 's'|| cmd[0] == 'S') {
                string seqfile;
                if (cmd[1] == 'e' || cmd[1] == 'E') {
                    if (cin >> seqfile) {
                        cout << "we sequence" << seqfile << " something" << endl;
                    }
                }
            }
        
            if (td.notify(b.curPlayer())) {
                b.curPlayer()->nextBlock  = b.curPlayer()->levptr->generate_Block(b.curPlayer());
                int numrow = b.recalculate(b.curPlayer());
                if (numrow >= 2) {
                    string influence;
                    cout << "Choose a Punishment: Blind Or Heavy Or Force";
                    cout << endl;
                    while (cin >> influence) {
                        if (influence == "Heavy") {
                            b.nextPlayer()->heavy = true;
                            break;
                        } else if (influence == "Blind") {
                            b.blind(b.nextPlayer());
                            break;
                        } else if (influence == "Force") {
                            cout << "Pick a block for your opponent next block" << endl;
                            char tempblock;
                            cin >> tempblock;
                            b.switchPlayer();
                            shared_ptr<Block> blocktype = nullptr;
                            switch(tempblock) {
                                case 'I' : blocktype = make_shared<IBlock>(); break;
                                case 'J' : blocktype = make_shared<JBlock>(); break;
                                case 'L' : blocktype = make_shared<LBlock>(); break;
                                case 'O' : blocktype = make_shared<OBlock>(); break;
                                case 'S' : blocktype = make_shared<SBlock>(); break;
                                case 'Z' : blocktype = make_shared<ZBlock>(); break;
                                case 'T' : blocktype = make_shared<TBlock>(); break;
			                }
                            b.curPlayer()->curBlock = blocktype;
                            b.switchPlayer();
                            break;
                        } else {
                            continue;
                        }
                    }
                }
                b.switchPlayer();
            }

        // punishment
        if (b.curPlayer()->starblock || mylevel == 4) { 
            if (b.curPlayer()->notclear == 5) {
                shared_ptr<Block> startemp = b.curPlayer()->curBlock;
                b.curPlayer()->curBlock = make_shared<starBlock>();
                
                b.right(b.curPlayer());
                b.right(b.curPlayer());
                b.drop(b.curPlayer());
                
                b.updatePossible(b.curPlayer());
                b.recalculate(b.curPlayer());
                td.notify(b.curPlayer());
                td.notify(b);
                if (enablegraph) {
                    gd->notify(b);
                }
                b.curPlayer()->curBlock = startemp;
                b.curPlayer()->notclear = 0;
            }
        }

            b.recalculate(b.curPlayer());
            td.notify(b.curPlayer());
            td.notify(b);
            if (enablegraph) {
                gd->notify(b);
            }
            index++;
        }
    }
}

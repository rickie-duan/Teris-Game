#include "Grid.h"
using namespace std;

Grid::Grid(): Active(false), blind(false), color(" "), window(nullptr), x(0), y(0) {}

Grid::~Grid() {}

void Grid::Activate(string new_color) {
    Active = true;
    color = new_color;
}

void Grid::Deactivate(string new_color) {
    Active = false;
    color = new_color;
}

void Grid::TurnBlind() {
    blind = true;
}

void Grid::NotBlind() {
    blind = false;
}

bool Grid::isActive() {
    return Active;
}

ostream &operator<<(ostream &out, const Grid &g) {
    if (!(g.blind)) {
    out << g.color;
    }
    else {
        out << "?";
    }
    return out;
}

string Grid::GetColor() {
    return color;
}

void Grid::draw(int row, int col, Xwindow *board) {
   if (color == "I") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Red);
   } else if (color == "J") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Green);
   } else if (color == "L") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Blue);
   } else if (color == "Z") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Pink);
   } else if (color == "S") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Yellow);
   } else if (color == "O") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Orange);
   } else if (color == "T") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Brown);
   } else if (color == " ") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::Black);
   }else if (color == "*") {
     board->fillRectangle(row * 25, col *25, 25, 25, Xwindow::White);
   }

    if (blind) {
        board->fillRectangle(row * 25, col *25, 25, 25, 1);
    }
}

#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "observer.h"
#include "Board.h"
#include "Player.h"
#include <memory>

class GraphicDisplay : public Observer {

 public:
    std::shared_ptr<Xwindow> graphic;
    GraphicDisplay(std::shared_ptr<Xwindow> g);
    GraphicDisplay() = default;
    void notify(Board& whoNotified) override; 
    bool notify(std::shared_ptr <Player> whoNotified) override; 
    
};

#endif

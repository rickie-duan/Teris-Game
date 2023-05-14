#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "observer.h"
#include "Board.h"
#include "Player.h"
#include <memory>

class TextDisplay : public Observer {

public:
    TextDisplay() = default;
    ~TextDisplay() = default;
    void notify(Board& whoNotified) override; 
    bool notify(std::shared_ptr <Player> whoNotified) override; 

};

#endif

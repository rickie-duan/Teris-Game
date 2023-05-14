#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <memory>
class Subject;
class Board;
class Player;

class Observer {
 public:
  virtual void notify(Board &b) = 0;
  virtual bool notify(std::shared_ptr <Player> p) = 0;
};
#endif

//Erik Koenitzer
#ifndef Ball_hpp
#define Ball_hpp

#include "Map.hpp"
#include <vector>

class Ball
{
public:
  Ball(Map& m);
  bool move(Map& m, std::vector<Ball>& balls);
  void restorePos(Map& m);
  void restorePosStar(Map& m);
  void startStarPos(Map& m);
  int getOwner() {return owner;}

  friend class Paddle;
private:
  char ballch;
  bool scored;
  int x;
  int y;
  int xDir;
  int yDir;
  int owner;
};

#endif
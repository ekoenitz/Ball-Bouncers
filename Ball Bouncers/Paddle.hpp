//Erik Koenitzer
#ifndef paddle_hpp
#define paddle_hpp

#include "Ball.hpp"
#include "Map.hpp"
#include <vector>

class Paddle
{
public:
  Paddle (bool ai, int pNum, Map& m);
  bool isAnAI () {return isAI;}
  void move (bool isPosDir, Map& m);
  void boing (Map& m, std::vector<Ball>& balls);
  void moveAI (Map& m, std::vector<Ball>& balls);
private:
  void unboing (Map& m);

  static const int SIZE = 3;
  char padchs [SIZE];
  bool vertDir;
  bool isAI;
  bool boinged;
  int x;
  int y;
};

#endif
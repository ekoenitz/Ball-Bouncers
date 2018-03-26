//Erik Koenitzer
#ifndef map_hpp
#define map_hpp

#include <iostream>
#include <string>
#include <vector>

class Map
{
public:
  Map() {}
  void spawnStar();
  bool isStarActive() {return map[starY][starX] == '*';}
  void setMap(std::string& s);
  
  friend std::ostream& operator << (std::ostream& out, const Map& m);
  friend class Ball;
  friend class Paddle;
private:
  std::vector<std::string> map;
  int starX;
  int starY;
};

#endif
//Erik Koenitzer
#include "map.hpp"

#include "windows.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

BOOL gotoxy(const WORD x, const WORD y) 
{
	COORD xy;
	xy.X = x;
	xy.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void Map::setMap(std::string& s)
{
  s += ".txt";
  std::ifstream fin(s);
  if (fin)
  {
    while (getline(fin, s))
		{
			map.push_back(s);
		}
    fin.close();
  }
}

void Map::spawnStar()
{
  bool noStar = true;
  do
  {
    starX = map.at(0).size()/3 + rand() % (map.at(0).size()/2);
    starY = map.size()/3 + rand() % (map.size()/2);
    (map[starY][starX] == ' ') && (map[starY][starX] = '*') && (noStar = false);
  } while (noStar);
}
  
std::ostream& operator << (std::ostream& out, const Map& m)
{
  gotoxy(0, 0);
  for (int i = 0; i < m.map.size(); i++)
  {
    out << m.map.at(i) << std::endl;
  }
  return out;
}
//Erik Koenitzer
#include "Ball.hpp"
#include "Map.hpp"
#include <vector>

Ball::Ball(Map& m)
{
  ballch = 'O';
  x = m.map[0].size()/2;
  y = m.map.size()/2;
  xDir = -1;
  yDir = 0;
  m.map[y][x] = ballch;
  owner = 0;
  scored = false;
}

bool Ball::move (Map& m, std::vector<Ball>& balls)
{
  (xDir == 0 && yDir == 0) && (xDir = 1);
  (m.map[y][x] == ballch) && (m.map[y][x] = ' ');
  bool hit = false; //NOT return value, used only for ball collisions but compiler wants it outside case 'O'

  if (y+yDir < m.map.size() && x+xDir < m.map[0].size() && !scored)
    {
    switch (m.map[y+yDir][x+xDir])
    {
    case '#':
      (m.map[y+yDir][x] == '#') ? yDir = (yDir == 1) ? -1 : 1 :
      (m.map[y][x+xDir] == '#') ? (xDir = (xDir == 1) ? -1 : 1) :
      (xDir = (xDir == 1 ? -1 : 1), yDir = (yDir == 1 ? -1 : 1));

      (m.map[y+yDir][x+xDir] != ' ' && m.map[y+yDir][x+xDir] != '|' && m.map[y+yDir][x+xDir] != '-') && (xDir = (xDir == 1 ? -1 : 1));
      break;
    case 'O':
      for (int i = 0; i < balls.size() && !hit; i++)
      {
        hit = (balls.at(i).x == x+xDir && balls.at(i).y == y+yDir);
        (hit) && (balls.at(i).xDir = xDir) && (balls.at(i).yDir = yDir);
      }
      xDir = (xDir == 1) ? -1 : (xDir == -1) ? 1 : 0;
      yDir = (yDir == 1) ? -1 : (yDir == -1) ? 1 : 0;
      break;
    case '\\':
      if (x+xDir <= 2 || x+xDir >= m.map.at(0).size()-3)
      {
        yDir = (xDir == 1) ? 1 : -1;
        owner = (xDir == 1) ? 2 : 1;
        xDir = (xDir == 1) ? -1 : 1;
      }
      else
      {
        owner = (yDir == 1) ? 4 : 3;
        xDir = (yDir == 1) ? 1 : -1;
        yDir = (yDir == 1) ? -1 : 1;
      }
      break;
    case '/':
      if (x+xDir <= 2 || x+xDir >= m.map.at(0).size()-3)
      {
        yDir = (xDir == 1) ? -1 : 1;
        owner = (xDir == 1) ? 2 : 1;
        xDir = (xDir == 1) ? -1 : 1;
      }
      else
      {
        owner = (yDir == 1) ? 4 : 3;
        xDir = (yDir == 1) ? -1 : 1;
        yDir = (yDir == 1) ? -1 : 1;
      }
      break;
    case '1':
      xDir = 1;
      yDir = 0;
      owner = 1;
      break;
    case '2':
      xDir = -1;
      yDir = 0;
      owner = 2;
      break;
    case '3':
      yDir = 1;
      xDir = 0;
      owner = 3;
      break;
    case '4':
      yDir = -1;
      xDir = 0;
      owner = 4;
      break;
    case '|':
    case '-':
      scored = true;
      break;
    case '*':
      m.map[y+yDir][x+xDir] = ' ';
      scored = true;
    }

    if (!scored)
    {
      x += xDir;
      y += yDir;
      (m.map[y][x] == ' ') ? (m.map[y][x] = ballch) : (scored = m.map[y][x] == '|' || m.map[y][x] == '-');
    }
  }
  return scored;
}

void Ball::restorePos(Map& m)
{
  x = m.map[0].size()/2;
  y = m.map.size()/2;
  m.map[y][x] = ballch;
  scored = false;
  switch (owner)
  {
  case 1:
    xDir = -1;
    yDir = 0;
    break;
  case 2:
    xDir = 1;
    yDir = 0;
    break;
  case 3:
    xDir = 0;
    yDir = -1;
    break;
  case 4:
    xDir = 0;
    yDir = 1;
    break;
  }
  owner = 0;
}

void Ball::restorePosStar(Map& m)
{
  m.map[y][x] = ' ';
  scored = false;
  switch (owner)
  {
  case 0:
  case 1:
    x = 3;
    y = m.map.size()/2;
    xDir = 1;
    yDir = 0;
    break;
  case 2:
    x = m.map[0].size()-4;
    y = m.map.size()/2;
    xDir = 1;
    yDir = 0;
    break;
  case 3:
    x = m.map[0].size()/2;
    y = 3;
    xDir = 0;
    yDir = 1;
    break;
  default:
    x = m.map[0].size()/2;
    y = m.map.size()-4;
    xDir = 0;
    yDir = -1;
    break;
  }

  m.map[y][x] = ballch;
}

void Ball::startStarPos(Map& m)
{
  m.map[y][x] = m.map.size() < 11 ? ' ' : '#'; //So 1P map isn't impossible
  x = 2;
  y = m.map.size()/2;
  xDir = 1;
  yDir = 0;
}
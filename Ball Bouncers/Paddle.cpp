//Erik Koenitzer
#include "Paddle.hpp"
#include "Map.hpp"
#include "Ball.hpp"
#include <vector>

Paddle::Paddle (bool ai, int pNum, Map& m)
{
  switch (pNum)
  {
  case 1:
    x = 1;
    y = m.map.size()/2;
    vertDir = true;
    isAI = ai;
    padchs[0] = '\\';
    padchs[1] = pNum+'0';
    padchs[2] = '/';
    break;
  case 2:
    x = m.map[0].size() - 2;
    y = m.map.size()/2;
    vertDir = true;
    isAI = ai;
    padchs[0] = '/';
    padchs[1] = pNum+'0';
    padchs[2] = '\\';
    break;
  case 3:
    x = m.map[0].size()/2;
    y = 1;
    vertDir = false;
    isAI = ai;
    padchs[0] = '\\';
    padchs[1] = pNum+'0';
    padchs[2] = '/';
    break;
  default:
    x = m.map[0].size()/2;
    y = m.map.size() - 2;
    vertDir = false;
    isAI = ai;
    padchs[0] = '/';
    padchs[1] = pNum+'0';
    padchs[2] = '\\';
  }

  m.map[y-vertDir][x-1+vertDir] = padchs[0];
  m.map[y][x] = padchs[1];
  m.map[y+vertDir][x+1-vertDir] = padchs[2];
}

void Paddle::move (bool isPosDir, Map& m)
{
  if (boinged)
  {
    unboing(m);
  }

  if (vertDir && m.map[y-2+isPosDir*4][x] == ' ')
  {
    m.map[y+1+isPosDir*-2][x] = ' ';
    isPosDir ? y++ : y--;
    m.map[y-1][x] = padchs[0];
    m.map[y][x] = padchs[1];
    m.map[y+1][x] = padchs[2];
  }
  else if (!vertDir && m.map[y][x-2+isPosDir*4] == ' ') //Checking !vertDir after checking vertDir is necessary to prevent weirdness
  {
    m.map[y][x+1+isPosDir*-2] = ' ';
    isPosDir ? x++ : x--;
    m.map[y][x-1] = padchs[0];
    m.map[y][x] = padchs[1];
    m.map[y][x+1] = padchs[2];
  }
}

void Paddle::boing (Map& m, std::vector<Ball>& balls)
{
  boinged = true;
  bool hitBall = false;

  switch (padchs[1])
  {
  case '1':
    m.map[y][x] = ' ';
    (m.map[y-1][x+1] == 'O') && (hitBall = true);
    m.map[y-1][x+1] = padchs[0];
    (m.map[y][x+1] == 'O') && (hitBall = true);
    m.map[y][x+1] = padchs[1];
    (m.map[y+1][x+1] == 'O') && (hitBall = true);
    m.map[y+1][x+1] = padchs[2];

    for (int i = 0; hitBall && i < balls.size(); i++)
    {
      bool hitThisOne = (balls[i].x == x+1 || balls[i].x == x || balls[i].x == x-1);
      (hitThisOne) && (hitThisOne = balls[i].y == y+1 || balls[i].y == y || balls[i].y == y-1);
      (hitThisOne) && (balls[i].xDir = 1, balls[i].yDir = balls[i].y - y, balls[i].owner = 1);
    }
    break;
  case '2':
    m.map[y][x] = ' ';
    (m.map[y-1][x-1] == 'O') && (hitBall = true);
    m.map[y-1][x-1] = padchs[0];
    (m.map[y][x-1] == 'O') && (hitBall = true);
    m.map[y][x-1] = padchs[1];
    (m.map[y+1][x-1] == 'O') && (hitBall = true);
    m.map[y+1][x-1] = padchs[2];

    for (int i = 0; hitBall && i < balls.size(); i++)
    {
      bool hitThisOne = (balls[i].x == x+1 || balls[i].x == x || balls[i].x == x-1);
      (hitThisOne) && (hitThisOne = balls[i].y == y+1 || balls[i].y == y || balls[i].y == y-1);
      (hitThisOne) && (balls[i].xDir = -1, balls[i].yDir = balls[i].y - y, balls[i].owner = 2);
    }
    break;
  case '3':
    m.map[y][x] = ' ';
    (m.map[y+1][x-1] == 'O') && (hitBall = true);
    m.map[y+1][x-1] = padchs[0];
    (m.map[y+1][x] == 'O') && (hitBall = true);
    m.map[y+1][x] = padchs[1];
    (m.map[y+1][x+1] == 'O') && (hitBall = true);
    m.map[y+1][x+1] = padchs[2];

    for (int i = 0; hitBall && i < balls.size(); i++)
    {
      bool hitThisOne = (balls[i].x == x+1 || balls[i].x == x || balls[i].x == x-1);
      (hitThisOne) && (hitThisOne = balls[i].y == y+1 || balls[i].y == y || balls[i].y == y-1);
      (hitThisOne) && (balls[i].xDir = balls[i].x - x, balls[i].yDir = 1, balls[i].owner = 3);
    }
    break;
  default:
    m.map[y][x] = ' ';
    (m.map[y-1][x-1] == 'O') && (hitBall = true);
    m.map[y-1][x-1] = padchs[0];
    (m.map[y-1][x] == 'O') && (hitBall = true);
    m.map[y-1][x] = padchs[1];
    (m.map[y-1][x+1] == 'O') && (hitBall = true);
    m.map[y-1][x+1] = padchs[2];

    for (int i = 0; hitBall && i < balls.size(); i++)
    {
      bool hitThisOne = (balls[i].x == x+1 || balls[i].x == x || balls[i].x == x-1);
      (hitThisOne) && (hitThisOne = balls[i].y == y+1 || balls[i].y == y || balls[i].y == y-1);
      (hitThisOne) && (balls[i].xDir = balls[i].x - x, balls[i].yDir = -1, balls[i].owner = 4);
    }
  }
}

void Paddle::unboing (Map&m)
{
  if (boinged)
  {
    boinged = false;
    switch (padchs[1])
    {
    case '1':
      m.map[y][x] = padchs[1];
      m.map[y-1][x+1] = ' ';
      m.map[y][x+1] = ' ';
      m.map[y+1][x+1] = ' ';
      break;
    case '2':
      m.map[y][x] = padchs[1];
      m.map[y-1][x-1] = ' ';
      m.map[y][x-1] = ' ';
      m.map[y+1][x-1] = ' ';
      break;
    case '3':
      m.map[y][x] = padchs[1];
      m.map[y+1][x-1] = ' ';
      m.map[y+1][x] = ' ';
        m.map[y+1][x+1] = ' ';
      break;
    default:
      m.map[y][x] = padchs[1];
      m.map[y-1][x-1] = ' ';
      m.map[y-1][x] = ' ';
      m.map[y-1][x+1] = ' ';
    }
  }
}

void Paddle::moveAI (Map& m, std::vector<Ball>& balls)
{
  int closest = 0;
  for (int i = 1; i < balls.size(); i++)
  {
    switch (padchs[1])
    {
    case '1':
      ((!balls.at(i).scored && balls.at(closest).x > balls.at(i).x) || balls.at(closest).scored) && (closest = i);
      break;
    case '2':
      ((!balls.at(i).scored && balls.at(closest).x < balls.at(i).x) || balls.at(closest).scored) && (closest = i);
      break;
    case '3':
      ((!balls.at(i).scored && balls.at(closest).y > balls.at(i).y) || balls.at(closest).scored) && (closest = i);
      break;
    default:
      ((!balls.at(i).scored && balls.at(closest).y < balls.at(i).y) || balls.at(closest).scored) && (closest = i);
    }
  }

  switch (padchs[1])
  {
  case '1':
  case '2':
    if (balls.at(closest).y != y-1 && balls.at(closest).y != y+1)
    {
      move((balls.at(closest).y > y), m);
    }
    else
    {
      boing(m, balls);
    }
    break;
  default:
    if (balls.at(closest).x != x-1 && balls.at(closest).x != x+1)
    {
      move((balls.at(closest).x > x), m);
    }
    else
    {
      boing(m, balls);
    }
  }
}

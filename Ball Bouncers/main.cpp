//Erik Koenitzer
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "windows.h"
#include <vector>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

#include "Ball.hpp"
#include "Map.hpp"
#include "Paddle.hpp"

using namespace std;

void initPong (Map& m, vector<Ball>& balls, vector<Paddle>& pads, vector<int>& scores, unsigned int& num)
{
  string userIn;
  string mapName;

  cout << endl << "(T)wo or (F)our players? ";
  getline(cin, userIn);
  userIn += " "; //So it won't crash if no input

  switch (userIn.at(0))
  {
  case 't':
  case 'T':
  case '2':
    mapName = "2PPong";
    num = 2;
    break;
  default:
    mapName = "4PPong";
    num = 4;
  }

  m.setMap(mapName);

  for (int i = 0; i < num; i++)
  {
    cout << endl << "Is Player " << i+1 << " (H)uman or (C)PU? ";
    getline(cin, userIn);
    userIn += " "; //So it won't crash if no input
    pads.push_back(Paddle (toupper(userIn.at(0)) == 'C', i+1, m));
    scores.push_back(0);
  }

  cout << endl << "Enter # of balls in play (max 25): ";
  getline(cin, userIn);
  userIn += " "; //So it won't crash if no input
  stringstream(userIn) >> num;
  (num > 25 || num < 1) && (num = 25);

  for (int i = 0; i < num; i++)
  {
    balls.push_back(Ball (m));
  }

  cout << endl << "Enter points to win: ";
  getline(cin, userIn);
  userIn += " "; //So it won't crash if no input
  stringstream(userIn) >> num;

  cout << endl << "Press Enter to start!";
  getline(cin, userIn);
  system("CLS");
}

void initStar (Map& m, vector<Paddle>& pads)
{
  string userIn;
  string mapName;
  int players;

  cout << endl << "(O)ne, (T)wo, or (F)our players? ";
  getline(cin, userIn);
  userIn += " "; //So it won't crash if no input

  switch (userIn.at(0))
  {
  case 'o':
  case 'O':
  case '1':
    mapName = "1PStar";
    players = 1;
    break;
  case 't':
  case 'T':
  case '2':
    mapName = "2PStar";
    players = 2;
    break;
  default:
    mapName = "4PStar";
    players = 4;
  }

  m.setMap(mapName);

  for (int i = 0; i < players; i++)
  {
    cout << endl << "Is Player " << i+1 << " (H)uman or (C)PU? ";
    getline(cin, userIn);
    userIn += " "; //So it won't crash if no input
    pads.push_back(Paddle (toupper(userIn.at(0)) == 'C', i+1, m));
  }

  cout << endl << "Press Enter to start!";
  getline(cin, userIn);
  system("CLS");
}

void outputScores (vector<int>& v)
{
  cout << "Scores" << endl;
  for (int i = 0; i < v.size(); i++)
  {
    cout << 'P' << i+1 << ": " << v.at(i) << endl;
  }
}

bool moveBalls (Map& m, vector<Ball>& balls)
{
  bool allScored = true;
  for (Ball& b : balls)
  {
    allScored = b.move(m, balls) && allScored;
  }
  return allScored;
}

void moveAIPads (Map& m, vector<Ball>& balls, vector<Paddle>& pads)
{
  for (Paddle& p : pads)
  {
    if (p.isAnAI())
    {
      p.moveAI(m, balls);
    }
  }
}

bool isWon (vector<int>& scores, int goal)
{
  bool gameWon = false;

  for (int i = 0; i < scores.size() && !gameWon; i++)
  {
    gameWon = scores.at(i) >= goal;
  }

  return gameWon;
}

int main()
{
  string userIn;
  srand(time(0));

  do
  {
    system("CLS");
    Map m;
    vector <Paddle> pads;
    vector <Ball> balls;
    vector <int> scores;
    unsigned int goal = 1;
    double time = 41;
    int starScore = 0;
    bool pongMode = true;
    bool starPresent = true;

    cout << "Ball Bouncers by Erik Koenitzer" << endl << endl << "\tControls" << endl;
    cout << "P1:\t\tP2:" << endl << "Up-Q\t\tUp-Up Arrow Key" << endl << "Down-A\t\tDown-Down Arrow Key" << endl << "Thrust-S or W   Thrust-Left Arrow Key" << endl;
    cout << endl << "P3:\t\tP4:" << endl << "Left-#Pad 4\tLeft-Left Click" << endl << "Right-#Pad 6\tRight-Right Click" << endl << "Thrust-#Pad 123 Thrust-Middle Click or Space" << endl;
    cout << endl << "Modes: " << endl;
    cout << "(P)ong (2-4 Players Competitive):" << endl << "Bounce balls into other players' goals while protecting your own." << endl;
    cout << endl << "(S)tar Seekers (1-4 Players Co-Operative):" << endl << "Knock the ball into stars to keep the timer going as long as possible." << endl;

    cout << endl << "Select a mode: ";
    getline(cin, userIn);
    userIn += " "; //So it won't crash if no input

    if (toupper(userIn.at(0)) == 'S')
    {
      initStar (m, pads);
      balls.push_back(Ball(m));
      balls.at(0).startStarPos(m);
      m.spawnStar();
      pongMode = false;
    }
    else
    {
      initPong(m, balls, pads, scores, goal);
    }

    do
    {
      double speed = 102.0;
	    do
	    {    
		    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(speed)));
        cout << m;
        if (pongMode)
        {
          outputScores(scores);
        }
        else 
        {
          cout << endl << "Time: " << setw(2) << static_cast<int>(time);
          time -= speed/1000; 
        }

        //Player 1
        if (GetAsyncKeyState('A'))
        {
          pads[0].move(true, m);
        }
        if (GetAsyncKeyState('Q'))
        {
          pads[0].move(false, m);
        }
        if (GetAsyncKeyState('S') || GetAsyncKeyState('W'))
        {
          pads[0].boing(m, balls);
        }

        //Player 2
        if (GetAsyncKeyState(VK_UP) && pads.size() > 1 && !pads.at(1).isAnAI())
        {
          pads[1].move(false, m);
        }
        if (GetAsyncKeyState(VK_DOWN) &&  pads.size() > 1 && !pads.at(1).isAnAI())
        {
          pads[1].move(true, m);
        }
        if (GetAsyncKeyState(VK_LEFT) &&  pads.size() > 1 && !pads.at(1).isAnAI())
        {
          pads[1].boing(m, balls);
        }

        //Player 3
        if (GetAsyncKeyState(VK_NUMPAD4) &&  pads.size() > 2 && !pads.at(2).isAnAI())
        {
          pads[2].move(false, m);
        }
        if (GetAsyncKeyState(VK_NUMPAD6) &&  pads.size() > 2 && !pads.at(2).isAnAI())
        {
          pads[2].move(true, m);
        }
        if ((GetAsyncKeyState(VK_NUMPAD2) || GetAsyncKeyState(VK_NUMPAD1) || GetAsyncKeyState(VK_NUMPAD3)) &&  pads.size() > 2 && !pads.at(2).isAnAI())
        {
          pads[2].boing(m, balls);
        }

        //Player 4
        if(GetAsyncKeyState(VK_LBUTTON) &&  pads.size() > 3 && !pads.at(3).isAnAI())
        {
          pads[3].move(false, m);
        }
        if(GetAsyncKeyState(VK_RBUTTON) &&  pads.size() > 3 && !pads.at(3).isAnAI())
        {
          pads[3].move(true, m);
        }
        if((GetAsyncKeyState(VK_MBUTTON) || GetAsyncKeyState(VK_SPACE)) &&  pads.size() > 3 && !pads.at(3).isAnAI())
        {
          pads[3].boing(m, balls);
        }
      
        (!pongMode) && (starPresent = m.isStarActive());
        moveAIPads(m, balls, pads);
        (speed > 75) && (speed -= 0.05); //Slowly speed up after every movement
	    } while (!moveBalls(m, balls) && time >= 1 && starPresent);
    
      if (pongMode)
      {
        for (Ball& b : balls)
        {
          (b.getOwner() != 0) && (scores.at(b.getOwner()-1)++);
          b.restorePos(m);
        }
      }
      else if (time >= 1)
      {
        balls.at(0).restorePosStar(m);
        time += 10;
        (time > 99.99) && (time = 99);
        starScore++;
        m.spawnStar();
        starPresent = true;
      }
    } while(!isWon(scores, goal) && time >= 1);

	  system("CLS");
    cout << "Game Finished!" << endl << endl << "Results:" << endl;

    if (pongMode)
    {
      int hiScorer = 0;
      for (int i = 0; i < scores.size(); i++)
      {
        cout << "Player " << i+1 << ": " << scores.at(i) << endl;
      
        if (scores.at(hiScorer) < scores.at(i))
        {
          hiScorer = i;
        }
      }
      cout << endl << "This game's winner is: " << endl;
      cout << "************" << endl << "* Player " << hiScorer+1 << " *" << endl << "************" << endl;
    }
    else
    {
      starScore;
      string rank;
      cout << endl << "You achieved a Star Score of: " << starScore << endl << endl << "Your rank is: ";
      switch (starScore)
      {
      case 0:
        rank = "Starless Sap";
        break;
      case 1:
        rank = "Asterik Amatuer";
        break;
      case 2:
        rank = "Button Basher";
        break;
      case 3:
        rank = "Up-and-Coming Collector";
        break;
      case 4:
        rank = "Star Seeker";
        break;
      case 5:
        rank = "Paddle Pro";
        break;
      case 6:
        rank = "Killer Collector";
        break;
      case 7:
        rank = "Lucky Lord";
        break;
      case 8:
        rank = "Ballin' Bouncer";
        break;
      default:
        rank = "Star Seer";
      }
      
      if (pads.size() > 1)
      {
        rank += "s";
      }

      cout << rank << endl;
    }

    cout << endl << "Play again? (Y/N):  ";
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    getline(cin,userIn);
    toupper(userIn.at(0));
  } while (userIn.at(0) != 'N');

	return 0;
}

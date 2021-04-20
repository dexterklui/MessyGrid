// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Main program of MessyGrid - a puzzle game where a player is given with a grid
// of numbers in random order except there is one empty cell with no number. The
// aim is to move the numbers around until the order is restored.

#include <iostream>
#include "main_menu.h"
#include "game.h"
#include "clear_screen.h"
using namespace std;

int main()
{
  char option = '1';
  ClearScreen(cout);
  do {
    switch (option) {  // Only print welcoming message in certain scenarios
      case '1':
      case 'N':
      case 'L':
      case 'V':
        cout << "Welcome to MessyGrid!" << endl << endl;
    }

    option = InitMainMenu();
    switch (option) {
      case 'N':  // New Game
        NewGame();
        ClearScreen(cout);
        break;
      case 'L':  // TODO: Load Game
        LoadGame();
        ClearScreen(cout);
        break;
      case 'V':  // TODO: View Leaderboard
        ClearScreen(cout);
        cout << "View leaderboard feature coming soon!" << endl << endl;
        break;
      case 'A':  // About MessyGrid
        ClearScreen(cout);
        PrintAbout();
        break;
      case 'E':  // Exit Game
        break;
      default:
        ClearScreen(cout);
        cout << "Invalid option!" << endl << endl;
    }
  } while (option != 'E');

  // farewall message
  cout << endl << "Thank you for playing MessyGrid. Bye bye!" << endl;

  return 0;
}

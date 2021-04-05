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
using namespace std;

int main()
{
  char option;
  do {
    option = InitMainMenu();
  } while (option != 'E');

  // farewall message
  cout << endl << "Thank you for playing MessyGrid. Bye bye!" << endl;

  return 0;
}

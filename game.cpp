// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Implementing the game.

#include <iostream>
#include <string>
#include <cctype>
#include "game.h"
#include "grid.h"
#include "clear_screen.h"
using namespace std;


void RunGame()
{
  int row, col;
  // TODO: encapsulate reading input to a function and check validity of the
  // input
  cout << "Please enter the number of rows of the grid: ";
  cin >> row;
  cin.ignore(100, '\n');
  cout << "Please enter the number of columns of the grid: ";
  cin >> col;
  cin.ignore(100, '\n');

  Grid grid;
  grid.InitGrid(row, col);
  grid.MovePiece('D');  // TODO: use randomize grid instead

  while ( !grid.IsInOrder() )
    LetUserMovePiece(grid);

  ClearScreen();
  grid.Print();
  cout << endl << "You reordered the messy grid. Congratulation!" << endl;
  cout << endl << "Press <Enter> to return to main menu...";
  string dummy;
  getline(cin, dummy);

  grid.Clean();  // release memory space of dynamic array storing the grid
}

void LetUserMovePiece(Grid& grid)
{
  bool valid_cmd = false;
  char cmd;

  ClearScreen();

  while (!valid_cmd) {
    grid.Print();

    cmd = ReadMoveCommand();
    cmd = toupper(cmd);  // to allow user input command in lower case

    switch (cmd) {
      case 'W':
      case 'S':
      case 'A':
      case 'D':
        valid_cmd = true;
        break;
      default:
        ClearScreen();
        cout << "Invalid input!" << endl << endl;
    }
  }

  grid.MovePiece(cmd);
}

char ReadMoveCommand()
{
  char input;

  cout << "Please move the cell." << endl;
  cout << "W: Up" << endl;
  cout << "S: Down" << endl;
  cout << "A: Left" << endl;
  cout << "D: Right" << endl;
  cin >> input;
  cin.ignore(100, '\n');  // clear remaining garbage value in cin, if any

  return input;
}

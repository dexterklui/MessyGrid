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

  Grid grid(row, col);
  grid.RandomizeGrid();

  while ( !grid.IsInOrder() )
    LetUserMovePiece(grid);

  ClearScreen();
  grid.Print(cout);
  cout << endl << "You reordered the messy grid. Congratulation!" << endl;
  cout << endl << "Press <Enter> to return to main menu...";
  string dummy;
  getline(cin, dummy);
}

void LetUserMovePiece(Grid& grid)
{
  ClearScreen();
  grid.Print(cout);

  char cmd = ReadMoveCommand(cin, cout);
  cmd = toupper(cmd);  // to allow user input command in lower case

  while(!grid.MovePiece(cmd)) {
      ClearScreen();
      cout << "Invalid move!" << endl << endl;
      grid.Print(cout);

      cmd = ReadMoveCommand(cin, cout);
      cmd = toupper(cmd);
  }
}

char ReadMoveCommand(istream &ins, ostream &outs)
{
  char input;

  outs << "Please move the cell." << endl;
  outs << "W: Up" << endl;
  outs << "S: Down" << endl;
  outs << "A: Left" << endl;
  outs << "D: Right" << endl;
  ins >> input;
  if (cin.eof()) {
    cerr << "Received EOF from cin" << endl;
    exit(1);
  }
  ins.ignore(100, '\n');  // clear remaining garbage value in cin, if any

  return input;
}

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

void NewGame()
{
  ClearScreen(cout);
  Dimension dimension = NewGameMenu(cin, cout);
  unsigned int rng_seed_increment = 0;

  Grid grid(dimension.row, dimension.col);  // Create a grid
  do {
    grid.RandomizeGrid(rng_seed_increment++);
  } while (grid.IsInOrder());

  RunGame(grid, 0);  // inital move count is 0
}

Dimension NewGameMenu(istream& ins, ostream& outs)
{
  Dimension dimension = {0, 0};

  if (!ins)
    return dimension;  // return immediately if istream is fail or bad

  outs << "Please input the number of rows (2-10):" << endl;
  ins >> dimension.row;
  while (!ins || dimension.row < 2 || dimension.row > 10) {
    ins.clear();
    ins.ignore(256, '\n');
    ClearScreen(outs);
    outs << "Invalid input!" << endl;
    outs << "Please input the number of rows (2-10):" << endl;
    ins >> dimension.row;
  }

  outs << "Please input the number of columns (2-10):" << endl;;
  ins >> dimension.col;
  while (!ins || dimension.col < 2 || dimension.col > 10) {
    ins.clear();
    ins.ignore(256, '\n');
    ClearScreen(outs);
    outs << "Invalid input!" << endl;
    outs << "Please input the number of columns (2-10):" << endl;
    ins >> dimension.col;
  }
  ins.ignore(256, '\n');

  return dimension;
}


void RunGame(Grid &grid, int move_count)
{
  int QuitControlNum = 0; // If QuitControlNum == 1, it means that we should end this while loop.
  while ( !grid.IsInOrder() ) {
    LetUserMovePiece(grid, QuitControlNum);  // TODO: re-write to handle save and quit cmd
    if (QuitControlNum == 1){break;}
    ++move_count;
  }

  // TODO: will pass this to a function handling congratulate event
  ClearScreen(cout);
  grid.Print(cout);
  cout << endl << "Congratulation! You reordered the messy grid." << endl;
  cout << "Total number of moves: " << move_count << endl;
  cout << endl << "Press <Enter> to return to main menu...";
  string dummy;
  getline(cin, dummy);
}


void LetUserMovePiece(Grid& grid, int& QuitControlNum)
{
  ClearScreen(cout);
  grid.Print(cout);

  char cmd = ReadMoveCommand(cin, cout);
  cmd = toupper(cmd);  // to allow user input command in lower case
  if (cmd == 'B'){
    QuitControlNum = 1;
    cout << endl;
    cout << "You have now successfully quit the game." << endl;
    cout << endl;
    cout << "Do you want to save your progress? ([Y]es. [N]o.): ";
    char QuitOrNot;
    cin >> QuitOrNot; // User enters "Y" means Save the game, "N" means not Save the game.
    QuitOrNot = toupper(QuitOrNot);
    while (QuitOrNot != 'Y' && QuitOrNot != 'N'){
      ClearScreen(cout);
      cout << "Invalid input!" << endl;
      cout << "Do you want to save your progress? ([Y]es. [N]o.): ";
      cin >> QuitOrNot;
      QuitOrNot = toupper(QuitOrNot);
    }
  }

  else {
    while(!grid.MovePiece(cmd)) {
      ClearScreen(cout);
      cout << "Invalid move!" << endl << endl;
      grid.Print(cout);

      cmd = ReadMoveCommand(cin, cout);
      cmd = toupper(cmd);
    }
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
  outs << "B: Quit the game" << endl;
  ins >> input;
  if (cin.eof()) {
    cerr << "Received EOF from cin" << endl;
    exit(1);
  }
  ins.ignore(256, '\n');  // clear remaining garbage value in cin, if any

  return input;
}

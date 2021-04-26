// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Implementing the game execution.

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cctype>
#include "game.h"
#include "grid.h"
#include "clear_screen.h"
using namespace std;

void NewGame()
{
  ClearScreen(cout);
  Dimension dimension = AskForGridSize(cin, cout);
  unsigned int rng_seed_increment = 0;

  Grid grid(dimension.row, dimension.col);  // Create a grid of given dimension
  do {
    grid.RandomizeGrid(rng_seed_increment++);
  } while (grid.IsInOrder());

  RunGame(grid, 0);  // the inital counter for number of move is 0
}


void LoadGame()
{
  ClearScreen(cout);
  ifstream fin("user_save_progress.txt");
  if (fin.fail()) {
    cout << "Could not open save file!" << endl;
    exit(1);
  }

  int move_count;
  int row;
  int col;
  int current_piece;
  fin >> move_count >> row >> col;

  Grid grid(row, col);  // create the grid

  // Set the pieces in the grid to restore the grid position based on the save
  // file.
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      fin >> current_piece;
      Cell c = {i, j};
      grid.set_piece(c, current_piece);
    }
  }

  fin.close();

  RunGame(grid, move_count);
}


Dimension AskForGridSize(istream& ins, ostream& outs)
{
  Dimension dimension = {0, 0};

  if (!ins)  // if fail or bad bit is turned on
    return dimension;

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
  int gonna_quit_game = 0;  // to indicate whether the player chose to quit game
  while ( !grid.IsInOrder() ) {
    LetUserMovePiece(grid, gonna_quit_game);
    if (gonna_quit_game != 0){
      // to read input that indicates whether to save progress (Y: yes, N: no)
      char gonna_save;  

      cout << endl;
      cout << "You have now successfully quit the game." << endl;
      cout << endl;
      cout << "Do you want to save your progress? ([Y]es. [N]o.): ";
      cin >> gonna_save;
      gonna_save = toupper(gonna_save);

      while (gonna_save != 'Y' && gonna_save != 'N'){
        ClearScreen(cout);
        cout << "Invalid input!" << endl;
        cout << "Do you want to save your progress? ([Y]es. [N]o.): ";
        cin >> gonna_save;
        gonna_save = toupper(gonna_save);
      }

      if (gonna_save == 'Y') {
        SaveToFile(move_count, grid);
      }

      break;  // break the main game loop to quit game
    }
    ++move_count;
  }

  CongratulationScreen(move_count, grid);
}


void LetUserMovePiece(Grid& grid, int& gonna_quit_game)
{
  ClearScreen(cout);
  grid.Print(cout);

  char cmd = ReadMoveCommand(cin, cout);
  cmd = toupper(cmd);  // to allow user input command in lower case

  while(!grid.MovePiece(cmd)) {
    if (cmd == 'B') {
      gonna_quit_game = 1;
      return;
    }

    ClearScreen(cout);
    cout << "Invalid move!" << endl << endl;
    grid.Print(cout);

    cmd = ReadMoveCommand(cin, cout);
    cmd = toupper(cmd);
  }
}

char ReadMoveCommand(istream &ins, ostream &outs)
{
  char input;

  outs << "Please move a piece:" << endl;
  outs << "W: Up" << endl;
  outs << "S: Down" << endl;
  outs << "A: Left" << endl;
  outs << "D: Right" << endl;
  outs << endl;
  outs << "B: Quit the game" << endl;  // not Q to prevent unintentional quit
  ins >> input;
  if (cin.eof()) {
    cerr << "Received EOF from cin" << endl;
    exit(5);
  }
  ins.ignore(256, '\n');  // clear remaining garbage value in cin, if any

  return input;
}


void CongratulationScreen(int move_count, const Grid& grid)
{
  ClearScreen(cout);
  grid.Print(cout);
  cout << endl << "Congratulation! You reordered the messy grid." << endl;
  cout << "Total number of moves: " << move_count << endl;
  cout << endl << "Press <Enter> to return to main menu...";
  string dummy;
  getline(cin, dummy);
}


void SaveToFile(int move_count, const Grid& grid)
{
  ofstream fout;
  fout.open("user_save_progress.txt");
  if (fout.fail()) {
    cout << "Error in file opening!" << endl;
    exit(1);
  }
  fout << move_count << endl;
  fout << grid.num_row() << endl;
  fout << grid.num_col() << endl;
  for (int i = 0; i < grid.num_row(); i++) {
    for (int j = 0; j < grid.num_col(); j++) {
      Cell c = {i, j};
      fout << grid.get_piece(c) << ' ';
    }
    fout << endl;
  }

  fout.close();
}

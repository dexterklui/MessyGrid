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
#include "clear_screen.h"
using namespace std;


// TODO: for testing
int main()
{
  RunGame();
  return 0;
}

void RunGame()
{
  const int ROW = 5;
  const int COL = 5;

  int grid[ROW][COL];
  InitGrid(grid, ROW, COL);
  // TODO: Randomize grid

  //while ( !GridIsInOrder(grid, ROW, COL) ) {
  while (true) {  // TODO: test: always loop to test moving mechanism

    ClearScreen();

    bool valid_cmd = false;
    char cmd = '\0';
    while (!valid_cmd) {
      PrintGrid(grid, ROW, COL);

      cmd = ReadMoveCommand();
      cmd = toupper(cmd);

      switch (cmd) {
        case 'W':
        case 'S':
        case 'A':
        case 'D':
          valid_cmd = true;
          break;
        default:
          cout << endl << "Invalid input!" << endl << endl;
      }
    }

    MoveCell(grid, ROW, COL, cmd);
  }

  ClearScreen();
  PrintGrid(grid, ROW, COL);
  cout << endl << "You reordered the messy grid. Congratulation!" << endl;
}

bool GridIsInOrder(int grid[][5], int row, int col)
{
  int correct_value = 1;
  for (int i = 0; i < row; ++i)
    for (int j = 0; j < col; ++j)
      // if it is not the last cell and the cell has incorrect value:
      if ((i != row-1 || j != col-1) && grid[i][j] != correct_value++)
        return false;
  return true;
}

void MoveCell(int grid[][5], int row, int col, char cmd)
{
  Cell empty_cell;  // store the row and col index of the empty cell
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      if (!grid[i][j]) {
        empty_cell.row = i;
        empty_cell.col = j;
        break;
      }
    }
  }

  Cell move_cell;  // store the row and col index of the cell to be moved
  move_cell = empty_cell;

  switch (cmd) {
    case 'W':
      move_cell.row += 1;
      break;
    case 'S':
      move_cell.row -= 1;
      break;
    case 'A':
      move_cell.col += 1;
      break;
    case 'D':
      move_cell.col -= 1;
      break;
    default:
      cout << "game.cpp: MoveCell(): invalid move command" << endl;
      return;
  }

  if (IsValidCell(row, col, move_cell))
    SwapCell(grid, empty_cell, move_cell);
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

void SwapCell(int grid[][5], Cell a, Cell b)
{
  // TODO: add guardian to prevent out of bound error when given invalid cell
  int tmp = grid[a.row][a.col];
  grid[a.row][a.col] = grid[b.row][b.col];
  grid[b.row][b.col] = tmp;
}

bool IsValidCell(int row, int col, Cell cell)
{
  if (cell.row < 0 || cell.row >= row)
    return false;
  if (cell.col < 0 || cell.col >= col)
    return false;
  return true;
}

void PrintGrid(int grid[][5], int row, int col)
{
  int count1 = 0;
  int count2 = 0;
  for (int i = 0; i < row; i++){
    if (count2 != 0) {
      cout << "---";
      for (int c = 0; c < col-1; c++){
        cout << "+----";
      }/* code */
      cout << endl;
    }
    count2 = 1;

    for (int j = 0; j < col; j++){
      int a  = grid[i][j];
      if (count1 % col != 0){
        cout << "| ";
      }
      if (a < 10){
        cout << " " << a << " ";
      }
      else if (a >= 10 && a < 100){
        cout << a << " ";
      }
      count1++;
    }
    cout << endl;
  }
}

void InitGrid(int grid[][5], int row, int col)
{
  int a = 1;
  for (int i = 0; i < row ; i ++){
    for (int j = 0; j < col; j++){
      if (a != row*col){
      grid[i][j] = a;
      }
      else{
        grid[i][j] = 0;
      }
      a++;
    }
  }
}

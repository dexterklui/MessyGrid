// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Define the member functions of class Grid.

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "grid.h"
using namespace std;


Grid::Grid(int row, int col) {
  // create zero-size grid when any dimension is less than or equal to zero
  if (row <= 0 || col <= 0) {
    num_row_ = num_col_ = 0;
    grid_ = nullptr;
    return;
  }

  num_row_ = row;
  num_col_ = col;

  // Initialize a row x col array
  grid_ = new int*[num_row_];
  for (int i = 0; i < num_row_; ++i) {
    grid_[i] = new int[num_col_];
  }

  // Assign values in ascending order starting from 1, except the last element
  // gets the value 0
  int value = 1;
  for (int i = 0; i < num_row_; ++i) {
    for (int j = 0; j < num_col_; ++j) {
      if (i != num_row_ - 1 || j != num_col_ - 1) {  // not the last cell
        grid_[i][j] = value++;
      }
      else {  // is the last cell
        grid_[i][j] = 0;
      }
    }
  }
}


Grid::~Grid()
{
  for (int i = 0; i < num_row_; ++i) {
    delete [] grid_[i];
    grid_[i] = 0;
  }
  delete [] grid_;
  grid_ = nullptr;

  num_row_ = 0;
  num_col_ = 0;
}


bool Grid::operator==(const Grid& grid) const
{
  if (num_row_ != grid.num_row_ || num_col_ != grid.num_col_)
    return false;

  for (int i = 0; i < num_row_; ++i)
    for (int j = 0; j < num_col_; ++j)
      if (grid_[i][j] != grid.grid_[i][j])
        return false;

  return true;
}


bool Grid::operator!=(const Grid& grid) const
{
  return ( !(*this == grid) );
}


int Grid::get_piece(Cell c) const
{
  if (!HasValidCell(c))
    return -1;
  return grid_[c.row_idx][c.col_idx];
}


void Grid::set_piece(Cell c, int p)
{
  if (HasValidCell(c))
    *cell_ptr(c) = p;
}


Cell Grid::get_cell(int p) const
{
  Cell c = {-1, -1};

  for (int i = 0; i < num_row_; ++i)
    for (int j = 0; j < num_col_; ++j)
      if (grid_[i][j] == p) {
        c.row_idx = i;
        c.col_idx = j;
        return c;
      }
  return c;
}


int Grid::MovePiece(char cmd)
{
  Cell empty_cell = get_cell(0);  // to store the location of the empty cell
  Cell move_cell = empty_cell;  // to store the location of the cell to be moved

  switch (cmd) {
    case 'W':
      move_cell.row_idx += 1;
      break;
    case 'S':
      move_cell.row_idx -= 1;
      break;
    case 'A':
      move_cell.col_idx += 1;
      break;
    case 'D':
      move_cell.col_idx -= 1;
      break;
  }

  return SwapPiece(empty_cell, move_cell);
}


bool Grid::IsInOrder() const
{
  int correct_value = 1;
  for (int i = 0; i < num_row_; ++i) {
    for (int j = 0; j < num_col_; ++j) {
      if (i == num_row_ -1 && j == num_col_ -1) {  // for the last cell
        if (grid_[i][j])  // if piece in last cell is not empty
          return false;
      }
      else if (grid_[i][j] != correct_value++) {  // for other cells
        return false;
      }
    }
  }
  return true;
}


bool Grid::HasValidCell(Cell c) const
{
  if (c.row_idx < 0 || c.row_idx >= num_row_)
    return false;
  if (c.col_idx < 0 || c.col_idx >= num_col_)
    return false;
  return true;
}


void Grid::Print(ostream& outs) const
{
  int count1 = 0;
  int count2 = 0;
  for (int i = 0; i < num_row_; i++) {
    if (count2 != 0) {
      outs << "---";
      for (int c = 0; c < num_col_-1; c++) {
        outs << "+----";
      }
      outs << endl;
    }
    count2 = 1;

    for (int j = 0; j < num_col_; j++) {
      int a  = grid_[i][j];
      if (count1 % num_col_ != 0) {
        outs << "| ";
      }
      if (a < 10 && a > 0){
        outs << " " << a << " ";
      }
      else if (a >= 10 && a < 100){
        outs << a << " ";
      }
      else if (a == 0){
        outs << "   ";
      }
      count1++;
    }
    outs << endl;
  }
}


int* Grid::cell_ptr(Cell c)
{
  if ( !HasValidCell(c) )
    throw out_of_range("Cell invalid!");
  return &grid_[c.row_idx][c.col_idx];
}


int Grid::SwapPiece(Cell a, Cell b)
{
  if (!HasValidCell(a) || !HasValidCell(b) || a.EqualCell(b))
    return 0;

  int piece_a = get_piece(a);
  set_piece(a, get_piece(b));
  set_piece(b, piece_a);
  return 1;
}

bool Grid::CanBeMoveOrNot(int MovingNum, int nowrow, int nowcol)
{
  if (MovingNum == 1 && (nowrow + 1) > num_row_) return 1;
  else if (MovingNum == 2 && (nowrow - 1) < 1) return 1;
  else if (MovingNum == 3 && (nowcol - 1) < 1) return 1;
  else if (MovingNum == 4 && (nowcol + 1) > num_col_) return 1;
  return 0;
}

void Grid::RandomizeGrid(unsigned int n)
{
  if (num_row_ <= 0 || num_col_ <= 0)
    return;

  srand((unsigned)time(NULL) + n);
  int num = num_row_ * num_col_;
  int MovingTimes = (rand() % (num*num*num - num*num)) + num*num;
  int nowrow = num_row_, nowcol = num_col_;

  for (int i = 0; i < MovingTimes; i++) {
    int MovingNum = (rand() % (4 - 1 + 1)) + 1;
    if (CanBeMoveOrNot(MovingNum, nowrow, nowcol)) continue;

    char cmd;
    if (MovingNum == 1) {
      cmd = 'W';
      nowrow += 1;
    }
    else if (MovingNum == 2) {
      cmd = 'S';
      nowrow -= 1;
    }
    else if (MovingNum == 3) {
      cmd = 'A';
      nowcol -= 1;
    }
    else {
      cmd = 'D';
      nowcol += 1;
    }

    MovePiece(cmd);
  }

  int a = 0, b = 0;
  for  (int i = 0; i < num_row_; i++) {
    for (int j = 0; j < num_col_; j++) {
      if (grid_[i][j] == 0) {
        a = i;
        b = j;
        break;
      }
    }
  }

  for (int i = 0; i < (num_row_ - a); i++) {
    char cmd2 = 'W';
    MovePiece(cmd2);
  }
  for (int i = 0; i < (num_col_ - b); i++) {
    char cmd3 = 'A';
    MovePiece(cmd3);
  }
}

// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Define the member functions of class Grid.

#include <iostream>
#include "grid.h"
using namespace std;


int Grid::get_piece(Cell c)
{
  if (!HasValidCell(c))
    return -1;
  return grid_[c.row_idx][c.col_idx];
}


void Grid::InitGrid(int row, int col)
{
  num_row_ = row;
  num_col_ = col;

  grid_ = new int*[num_row_];
  for (int i = 0; i < num_row_; ++i) {
    grid_[i] = new int[num_col_];
  }

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


void Grid::MovePiece(char cmd)
{
  Cell empty_cell {-1, -1};  // store the row and col index of the empty cell

  // Find the empty cell and fill the row and col indices of empty_cell
  for (int i = 0; i < num_row_; ++i) {
    for (int j = 0; j < num_col_; ++j) {
      if (!grid_[i][j]) {
        empty_cell.row_idx = i;
        empty_cell.col_idx = j;
        break;
      }
    }
    if (empty_cell.row_idx != -1)  // break when found the empty cell
      break;
  }

  Cell move_cell;  // store the row and col index of the cell to be moved
  move_cell = empty_cell;

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
    default:  // should never reach default. This acts as a debug info
      cout << "game.cpp: MoveCell(): invalid move command" << endl;
      return;
  }

  SwapPiece(empty_cell, move_cell);
}


bool Grid::IsInOrder()
{
  int correct_value = 1;
  for (int i = 0; i < num_row_; ++i)
    for (int j = 0; j < num_col_; ++j)
      // if it is not the last cell and the cell has incorrect value:
      if ((i != num_row_ - 1 || j != num_col_ - 1)
          && grid_[i][j] != correct_value++)
        return false;
  return true;
}


bool Grid::HasValidCell(Cell cell)
{
  if (cell.row_idx < 0 || cell.row_idx >= num_row_)
    return false;
  if (cell.col_idx < 0 || cell.col_idx >= num_col_)
    return false;
  return true;
}


void Grid::Print()
{
  int count1 = 0;
  int count2 = 0;
  for (int i = 0; i < num_row_; i++) {
    if (count2 != 0) {
      cout << "---";
      for (int c = 0; c < num_col_-1; c++){
        cout << "+----";
      }
      cout << endl;
    }
    count2 = 1;

    for (int j = 0; j < num_col_; j++) {
      int a  = grid_[i][j];
      if (count1 % num_col_ != 0){
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


void Grid::Clean()
{
  for (int i = 0; i < num_row_; ++i) {
    delete grid_[i];
    grid_[i] = 0;
  }
  delete grid_;
  grid_ = 0;

  num_row_ = 0;
  num_col_ = 0;
}


void Grid::SwapPiece(Cell a, Cell b)
{
  if (!HasValidCell(a) || !HasValidCell(b) ||  a.EqualCell(b))
    return;

  int tmp = grid_[a.row_idx][a.col_idx];
  grid_[a.row_idx][a.col_idx] = grid_[b.row_idx][b.col_idx];
  grid_[b.row_idx][b.col_idx] = tmp;
}
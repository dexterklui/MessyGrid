// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Define struct Cell that represents a cell in the grid; and class Grid that
// provides a 2-D grid where a player can move the pieces around to re-order the
// pieces.
//
// Terminology in function description:
// - Grid: A grid is a 2-D array of cells containing pieces.
// - Cell: A cell is a place in the grid given by a row and a column index. Each
//         cell in the grid contains a piece, except for each grid there is one
//         empty cell which is represented as containing a pseudo-piece with a
//         value of 0.
// - Piece: Each piece is associated with a unique positive integer, ranging
//          from 1 to (number of cells - 1), except there is one pseudo-piece
//          with a value of 0, representing that the cell it is in is empty.
//          They are moved around during the game until they are in ascending
//          order. 

#ifndef GRID_H
#define GRID_H

// To represent a cell in the grid with the row and column index.
struct Cell {
  int row_idx;
  int col_idx;

  // Method: Check if this cell is equal to another cell, i.e. having the same
  //         row and column index.
  bool EqualCell(Cell c)
  {
    if (row_idx == c.row_idx && col_idx == c.col_idx)
      return true;
    return false;
  }
};

// To store grid itself and the information about the grid, and provide methods
// to work with the grid.
class Grid {
 public:
  int num_row() { return num_row_; }  // get number of rows
  int num_col() { return num_col_; }  // get number of columns

  // Method: Get the value of a piece in a given cell.
  // Input: Cell c: The target cell containing the piece.
  // Output: int: The value of the piece in the target cell; or -1 if the cell
  //              is invalid (beyond the dimension of the grid).
  int get_piece(Cell c);

  // Method: Initialize the grid of a given dimension and assign pieces to the
  //         cells in ascending order (left to right, up to bottom) starting
  //         from 1, except the last cell is has a pseudo-piece with a value of
  //         0.
  void InitGrid(int row, int col);

  // Method: Starting from current piece arrangement, randomize the pieces
  //         inside the grid by randomly moving around the pieces.
  void RandomizeGrid();

  // Method: Move an adjacent piece into the empty cell of the grid according to
  //         the command.
  // Input: char cmd: The command to move the piece. Valid values are:
  //                  W: move the piece below the empty cell up
  //                  S: move the piece above the empty cell down
  //                  A: move the piece on the right of the empty cell left
  //                  D: move the piece on the left of the empty cell right
  void MovePiece(char cmd);

  // Method: Check whether all the pieces in the grid are in ascending order
  //         except the last cell at the bottom right is empty.
  // Output: bool: true if pieces are in ascending order; false otherwise.
  bool IsInOrder();

  // Method: Check if a cell is within the dimension of the grid.
  // Output: bool: true if the cell is within the dimension; false otherwise.
  bool HasValidCell(Cell cell);

  // Method: Print the current grid status on the screen
  void Print();

  // Method: Release memory space of the dynamic array representing the grid.
  //         Do not run this before InitGrid(). Must run this before the grid is
  //         destroyed (e.g. when it leaves its scope), IF it has been
  //         initialized with InitGrid().
  void Clean();

 private:
  int num_row_;  // number of rows of the grid
  int num_col_;  // number of columns of the grid
  int** grid_;  // point to the 2-D dynamic array representing the grid

  // Method: Swap the pieces of two cells, if the cells are valid and not equal
  //         to each other.
  void SwapPiece(Cell a, Cell b);
};

#endif  // ifndef GRID_H

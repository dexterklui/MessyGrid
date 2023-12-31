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
// - Cell: A cell is a place in the grid given by its row and column index. Each
//         cell contains a piece, except there is one empty cell which is
//         represented as containing a pseudo-piece with a value of 0.
// - Piece: Each piece is associated with a unique positive integer, ranging
//          from 1 to (number of cells - 1), except there is one pseudo-piece
//          with a value of 0. The pseudo-piece is used to represent that its
//          cell is empty. They are moved around during the game until they are
//          in ascending order.

#ifndef GRID_H
#define GRID_H

#include <iostream>

// To represent a cell in the grid with the row and column index.
struct Cell {
  int row_idx;
  int col_idx;

  // Function: Check if this cell is equal to another cell, i.e. having the same
  //           row and column index.
  bool EqualCell(Cell c) const
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
  // Constructor: Initialize the grid of a given dimension and assign pieces to
  //              the cells in ascending order (left to right, up to bottom)
  //              starting from 1, except the last (bottom right) cell has a
  //              pseudo-piece with a value of 0.
  // Input: int row, int col: The number of rows and columns of the grid.
  Grid(int row, int col);

  // Destructor: Release memory space of the dynamic array representing the
  //             grid.
  ~Grid();

  bool operator==(const Grid& grid) const;  // return true if two grids are the same
  bool operator!=(const Grid& grid) const;  // return true if two grids are different

  int num_row() const { return num_row_; }  // get number of rows
  int num_col() const { return num_col_; }  // get number of columns

  // Function: Get the value of a piece in a given cell.
  // Input: Cell c: The target cell containing the piece.
  // Output: int: The value of the piece in the target cell; or -1 if the cell
  //              is invalid (beyond the dimension of the grid).
  int get_piece(Cell c) const;

  // Function: Set the piece in a cell to be the given piece, if the cell given
  //           is valid.
  // Input: Cell c: The target cell where the piece is set.
  //        int p: The piece that is set to the target cell.
  void set_piece(Cell c, int p);

  // Function: Given a value of a piece, find the cell where the piece is in
  // Input: int p: The value of the target piece
  // Output: Cell: The cell where the target piece is in. If the target piece
  //               is not found in the grid, the cell returned has its row and
  //               col index set to -1.
  Cell get_cell(int p) const;

  // Function: Starting from current piece arrangement, randomize the pieces
  //           inside the grid by randomly moving around the pieces.
  // Input: unsigned int n: An increment to the RNG seed. The purpose is to use
  //                        a different seed without waiting for another second
  //                        when the previous seed failed to randomize a grid
  //                        (which happens sometimes for a small grid).
  void RandomizeGrid(unsigned int n);

  // Function: Swap the pieces of two cells if the cells are valid and not equal
  //           to each other. Return if the swap is successful.
  //  Input: Cell a, Cell b: two two cells whose pieces are swapped
  //  Output: int: 1 if piece swapped, 0 otherwise
  int SwapPiece(Cell a, Cell b);

  // Function: Move an adjacent piece into the empty cell of the grid according
  //           to the command. If there is no required adjacent piece (when the
  //           empty cell is at the bottom and no more piece below), do nothing.
  //           Also do nothing if the command is invalid. Return if the move is
  //           succesful.
  // Input: char cmd: The command to move the piece. Valid values are:
  //                  W: move up the piece below the empty cell
  //                  S: move down the piece above the empty cell
  //                  A: move left the piece on the right of the empty cell
  //                  D: move right the piece on the left of the empty cell
  // Output: int: 1 if a piece is moved, 0 otherwise
  int MovePiece(char cmd);

  // Function: Check whether all the pieces in the grid are in ascending order
  //           except the last cell at the bottom right is empty.
  // Output: bool: true if pieces are in ascending order; false otherwise.
  bool IsInOrder() const;

  // Function: Check if a cell is within the dimension of the grid.
  // Input: Cell c: The cell to be checked.
  // Output: bool: true if the cell is within the dimension; false otherwise.
  bool HasValidCell(Cell c) const;

  // Function: Print the current grid status on the screen
  // Input: std::ostream& outs: the stream to which the output goes
  void Print(std::ostream& outs) const;

 private:
  int num_row_;  // number of rows of the grid
  int num_col_;  // number of columns of the grid
  int** grid_;  // point to the 2-D dynamic array representing the grid

  // Function: Return a pointer to an element of the 2-D array representing the
  //           grid.
  // Input: Cell c: The cell representing location of the element.
  // Output: int*: a pointer to the element.
  int* cell_ptr(Cell c);

  // Function: Check whether a random movement generated by computer is valiad or not.
  // Output: bool: True if the movement is invalid; False otherwise
  bool CanBeMoveOrNot(int MovingNum, int nowrow, int nowcol);
};

#endif  // ifndef GRID_H

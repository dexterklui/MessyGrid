// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Declare functions for running the game MessyGrid

#ifndef GAME_H
#define GAME_H

// Storing the row and col index of a cell in the grid
struct Cell {
  int row;
  int col;
};

// Function: Main function to run the game
void RunGame();

// TODO: description
void InitGrid(int grid[][5], int row, int col);

// TODO: description
void PrintGrid(int grid[][5], int row, int col);

// Function: Accept user input and move the cell in the grid accordingly
// Input: int grid[][5]: a 2D array representing the grid
//        int row: the number of rows
//        int col: the number of columns
//        char cmd: the move command:
//                  W: move cell below up
//                  S: move cell above down
//                  A: move cell on the right left
//                  D: move cell on the left right
void MoveCell(int grid[][5], int row, int col, char cmd);

// Function: Check if a grid is in order
// Input: int grid[][5]: a 2D array storing the board position
//        int row: the number of rows
//        int col: the number of columns
// Output: bool: true if the grid is in order, false otherwise
bool GridIsInOrder(int grid[][5], int row, int col);

// Function: Prompt user to enter a character to move the cell
// Output: Return a character representing a valid move command:
//         W: move the cell below up
//         S: move the cell above down
//         A: move the cell on the right left
//         D: move the cell on the left right
char ReadMoveCommand();

// Function: swap the value of two cells in a grid
// Input: int grid[][5]: a 2D array storing the board position
//        Cell x, Cell y: the two cells whose values to be swapped
void SwapCell(int grid[][5], Cell a, Cell b);

// Function: check if a given cell is valid (within the range of the grid)
// Input: int row: the number of rows of the grid
//        int col: the number of columns of the grid
//        Cell cell: the cell to be checked
// Output: true if the cell is within the dimension of the grid, false otherwise
bool IsValidCell(int row, int col, Cell cell);

#endif  // ifndef GAME_H

// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Declare functions for running the game MessyGrid

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "grid.h"
using namespace std;

// Struct: Specify a grid dimension with the number of rows and columns
struct Dimension
{
  int row;
  int col;
};

// Function: Prepare a new grid then call RunGame() to start a game
void NewGame();

// Function: Prepare a grid based on save progress then call RunGame() to start
//           a game.
void LoadGame();

// Function: Prompt user for a grid dimension (from 2x2 to 10x10) and return it
// Input: istream &ins: The input stream that provides input
//        ostream &outs: The output stream that prompt message goes
// Output: Dimension: The struct that stores the dimension of the grid
Dimension AskForGridSize(istream& ins, ostream& outs);

// Function: Run the game until quit or game over (when grid is re-ordered)
// Input: Grid& grid: the grid to start playing with
//        int move_count: the initial move counter to start playing with
void RunGame(Grid &grid, int move_count);

// Function: Handles displaying of the grid and dealing with user input for
//           moving a piece.
// Input: Grid& grid: A class Grid storing the grid of the current game.
void LetUserMovePiece(Grid& grid, int& QuitControlNum);

// Function: Prompt user to enter a character as a move command. It does not
//           check whether it is a valid command but return the input character
//           faithfully.
// Input: istream &ins: the input stream from which the input is extracted
//        ostream &outs: the output stream to which the prompt message is
//                       printed
// Output: Return the character read from the user
char ReadMoveCommand(istream &ins, ostream &outs);

// Function: Show the screen to congratulate the user when the game is finished.
// Input: int move_count: The total number of moves
//        const Grid& grid: A class Grid storing the grid of the current game.
void CongratulationScreen(int move_count, const Grid& grid);

// Function: Ask the user whether to save progress before quitting the game
// Input: int move_count: The number of moves so far
//        const Grid& grid: A class Grid storing the grid of the current game.
void AskIfSaveProgress(int move_count, const Grid& grid);

// Function: Open a file as an input file stream and return this stream
// Input: const char file_path[]: The path to the file
// Output: ifstream: The input file stream linked with the opened file
ifstream OpenReadFile(const char file_path[]);

// Function: Open a file as an output file stream and return this stream
// Input: const char file_path[]: The path to the file
// Output: ifstream: The output file stream linked with the opened file
ofstream OpenWriteFile(const char file_path[]);

// Function: Save game progress into the file "user_save_progress.txt". The save
//           file will record the number of moves so far, the dimension of the
//           grid and the number on each cell of the grid.
// Input: int move_count: The number of moves that have been made so far.
//        const Grid& grid: A class Grid storing the grid of the current game.
void SaveToFile(int move_count, const Grid& grid);

#endif  // ifndef GAME_H

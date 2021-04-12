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

// Function: Main function to run the game
void RunGame();

// Function: Handles displaying of the grid and dealing with valid and invalid
//           user input to move a piece.
// Input: Grid& grid: A class Grid storing the grid of the current game.
void LetUserMovePiece(Grid& grid);

// Function: Prompt user to enter a character as a move command. It does not
//           check whether it is a valid command but return the input character
//           faithfully.
// Input: istream &ins: the input stream from which the input is extracted
//        ostream &outs: the output stream to which the prompt message is
//                       printed
// Output: Return the character read from the user
char ReadMoveCommand(istream &ins, ostream &outs);

#endif  // ifndef GAME_H

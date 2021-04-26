[![C/C++ CI](https://github.com/WilliamYEhku/MessyGrid/actions/workflows/c-cpp.yml/badge.svg?event=push)](https://github.com/WilliamYEhku/MessyGrid/actions/workflows/c-cpp.yml)

# MessyGrid

**ENGG1340/COMP2113 Programming Technologies - Group Project**  
Group: 165

## Description:

**MessyGrid** is a puzzle game where a player is given a grid of numbers in
random order except there is one empty cell with no number. The aim is to move
the numbers around until the order is restored.

## Identification of members:

Name: Lui Ka On (UID: 3035074610)  
Name: Ye Zhongzheng (UID: 3035782176)

## Rules:

1. The player chooses the size of the grid, e.g. 5x5 or 4x6.
2. After a random board arrangement with one empty cell is generated, the
   player moves one of the number around the empty cell into the empty cell.
3. Player continues to move the numbers around one at a time until the numbers
   on the board is in ascending order (from left to right, top to bottom). Then
   the game is finished.
4. The player can save the game progress at any time.
5. The player can load a previous saved progress and resume the game.
6. During the game the system keeps recording the cumulative number of moves.

## Features:

1. The system generates a grid of a custom size based on the player's
   preference. 
   * Fulfills requirement 2: Using a class to store the grid configuration
     in its member data and provide methods to manipulate the grid. The game
     also uses structs to store a particular location of a cell in the grid.
     These class and structs provide data structures for storing game status.
   * Fulfills requirement 3: Using dynamic 2D-array for custom-sized grid.
2. The system takes away the largest number, leaving one empty cell on the
   grid, and then uses a random generator to produce a serious of random moves
   to generate a chaotic board arrangement. The arrangement generated will
   always have an empty cell at the bottom right.
   * Fullfills requirement 1: Creating random initial status - random game event
3. The system awaits input from the player (`W`, `S`, `A`, `D` for Up, Down,
   Left, Right) to move the numbers around.
4. The system updates the board arrangement and prints it on screen upon each
   move.
5. The system stores a game progress by storing it in a save file upon a save
   command by the user.
   * Filfills requirement 4: File output to save game status
6. The system loads a previously saved game progress by reading a save file upon
   a load command by the user.
   * Fulfills requirement 4: File input to load game status
8. Different codes (e.g. functions) for different features are separated into
   multiple source and header files. E.g. a header file and a source file are
   dedicated to the class Grid; a main source file is dedicated to a simple main
   function which is the entry point of the program; and etc.
   * Fulfills requirement 5: Program codes in multiple files

## Compilation Instruction:

Type `make` in the terminal to compile the program. The path of the compiled
program is `bin/main`. Alternatively, you can compile and run the program with a
single command `make run`.

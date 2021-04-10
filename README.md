[![C/C++ CI](https://github.com/WilliamYEhku/MessyGrid/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/WilliamYEhku/MessyGrid/actions/workflows/c-cpp.yml)

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
4. The player can save the game progress at any time with an arbitrary name.
   Multiple saves are allowed.
5. The player can load a previous saved progress and resume the game.
6. During the game the system keeps recording the cumulative number of moves
   and the time elapsed.
7. When the game finishes (i.e. the player restores the order of the numbers),
   the system will allow the user to record her alias and the statistics on the
   game leaderboard.

## Features:

1. The system generates a grid of a custom size based on the player's
   preference.
2. The system takes away the largest number, leaving one empty cell on the
   grid, and then uses a random generator to randomly generate a chaotic board
   arrangement. The arrangement generated will always have an empty cell at
   the bottom right. (Requirement 1)
3. The system awaits input from the player (`W`, `S`, `A`, `D` for Up, Down,
   Left, Right) to move the numbers around. (Requirement 3)
4. The system updates the board arrangement and prints it on screen upon each
   move.
5. The system stores a game progress by storing it in a save file upon a save
   command by the user. (Requirement 2, 4)
6. The system loads a previously saved game progress by reading a particular
   save file upon a load command by the user. (Requirement 2, 4)
7. The system stores the game result to the leaderboard when a game is
   finished.
8. Different codes (e.g. functions) for different features (e.g. board
   arrangement generation and game status saving) are stored in different code
   files. (Requirement 5)

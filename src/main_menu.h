// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Declare functions for displaying the main menu and handle user input there.

#ifndef MAINMENU_H
#define MAINMENU_H

// Function: Enter the main menu and let user choos an option
// Output: char: The option chose by the user. Possible values are:
char InitMainMenu();

// Function: Print main menu and list options on screen. Options are:
//           N: New game
//           L: Load game
//           A: Brief description about MessyGrid
//           E: Exit game
void PrintMainMenu();

// Function: Print brief description about MessyGrid
void PrintAbout();

#endif  // ifndef MAINMENU_H

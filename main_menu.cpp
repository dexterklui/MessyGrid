// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Define functions for displaying the main menu and handle user input there.

#include <iostream>
#include <cctype>
#include "main_menu.h"
#include "clear_screen.h"
using namespace std;

char InitMainMenu()
{
  char option;  // to store the option chose by the user

  ClearScreen();
  cout << "Welcome to MessyGrid!" << endl << endl;

  while (true) {
    PrintMainMenu();

    cin >> option;  // read option from user
    option = toupper(option);

    switch (option) {
      case 'N':  // new game
      case 'L':  // load game
      case 'E':  // exit game
        return option;

      case 'A':  // about MessyGrid
        ClearScreen();
        PrintAbout();
        break;

      default:
        ClearScreen();
        cout << "Invalid option!" << endl << endl;
    }
  }
}

void PrintMainMenu()
{
  cout << "Please choose an option:" << endl;
  cout << "- [N]ew game" << endl;
  cout << "- [L]oad game" << endl;
  cout << "- [A]bout MessyGrid" << endl;
  cout << "- [E]xit game" << endl;
  cout << endl;
  cout << "Please enter an option: ";
}

void PrintAbout()
{
  // Max columns is 80 (i.e. for each line output no more than 80 characters)
  // This is easier for reading.
  cout << "MessyGrid is a puzzle game where a player is given with a grid of"
    << "numbers in" << endl
    << "random order except there is one empty cell with no number. The aim is"
    << "to move" << endl
    << "the numbers around until the order is restored." << endl << endl;
}

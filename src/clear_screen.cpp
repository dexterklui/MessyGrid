// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Implement function to clear screen on the terminal

#include <iostream>
#include <string>
#include "clear_screen.h"
using namespace std;

void ClearScreen(ostream& outs)
{
  // Printing 100 lines to clear screen is pathetic but does the job
  // (cplusplus.com) Good thing is that there is  no need to use the bad
  // system() which is resource heavy and not secure
  outs << string(100, '\n');
}

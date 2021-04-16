// ENGG1340/COMP2113 Programming Technologies - Group Project
// Authors: Lui Ka On (3035074610), Ye Zhongzheng (3035782176)
// Group Project: MessyGrid
// Group: 165
//
// Description:
// Implement function to clear screen on the terminal.

#include <iostream>
#include <string>
#include "clear_screen.h"
using namespace std;

void ClearScreen(ostream& outs)
{
  // pathetic but does the job (cplusplus.com)
  // but no need to use the bad system() which is resource heavy and unsecure
  outs << string(100, '\n');
}

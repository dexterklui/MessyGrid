#include <iostream>
#include <iomanip>
#include <string>
#include "../src/grid.h"
using namespace std;

void grid_test(const string test_name, const int row, const int col,
    const int expect_row, const int expect_col) {
  cout << "test: " << test_name << ", result: ";
  Grid grid(row, col);
  cerr << left;
  if (grid.num_row() != expect_row) {
    cerr << " Fail!" << endl;
    cerr << setw(18) << "grid.num_row(): " << grid.num_row() << endl;
    cerr << setw(18) << "Expect: " << expect_row << endl;
    throw 1;
  }
  else if (grid.num_col() != expect_col) {
    cerr << " Fail!" << endl;
    cerr << setw(18) << "grid.num_col(): " << grid.num_col() << endl;
    cerr << setw(18) << "Expect: " << expect_col << endl;
    throw 1;
  }
  else {
    cout << " succeed" << endl;
  }
}

int main()
{
  try {
    grid_test("3x3 grid", 3, 3, 3, 3);
    grid_test("4x7 grid", 4, 7, 4, 7);
    grid_test("0x0 grid", 0, 0, 0, 0);
    grid_test("-1x-1 grid", -1, -1, 0, 0);
    grid_test("-3x-5 grid", -3, -5, 0, 0);
  }
  catch (int) {
    cout << "A test has been failed!" << endl;
    return 1;
  }

  cout << "Passed all tests." << endl;
  return 0;
}

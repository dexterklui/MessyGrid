#include <iostream>
#include <iomanip>
#include <string>
#include "../src/grid.h"
using namespace std;

void grid_test(const string test_name, const int row, const int col,
    const int expect_row, const int expect_col) {
  cout << "test: " << setw(10) << test_name << ", result: ";
  Grid grid(row, col);
  cerr << left;

  // test if number of row is correct
  if (grid.num_row() != expect_row) {
    cerr << " Fail!" << endl;
    cerr << setw(18) << "grid.num_row(): " << grid.num_row() << endl;
    cerr << setw(18) << "Expect: " << expect_row << endl;
    throw 1;
  }

  // test if number of col is correct
  if (grid.num_col() != expect_col) {
    cerr << " Fail!" << endl;
    cerr << setw(18) << "grid.num_col(): " << grid.num_col() << endl;
    cerr << setw(18) << "Expect: " << expect_col << endl;
    throw 1;
  }

  // test if all the pieces in the grid is in order and test grid.get_piece() is
  // working
  for (int i = 0; i < expect_row; ++i) {
    for (int j = 0; j < expect_col; ++j) {
      // pieces should be in ascending order, except last piece is 0
      int expect_piece =
        (i == expect_row-1 && j == expect_col-1 ? 0 : i*expect_col + j+1);
      Cell expect_cell = {i, j};

      // test if all the pieces are in order and test Grid::get_piece()
      int result_piece = grid.get_piece(expect_cell);
      if (result_piece != expect_piece) {
        cerr << " Failed piece order test or Grid::get_piece() test!" << endl;
        cerr << "Value of grid[" << i << "][" << j << "]: "
          << result_piece << endl;
        cerr << setw(21 + i/10 + j/10) << "Expect: " << expect_piece << endl;
        throw 1;
      }

      // test Grid::get_cel()
      Cell result_cell = grid.get_cell(expect_piece);
      if (result_cell.row_idx != expect_cell.row_idx
          || result_cell.col_idx != expect_cell.col_idx) {
        cerr << " Failed Grid::get_cell() test!" << endl;
        cerr << "Given piece " << expect_piece << ":" << endl;
        cerr << "Value of cell coords: " << result_cell.row_idx << " "
          << result_cell.col_idx << endl;
        cerr << setw(22) << "Expect: " << expect_cell.row_idx << " "
          << expect_cell.col_idx << endl;
        throw 1;
      }
    }
  }

  // success message
  cout << "success" << endl;
}

int main()
{
  try {
    grid_test("3x3 grid", 3, 3, 3, 3);
    grid_test("4x7 grid", 4, 7, 4, 7);
    grid_test("10x10 grid", 10, 10, 10, 10);
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

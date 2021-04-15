#define TEST_NO_MAIN

#include "acutest.hpp"
#include "test_grid.h"
#include "../src/grid.h"
#include <cstring>
#include <sstream>
using namespace std;

// General test cases
struct RowColTestVector
{
  const char* name;
  const int input_row;
  const int input_col;
  const int expected_row;
  const int expected_col;
};

RowColTestVector test_vectors[] = {
  {"3x2"   ,3  ,2  ,3  ,2}  ,
  {"4x7"   ,4  ,7  ,4  ,7}  ,
  {"10x10" ,10 ,10 ,10 ,10} ,
  {"0x0"   ,0  ,0  ,0  ,0}  ,
  {"-1x-1" ,-1 ,-1 ,0  ,0}  ,
  {"-3x-5" ,-3 ,-5 ,0  ,0}  ,
};


void TestGridRowCol(void)
{
  unsigned long int i;
  int output_row;
  int output_col;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    RowColTestVector* vec = &test_vectors[i];

    TEST_CASE_("%s grid should have %d rows and %d cols",
        vec->name, vec->expected_row, vec->expected_col);

    Grid grid(vec->input_row, vec->input_col);

    output_row = grid.num_row();
    TEST_CHECK_(output_row == vec->expected_row, "output row: %d", output_row);
    output_col = grid.num_col();
    TEST_CHECK_(output_col == vec->expected_col, "output col: %d", output_col);
  }
}

void TestGridHasValidCell(void)
{
  struct TestVector
  {
    const char* name;
    const int row;
    const int col;
    const Cell check_cell;
    const int expected_value;
  };

  TestVector test_vectors[] = {
    {"3x2 grid should have (0, 0) cell"        , 3 , 2 , {0 , 0}  , 1},
    {"3x2 grid should have (1, 0) cell"        , 3 , 2 , {1 , 0}  , 1},
    {"3x2 grid should have (2, 1) cell"        , 3 , 2 , {2 , 1}  , 1},
    {"3x2 grid should not have (3, 1) cell"    , 3 , 2 , {3 , 1}  , 0},
    {"3x2 grid should not have (2, 2) cell"    , 3 , 2 , {2 , 2}  , 0},
    {"3x2 grid should not have (3, 2) cell"    , 3 , 2 , {3 , 2}  , 0},
    {"3x7 grid should not have (-1, -1) cell"  , 3 , 7 , {-1, -1} , 0},
    {"3x2 grid should not have (-1, 1) cell"   , 3 , 2 , {-1, 1}  , 0},
    {"4x4 grid should not have (2, -1) cell"   , 4 , 4 , {2 , -1} , 0},
    {"0x0 grid should not have (0, 0) cell"    , 0 , 0 , {0 , 0}  , 0},
    {"0x0 grid should not have (1, 2) cell"    , 0 , 0 , {1 , 2}  , 0},
    {"0x0 grid should not have (-1, -1) cell"  , 0 , 0 , {-1, -1} , 0},
    {"-1x-2 grid should not have (0, 0) cell"  , -1, -2, {0 , 0}  , 0},
    {"-1x-2 grid should not have (2, 100) cell", -1, -2, {2 , 100}, 0},
    {"-1x-2 grid should not have (-1, -2) cell", -1, -2, {-1, -2} , 0},
    {"10x10 grid should have (5, 7) cell"      , 10, 10, {5 , 7}  , 1},
    {"10x10 grid should have (9, 9) cell"      , 10, 10, {9 , 9}  , 1},
    {"1x1 grid should have (0, 0) cell"        , 1 , 1 , {0 , 0}  , 1},
  };

  unsigned long int i;
  int output_value;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];
    TEST_CASE(vec->name);

    Grid grid(vec->row, vec->col);
    output_value = grid.HasValidCell(vec->check_cell);

    TEST_CHECK(output_value == vec->expected_value);
  }
}

void TestGridGetPieceAndInitialOrder(void)
{
  unsigned long int i;
  int expected_value;
  int output_value;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    RowColTestVector* vec = &test_vectors[i];

    TEST_CASE(vec->name);

    Grid grid(vec->input_row, vec->input_col);
    Cell target_cell;

    for (int m = 0; m < vec->expected_row; ++m) {
      for (int n = 0; n < vec->expected_col; ++n) {
        // pieces should be in ascending order, except last piece is 0
        expected_value = (m == vec->expected_row-1 && n == vec->expected_col-1 ?
            0 : m*vec->expected_col + n+1);
        target_cell.row_idx = m;
        target_cell.col_idx = n;
        output_value = grid.get_piece(target_cell);

        TEST_CHECK(output_value == expected_value);
        TEST_MSG("Value in cell[%d][%d] should be %d but got %d",
            m, n, expected_value, output_value);
      }
    }
  }
}

void TestGridGetCell(void)
{
  unsigned long int i;
  int value;
  Cell expected_cell;
  Cell output_cell;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    RowColTestVector* vec = &test_vectors[i];

    TEST_CASE(vec->name);

    Grid grid(vec->input_row, vec->input_col);

    for (int m = 0; m < vec->expected_row; ++m) {
      for (int n = 0; n < vec->expected_col; ++n) {
        value = (m == vec->expected_row-1 && n == vec->expected_col-1 ?
            0 : m*vec->expected_col + n+1);
        output_cell = grid.get_cell(value);
        expected_cell = {m, n};

        TEST_CHECK(output_cell.row_idx == expected_cell.row_idx
            && output_cell.col_idx == expected_cell.col_idx);
        TEST_MSG("Value %d should at [%d][%d] but got [%d][%d]", value,
            expected_cell.row_idx, expected_cell.col_idx,
            output_cell.row_idx, output_cell.col_idx);
      }
    }

    expected_cell = {-1, -1};
    int input_values[4] = {
      -27, -1, vec->expected_row * vec->expected_col, 2384};

    for (int j = 0; j < 4; ++j) {
      output_cell = grid.get_cell(input_values[j]);
      TEST_CHECK(output_cell.row_idx == expected_cell.row_idx
          && output_cell.col_idx == expected_cell.col_idx);
      TEST_MSG("Value %d should at [%d][%d] but got [%d][%d]", input_values[j],
          expected_cell.row_idx, expected_cell.col_idx,
          output_cell.row_idx, output_cell.col_idx);
    }
  }
}


void TestGridSetPiece(void)
{
  struct TestVector
  {
    const char* name;
    const int row;
    const int col;
    const int expected_row;
    const int expected_col;
    const Cell cell;
    const int piece;
    const int expected_value;
  };

  TestVector test_vectors[] = {
    {"set 4 at [2][2] in 3x5 grid should get 4", 3, 5, 3, 5, {2, 2}, 4, 4},
    {"set -1 at [2][3] in 3x5 grid should get -1", 3, 5, 3, 5, {2, 3}, -1, -1},
    {"set 0 at [0][0] in 4x3 grid should get 0", 4, 3, 4, 3, {0, 0}, 0, 0},
    {"set 2 at [-1][0] in 3x3 grid should get -1", 3, 3, 3, 3, {-1, 0}, 2, -1},
    {"set 7 at [0][0] in -3x3 grid should get -1", -3, 3, 0, 0, {0, 0}, 7, -1},
    {"set 9 at [9][8] in 10x9 grid should get 9", 10, 9, 10, 9, {9, 8}, 9, 9},
  };

  unsigned long int i;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];

    TEST_CASE(vec->name);

    Grid grid(vec->row, vec->col);
    grid.set_piece(vec->cell, vec->piece);

    // check value of the cell that has been set: value should be updated if the
    // cell is valid, otherwise the result should be -1
    int output_value = grid.get_piece(vec->cell);
    TEST_CHECK(output_value == vec->expected_value);
    TEST_MSG("grid.get_piece() produced: %d", output_value);

    // the values of all other cells should remained unchanged
    for (int m = 0; m < vec->expected_row; ++m) {
      for (int n = 0; n < vec->expected_col; ++n) {
        Cell current_cell = {m, n};
        output_value = grid.get_piece(current_cell);
        int expected_value;

        // If it is the cell that has been set a piece, skip because we already
        // tested it before the loop.
        if (current_cell.row_idx == vec->cell.row_idx
            && current_cell.col_idx == vec->cell.col_idx) {
          continue;
        }

        // initially (without being changed by set_piece), value should be in
        // ascending order starting from 1 except last cell should be 0
        expected_value = (m == vec->expected_row-1 && n == vec->expected_col-1 ?
          0 : m * vec->expected_col + n + 1);

        TEST_CHECK(output_value == expected_value);
        TEST_MSG("[%d][%d] has not changed and should be %d but got %d",
            m, n, expected_value, output_value);
      }
    }
  }
}


void TestGridEqualOperator(void)
{
  unsigned long int i;
  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    RowColTestVector* vec = &test_vectors[i];
    Grid grid_1(vec->input_row, vec->input_col);
    Grid grid_2(vec->input_row, vec->input_col);

    TEST_CASE_("Two %s initialized grid should equal", vec->name);
    TEST_CHECK(grid_1 == grid_2);
    TEST_CHECK(! (grid_1 != grid_2));

    TEST_CASE_("%s ordered grid should not equal grid with different piece",
        vec->name);
    Cell cell = {0, 0};
    grid_2.set_piece(cell, -5);
    if (vec->expected_row != 0 && vec->expected_col != 0) {  // not 0x0 grid
      TEST_CHECK_(! (grid_1 == grid_2), "Should be different at 1st cell");
      TEST_CHECK_(grid_1 != grid_2, "Should be different at 1st cell");
    }

    grid_2.set_piece(cell, 1);  // undo previous change
    cell = {vec->expected_row - 1, vec->expected_col - 1};  // last cell
    grid_2.set_piece(cell, -5);
    if (vec->expected_row != 0 && vec->expected_col != 0) {  // not 0x0 grid
      TEST_CHECK_(! (grid_1 == grid_2), "Should be different at the last cell");
      TEST_CHECK_(grid_1 != grid_2, "Should be different at the last cell");
    }

    TEST_CASE_("%s ordered grid should not equal 1x8 ordered grid", vec->name);
    Grid grid_3(1,8);
    TEST_CHECK(! (grid_1 == grid_3));
    TEST_CHECK(grid_1 != grid_3);
  }
}


void TestGridIsInOrder(void)
{
  unsigned long int i;
  int output_value;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    RowColTestVector* vec = &test_vectors[i];

    TEST_CASE_("Should return true after initializing %s grid",
        vec->name);

    Grid grid(vec->input_row, vec->input_col);
    output_value = grid.IsInOrder();
    TEST_CHECK(output_value = 1);
    TEST_MSG("The grid should be in order initially");

  }

  struct TestVector
  {
    const char* name;
    const int row;
    const int col;
    const Cell cell;
    const int piece;
    const int expected_value;
  };

  TestVector test_vectors[] = {
    {"should return false after set 0 at [0][0] of 3x2 grid",
      3, 2, {0, 0}, 0, 0},
    {"should return true after set 0 at [2][1] of 3x2 grid",
      3, 2, {2, 1}, 0, 1},
    {"should return true after set 0 at [3][0] of 3x2 grid",
      3, 2, {3, 0}, 0, 1},
    {"should return true after set 0 at [2][2] of 3x2 grid",
      3, 2, {2, 2}, 0, 1},
    {"should return true after set 4 at [1][1] of 3x2 grid",
      3, 2, {1, 1}, 4, 1},
    {"should return true after set 4 at [-1][1] of 3x2 grid",
      3, 2, {-1, 1}, 4, 1},
    {"should return false after set 4 at [1][0] of 3x2 grid",
      3, 2, {1, 0}, 4, 0},
    {"should return false after set 12 at [2][3] of 3x4 grid",
      3, 4, {2, 3}, 12, 0},
    {"should return false after set -1 at [9][9] of 10x10 grid",
      10, 10, {9, 9}, -1, 0},
    {"should return true after set -1 at [0][0] of -1x-1 grid",
      -1, -1, {0, 0}, -1, 1},
  };

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];

    TEST_CASE(vec->name);

    Grid grid(vec->row, vec->col);
    grid.set_piece(vec->cell, vec->piece);
    TEST_CHECK(grid.IsInOrder() == vec->expected_value);
  }
}

void TestGridSwapPiece(void)
{
  struct TestVector
  {
    const int row;
    const int col;
    const int expected_row;
    const int expected_col;
    const Cell cell_a;
    const Cell cell_b;
    const int expected_val_a;
    const int expected_val_b;
    const int expected_return_val;
  };

  TestVector test_vectors[] = {
    {3, 2, 3, 2, {0, 0}, {2, 1}, 0, 1, 1},
    {3, 2, 3, 2, {0, 1}, {3, 2}, 2, -1, 0},
    {3, 2, 3, 2, {0, 2}, {2, 0}, -1, 5, 0},
    {3, 2, 3, 2, {3, 0}, {1, 1}, -1, 4, 0},
    {5, 4, 5, 4, {1, 2}, {3, 1}, 14, 7, 1},
    {9, 9, 9, 9, {1, 2}, {1, 2}, 12, 12, 0},
    {3, 4, 3, 4, {1, 2}, {2, 2}, 11, 7, 1},
    {0, 0, 0, 0, {0, 0}, {0, 0}, -1, -1, 0},
    {-1, 4, 0, 0, {0, 0}, {0, 1}, -1, -1, 0},
  };

  unsigned long int i;
  int output_return_val;
  int result_cell_val;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];

    TEST_CASE_("Swap [%d][%d] & [%d][%d] in %dx%d grid should %s",
        vec->cell_a.row_idx, vec->cell_a.col_idx,
        vec->cell_b.row_idx, vec->cell_b.col_idx,
        vec->row, vec->col,
        vec->expected_return_val ? "succeed" : "fail");

    Grid grid(vec->row, vec->col);

    // check return value
    output_return_val = grid.SwapPiece(vec->cell_a, vec->cell_b);
    TEST_CHECK(output_return_val == vec->expected_return_val);
    TEST_MSG("SwapPiece() should return %d but got %d",
        vec->expected_return_val, output_return_val);

    // check the values of the two swapped cells
    result_cell_val = grid.get_piece(vec->cell_a);
    TEST_CHECK(result_cell_val == vec->expected_val_a);
    TEST_MSG("[%d][%d] should be %d but got %d",
        vec->cell_a.row_idx, vec->cell_a.col_idx,
        vec->expected_val_a, result_cell_val);

    result_cell_val = grid.get_piece(vec->cell_b);
    TEST_CHECK(result_cell_val == vec->expected_val_b);
    TEST_MSG("[%d][%d] should be %d but got %d",
        vec->cell_b.row_idx, vec->cell_b.col_idx,
        vec->expected_val_b, result_cell_val);

    // the values of all other cells should remained unchanged
    for (int m = 0; m < vec->expected_row; ++m) {
      for (int n = 0; n < vec->expected_col; ++n) {
        Cell current_cell = {m, n};
        result_cell_val = grid.get_piece(current_cell);
        int expected_value;

        // If it is a swapped cell, skip because we already tested it
        if ((current_cell.row_idx == vec->cell_a.row_idx
            && current_cell.col_idx == vec->cell_a.col_idx)
            || (current_cell.row_idx == vec->cell_b.row_idx
            && current_cell.col_idx == vec->cell_b.col_idx)) {
          continue;
        }

        // initially (without being changed by set_piece), value should be in
        // ascending order starting from 1 except last cell should be 0
        expected_value = (m == vec->expected_row-1 && n == vec->expected_col-1 ?
          0 : m * vec->expected_col + n + 1);

        TEST_CHECK(result_cell_val == expected_value);
        TEST_MSG("[%d][%d] has not changed and should be %d but got %d",
            m, n, expected_value, result_cell_val);
      }
    }
  }
}

void TestGridMovePiece(void)
{
  struct TestVector
  {
    const int row;
    const int col;
    const int expected_row;
    const int expected_col;
    const char* cmd_str;
    const int cmd_len;
    const int expected_return_val;  // only for the last command in cmd_str
    const int expected_grid[5][5];
  };

  TestVector test_vectors[] = {
    {3, 3, 3, 3, "W", 1, 0, {
      {1 , 2 , 3 , -1, -1},
      {4 , 5 , 6 , -1, -1},
      {7 , 8 , 0 , -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 3, 3, 3, "S", 1, 1, {
      {1 , 2 , 3 , -1, -1},
      {4 , 5 , 0 , -1, -1},
      {7 , 8 , 6 , -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 3, 3, 3, "A", 1, 0, {
      {1 , 2 , 3 , -1, -1},
      {4 , 5 , 6 , -1, -1},
      {7 , 8 , 0 , -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 3, 3, 3, "D", 1, 1, {
      {1 , 2 , 3 , -1, -1},
      {4 , 5 , 6 , -1, -1},
      {7 , 0 , 8 , -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 3, 3, 3, "w", 1, 0, {
      {1 , 2 , 3 , -1, -1},
      {4 , 5 , 6 , -1, -1},
      {7 , 8 , 0 , -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 3, 3, 3, "q", 1, 0, {
      {1 , 2 , 3 , -1, -1},
      {4 , 5 , 6 , -1, -1},
      {7 , 8 , 0 , -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 3, 3, 3, "WS", 2, 1, {
      {1 , 2 , 3 , -1, -1},
      {4 , 5 , 0 , -1, -1},
      {7 , 8 , 6 , -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 4, 3, 4, "sD", 2, 1, {
      {1 , 2 , 3 , 4 , -1},
      {5 , 6 , 7 , 8 , -1},
      {9 , 10, 0 , 11, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 4, 3, 4, "cKdQ", 4, 0, {
      {1 , 2 , 3 , 4 , -1},
      {5 , 6 , 7 , 8 , -1},
      {9 , 10, 11, 0 , -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 4, 3, 4, "SSSS", 4, 0, {
      {1 , 2 , 3 , 0 , -1},
      {5 , 6 , 7 , 4 , -1},
      {9 , 10, 11, 8 , -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 4, 3, 4, "DDDDSSSS", 8, 0, {
      {0 , 2 , 3 , 4 , -1},
      {1 , 6 , 7 , 8 , -1},
      {5 , 9 , 10, 11, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {3, 4, 3, 4, "DDDDSSSSAW", 10, 1, {
      {2 , 6 , 3 , 4 , -1},
      {1 , 0 , 7 , 8 , -1},
      {5 , 9 , 10, 11, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
    {5, 5, 5, 5, "ASSWDQDWSDS", 11, 1, {
      {1 , 2 , 3 , 4 , 5 },
      {6 , 7 , 8 , 9 , 10},
      {11, 0 , 13, 14, 15},
      {16, 12, 17, 18, 19},
      {21, 22, 23, 24, 20},
    }},
    {0, 2, 0, 0, "SSDD", 4, 0, {
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1},
    }},
  };

  unsigned long int i;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];
    char cmd;
    int output_return_val;

    TEST_CASE_("Move pieces with %d commands '%s' in %dx%d grid",
        vec->cmd_len, vec->cmd_str, vec->row, vec->col);

    Grid grid(vec->row, vec->col);

    for (int j = 0; j < vec->cmd_len; ++j) {
      cmd = vec->cmd_str[j];
      output_return_val = grid.MovePiece(cmd);
    }

    // check return value for last move command
    TEST_CHECK(output_return_val == vec->expected_return_val);
    TEST_MSG("MovePiece() for last command should return %d but got %d",
        vec->expected_return_val, output_return_val);

    // check if the values in the grid are correct
    for (int m = 0; m < vec->expected_row; ++m) {
      for (int n = 0; n < vec->expected_col; ++n) {
        Cell current_cell = {m, n};
        int current_val = grid.get_piece(current_cell);
        TEST_CHECK(current_val == vec->expected_grid[m][n]);
        TEST_MSG("[%d][%d] should be %d but got %d",
            m, n, vec->expected_grid[m][n], current_val);
      }
    }

    // check [0][0] for grid with resultant dimension 0x0
    if (vec->expected_row == 0 || vec->expected_col == 0) {
      Cell cell = {0, 0};
      TEST_CHECK(grid.get_piece(cell) == -1);
      TEST_MSG("The resultant dimension should be 0x0 so [0][0] should be -1");
    }
  }
}


void TestGridPrint(void)
{
  struct TestVector
  {
    const char* name;
    const int row;
    const int col;
    const char* cmd_str;
    const int cmd_len;
    const char* expected_output;
  };

  TestVector test_vectors[] = {
    {"Print 2x3 grid", 2, 3, "", 0,
      " 1 |  2 |  3 \n---+----+----\n 4 |  5 |    \n"
    },
    {"Print 3x2 grid", 3, 2, "SDDWASDS", 8,
      "   |  2 \n---+----\n 1 |  5 \n---+----\n 4 |  3 \n"
    },
    {"2x0 grid", 2, 0, "SDD", 3,
      ""
    },
    {"4x4 grid", 4, 4, "WDDQ", 4,
      " 1 |  2 |  3 |  4 \n---+----+----+----\n 5 |  6 |  7 |  8 \n---+----+----+----\n 9 | 10 | 11 | 12 \n---+----+----+----\n13 |    | 14 | 15 \n"
    },
  };

  unsigned long int i;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];
    stringstream iostr("");
    char print_output[256] = "";  // Remember increase size if needed

    TEST_CASE(vec->name);

    Grid grid(vec->row, vec->col);
    for (int j = 0; j < vec->cmd_len; ++j)
      grid.MovePiece(vec->cmd_str[j]);

    grid.Print(iostr);
    iostr.get(print_output, 256, '\0');

    TEST_CHECK(strcmp(print_output, vec->expected_output) == 0);
    TEST_MSG("Expected:\n%s", vec->expected_output);
    TEST_MSG("Produced:\n%s", print_output);
  }
}

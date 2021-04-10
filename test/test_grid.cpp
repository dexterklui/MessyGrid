#include "acutest.hpp"
#include "../src/grid.h"

// General test cases
struct TestVector
{
  const char* name;
  const int input_row;
  const int input_col;
  const int expected_row;
  const int expected_col;
};

TestVector test_vectors[] = {
  {"3x2"   ,3  ,2  ,3  ,2}  ,
  {"4x7"   ,4  ,7  ,4  ,7}  ,
  {"10x10" ,10 ,10 ,10 ,10} ,
  {"0x0"   ,0  ,0  ,0  ,0}  ,
  {"-1x-1" ,-1 ,-1 ,0  ,0}  ,
  {"-3x-5" ,-3 ,-5 ,0  ,0}  ,
};

void test_grid_row_col(void)
{
  unsigned long int i;
  int output_row;
  int output_col;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];

    TEST_CASE_("%s grid should have %d rows and %d cols",
        vec->name, vec->expected_row, vec->expected_col);

    Grid grid(vec->input_row, vec->input_col);

    output_row = grid.num_row();
    TEST_CHECK_(output_row == vec->expected_row, "output row: %d", output_row);
    output_col = grid.num_col();
    TEST_CHECK_(output_col == vec->expected_col, "output col: %d", output_col);
  }
}

void test_grid_has_valid_cell(void)
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

// correctness of this tests also depends on correctness of Grid::get_piece()
void test_grid_initial_order_and_get_piece(void)
{
  unsigned long int i;
  int expected_value;
  int output_value;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];

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

void test_grid_get_cell(void)
{
  unsigned long int i;
  int value;
  Cell expected_cell;
  Cell output_cell;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];

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

TEST_LIST = {
  {"grid_row_col", test_grid_row_col},
  {"grid_has_valid_cell", test_grid_has_valid_cell},
  {"grid_initial_order_and_get_piece", test_grid_initial_order_and_get_piece},
  {"grid_get_cell", test_grid_get_cell},
  {NULL, NULL}
};

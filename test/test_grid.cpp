#include "acutest.hpp"
#include "../src/grid.h"

struct TestVector {
  const char* name;
  const int input_row;
  const int input_col;
  const int expected_row;
  const int expected_col;
};

struct TestVector test_vectors[] = {
  {"3x3"   ,3  ,2  ,3  ,2}  ,
  {"4x7"   ,4  ,7  ,4  ,7}  ,
  {"10x10" ,10 ,10 ,10 ,10} ,
  {"0x0"   ,0  ,0  ,0  ,0}  ,
  {"-1x-1" ,-1 ,-1 ,0  ,0}  ,
  {"-3x-5" ,-3 ,-5 ,0  ,0}  ,
};

void test_grid_row_col(void) {
  unsigned long int i;
  int output_row;
  int output_col;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    struct TestVector* vec = &test_vectors[i];

    TEST_CASE(vec->name);

    Grid grid(vec->input_row, vec->input_col);

    output_row = grid.num_row();
    TEST_CHECK(output_row == vec->expected_row);
    TEST_MSG("Expected: %d", vec->expected_row);
    TEST_MSG("Produced: %d", output_row);

    output_col = grid.num_col();
    TEST_CHECK(output_col == vec->expected_col);
    TEST_MSG("Expected: %d", vec->expected_col);
    TEST_MSG("Produced: %d", output_col);
  }
}

void test_grid_initial_order(void) {
  unsigned long int i;
  int expected_value;
  int output_value;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    struct TestVector* vec = &test_vectors[i];

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
        TEST_MSG("Value in cell[%d][%d]:", m, n);
        TEST_MSG("Expected: %d", expected_value);
        TEST_MSG("Produced: %d", output_value);
      }
    }
  }
}

void test_grid_get_cell(void) {
  unsigned long int i;
  int value;
  Cell expected_cell;
  Cell output_cell;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    struct TestVector* vec = &test_vectors[i];

    TEST_CASE(vec->name);

    Grid grid(vec->input_row, vec->input_col);

    for (int m = 0; m < vec->expected_row; ++m) {
      for (int n = 0; n < vec->expected_col; ++n) {
        value = (m == vec->expected_row-1 && n == vec->expected_col-1 ?
            0 : m*vec->expected_col + n+1);
        output_cell = grid.get_cell(value);
        expected_cell = {m, n};

        TEST_CHECK(output_cell.row_idx == expected_cell.row_idx);
        TEST_MSG("Expected: %d", expected_cell.row_idx);
        TEST_MSG("Produced: %d", output_cell.row_idx);

        TEST_CHECK(output_cell.col_idx == expected_cell.col_idx);
        TEST_MSG("Expected: %d", expected_cell.col_idx);
        TEST_MSG("Produced: %d", output_cell.col_idx);
      }
    }

    // The expected_cell of all following tests should be the same
    expected_cell = {-1, -1};
    int values[4] = {-27, -1, vec->expected_row * vec->expected_col, 2384};

    for (int j = 0; j < 4; ++j) {
      output_cell = grid.get_cell(values[j]);
      TEST_CHECK(output_cell.row_idx == expected_cell.row_idx);
      TEST_MSG("Expected: %d", expected_cell.row_idx);
      TEST_MSG("Produced: %d", output_cell.row_idx);

      TEST_CHECK(output_cell.col_idx == expected_cell.col_idx);
      TEST_MSG("Expected: %d", expected_cell.col_idx);
      TEST_MSG("Produced: %d", output_cell.col_idx);
    }
  }
}

TEST_LIST = {
  {"grid_row_col", test_grid_row_col},
  {"grid_initial_order", test_grid_initial_order},
  {"grid_get_cell", test_grid_get_cell},
  {NULL, NULL}
};

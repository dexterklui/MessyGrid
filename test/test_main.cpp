#include "acutest.hpp"
#include "test_grid.h"

TEST_LIST = {
  {"grid_row_col", test_grid_row_col},
  {"grid_has_valid_cell", test_grid_has_valid_cell},
  {"grid_initial_order_and_get_piece", test_grid_initial_order_and_get_piece},
  {"grid_get_cell", test_grid_get_cell},
  {"grid_set_piece", test_grid_set_piece},
  {"grid_IsInOrder_method", test_grid_is_in_order_method},
  {NULL, NULL}
};

#include "acutest.hpp"
#include "test_grid.h"
#include "test_game.h"

TEST_LIST = {
  {"grid_row_col", TestGridRowCol},
  {"grid_has_valid_cell", TestGridHasValidCell},
  {"grid_initial_order_and_get_piece", TestGridGetPieceAndInitialOrder},
  {"grid_get_cell", TestGridGetCell},
  {"grid_set_piece", TestGridSetPiece},
  {"grid_equal_operator", TestGridEqualOperator},
  {"grid_is_in_order", TestGridIsInOrder},
  {"grid_swap_piece", TestGridSwapPiece},
  {"grid_move_piece", TestGridMovePiece},
  {"grid_print", TestGridPrint},

  {"game_read_move_command", TestReadMoveCommand},
  {NULL, NULL}
};

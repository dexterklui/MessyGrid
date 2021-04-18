#define TEST_NO_MAIN

#include <sstream>
#include "acutest.hpp"
#include "../../src/game.h"
using namespace std;

void TestNewGameMenu(void)
{
  struct TestVector
  {
    const char* name;
    const char* input;
    const Dimension expected_output;
  };

  TestVector test_vectors[] = {
    {"Input '4\\n5' should return 4x5 dimension", "4\n5", {4, 5}},
    {"Input '2\\n1\\n2' should return 2x2 dimension", "2\n2", {2, 2}},
    {"Input '7 5' should return 7x5 dimension", "7 5", {7, 5}},
    {"Input '0\\n3\\n3' should return 3x3 dimension", "0\n3\n3", {3, 3}},
    {"Input '0\\n-3 2\\n5 4' should return 5x4 dimension",
      "0\n-3 2\n5 4", {5, 4}},
    {"Input 'l\\n4 3' should return 4x3 dimension",
      "l\n4 3", {4, 3}},
    {"Input 'l\\napp 5 10\\n4up 6\\n10' should return 4x10 dimension",
      "l\napp 5 10\n4up 6\n10", {4, 10}},
    {"Input '11\\n10\\n12\\n10' should return 10x10 dimension",
      "11\n10\n12\n10", {10, 10}},
  };

  unsigned long int i;
  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = & test_vectors[i];

    TEST_CASE(vec->name);

    istringstream iss(vec->input);
    ostringstream oss;
    Dimension output = NewGameMenu(iss, oss);

    TEST_CHECK(output.row == vec->expected_output.row
        && output.col == vec->expected_output.col);
    TEST_MSG("Produced: %dx%d", output.row, output.col);
  }
}

void TestReadMoveCommand(void)
{
  struct TestVector
  {
    const char* name;
    const char* input;
    const char expected_output;
  };

  TestVector test_vectors[] = {
    {"W should return W", "W", 'W'},
    {"S should return S", "S", 'S'},
    {"A should return A", "A", 'A'},
    {"D should return D", "D", 'D'},
    {"w should return w", "w", 'w'},
    {"a should return a", "a", 'a'},
    {"s should return s", "s", 's'},
    {"d should return d", "d", 'd'},
    {"ABCDE should return A", "ABCDE", 'A'},
    {"ef82ghi should return e", "ef82ghi", 'e'},
    {"-298sb should return -", "-298sb", '-'},
    {"S*)aD1/di0 should return S", "S*)aD1/di0", 'S'},
    {"\\nD\\t93*abc should return D", "\nD\t93*abc", 'D'},
    {"  \\tw\\t93*abc should return w", "  \tw\t93*abc", 'w'},
  };

  unsigned long int i;

  for (i = 0; i < sizeof(test_vectors) / sizeof(test_vectors[0]); ++i) {
    TestVector* vec = &test_vectors[i];

    TEST_CASE(vec->name);

    istringstream iss(vec->input);
    ostringstream oss;

    char output = ReadMoveCommand(iss, oss);
    TEST_CHECK_(output == vec->expected_output, "Returned: %c", output);
  }
}

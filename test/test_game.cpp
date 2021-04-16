#define TEST_NO_MAIN

#include <sstream>
#include "acutest.hpp"
#include "../src/game.h"
using namespace std;

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

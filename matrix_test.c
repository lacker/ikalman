#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void test_copy() {
  Number foo[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
  };
  Number bar[3][3];
  m_copy(foo, bar, 3, 3);
  m_print(bar, 3, 3);
}

int main(int argc, char *argv[]) {
  test_copy();
  return 0;
}

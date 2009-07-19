#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void test_copy() {
  /* Put some data in foo, then copy it to bar */
  Matrix foo = alloc_matrix(3, 3);
  Matrix bar = alloc_matrix(3, 3);
  foo.data[1][1] = 1337.0;
  copy_matrix(foo, bar);
  assert(bar.data[1][1] == 1337.0);
}

int main(int argc, char *argv[]) {
  test_copy();
  printf("OK\n");
  return 0;
}

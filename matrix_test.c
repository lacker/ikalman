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

  free_matrix(foo);
  free_matrix(bar);
}

void test_inverse() {
  Matrix foo = alloc_matrix(4, 4);
  set_matrix(foo,
	     1.0, 2.0, 3.0, 4.0,
	     4.0, 1.0, 7.0, 9.0,
	     0.0, 0.0, -4.0, -4.0,
	     2.3, 3.4, 3.1, 0.0);
  Matrix foo_copy = alloc_matrix(4, 4);
  copy_matrix(foo, foo_copy);
  Matrix bar = alloc_matrix(4, 4);
  Matrix identity = alloc_matrix(4, 4);
  set_identity_matrix(identity);

  /* foo should be invertible */
  assert(destructive_invert_matrix(foo, bar));

  /* The process should leave foo as an identity */
  assert(equal_matrix(foo, identity, 0.0001));

  /* bar should be foo's inverse in either direction of multiplication */
  multiply_matrix(foo_copy, bar, foo);
  assert(equal_matrix(foo, identity, 0.0001));
  multiply_matrix(bar, foo_copy, foo);
  assert(equal_matrix(foo, identity, 0.0001));

  free_matrix(foo);
  free_matrix(foo_copy);
  free_matrix(bar);
}

int main(int argc, char *argv[]) {
  test_copy();
  test_inverse();
  printf("OK\n");
  return 0;
}

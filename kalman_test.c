#include <stdio.h>
#include "kalman.h"

/* Test the example of a train moving along a 1-d track */
void test_train() {
  KalmanFilter f = alloc_filter(2, 1);
  free_filter(f);
}

int main(int argc, char *argv[]) {
  test_train();
  printf("OK\n");
  return 0;
}

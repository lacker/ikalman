#include <stdio.h>
#include "gps.h"

/* Test the 2d velocity-only model */
void test_velocity2d() {
  KalmanFilter f = alloc_filter_velocity2d();

  free_filter(f);
}

int main(int argc, char *argv[]) {
  test_velocity2d();
  printf("OK\n");
  return 0;
}

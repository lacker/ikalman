
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "gps.h"

void test_read_lat_long() {
  FILE* file = fopen("testdata/gps_example_1", "r");
  assert(file);

  double lat, lon;

  /* Check the first line */
  assert(read_lat_long(file, &lat, &lon));
  printf("lat: %f long: %f\n", lat, lon);
  assert(abs(lat - 39.315828) < 0.000001);
  assert(abs(lon - -120.167838) < 0.000001);
  
  /* Check there are 132 lines total */
  for (int i = 0; i < 131; ++i) {
    assert(read_lat_long(file, &lat, &lon));
  }
  assert(!read_lat_long(file, &lat, &lon));

  fclose(file);
}

/* Test the 2d velocity-only model */
void test_velocity2d() {
  KalmanFilter f = alloc_filter_velocity2d();

  free_filter(f);
}

int main(int argc, char *argv[]) {
  test_read_lat_long();
  test_velocity2d();
  printf("OK\n");
  return 0;
}

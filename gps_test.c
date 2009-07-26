
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
  assert(abs(lat - 39.315828) < 0.000001);
  assert(abs(lon - -120.167838) < 0.000001);
  
  /* Check there are 132 lines total */
  for (int i = 0; i < 131; ++i) {
    assert(read_lat_long(file, &lat, &lon));
  }
  assert(!read_lat_long(file, &lat, &lon));

  fclose(file);
}

void test_heading_north() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, i * 0.0001, 0.0);
  }

  double heading = get_heading(f);
  assert(abs(heading - 0.0) < 0.01);
  
  free_filter(f);
}

void test_heading_east() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, 0.0, i * 0.0001);
  }

  double heading = get_heading(f);
  assert(abs(heading - 90.0) < 0.01);
  
  free_filter(f);
}

void test_heading_south() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, i * -0.0001, 0.0);
  }

  double heading = get_heading(f);
  assert(abs(heading - 180.0) < 0.01);
  
  free_filter(f);
}

void test_heading_west() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, 0.0, i * -0.0001);
  }

  double heading = get_heading(f);
  assert(abs(heading - 270.0) < 0.01);
  
  free_filter(f);
}

/* Test the 2d velocity-only model */
void test_velocity2d() {
  KalmanFilter f = alloc_filter_velocity2d();

  free_filter(f);
}

int main(int argc, char *argv[]) {
  test_read_lat_long();
  test_heading_north();
  test_heading_east();
  test_heading_south();
  test_heading_west();
  test_velocity2d();
  printf("OK\n");
  return 0;
}

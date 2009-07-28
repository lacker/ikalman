
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

void test_bearing_north() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, i * 0.0001, 0.0, 1.0);
  }

  double bearing = get_bearing(f);
  assert(abs(bearing - 0.0) < 0.01);
  
  /* Velocity should be 0.0001 x units per timestep */
  double dlat, dlon;
  get_velocity(f, &dlat, &dlon);
  assert(abs(dlat - 0.0001) < 0.00001);
  assert(abs(dlon) < 0.00001);
  
  free_filter(f);
}

void test_bearing_east() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, 0.0, i * 0.0001, 1.0);
  }

  double bearing = get_bearing(f);
  assert(abs(bearing - 90.0) < 0.01);

  /* At this rate, it takes 10,000 timesteps to travel one longitude
     unit, and thus 3,600,000 timesteps to travel the circumference of
     the earth. Let's say one timestep is a second, so it takes
     3,600,000 seconds, which is 60,000 minutes, which is 1,000
     hours. Since the earth is about 25000 miles around, this means we
     are traveling at about 25 miles per hour. */
  double mph = get_mph(f);
  assert(abs(mph - 25.0) < 2.0);
  
  free_filter(f);
}

void test_bearing_south() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, i * -0.0001, 0.0, 1.0);
  }

  double bearing = get_bearing(f);
  assert(abs(bearing - 180.0) < 0.01);
  
  free_filter(f);
}

void test_bearing_west() {
  KalmanFilter f = alloc_filter_velocity2d();
  for (int i = 0; i < 100; ++i) {
    update_velocity2d(f, 0.0, i * -0.0001, 1.0);
  }

  double bearing = get_bearing(f);
  assert(abs(bearing - 270.0) < 0.01);
  
  free_filter(f);
}

void test_variable_timestep() {
  KalmanFilter f = alloc_filter_velocity2d();

  /* Move at a constant speed but taking slower and slower readings */
  int east_distance = 0;
  for (int i = 0; i < 20; ++i) {
    east_distance += i;
    update_velocity2d(f, 0.0, east_distance * 0.0001, i);
  }

  double dlat, dlon;
  get_velocity(f, &dlat, &dlon);
  assert(abs(dlat) < 0.000001);
  assert(abs(dlon - 0.0001) < 0.000001);
  
  free_filter(f);
}

void test_calculate_mph() {
  double mph = calculate_mph(39.315842, -120.167107,
			     -0.000031, 0.000003);
  assert(abs(mph - 7.74) < 0.01);
}

int main(int argc, char *argv[]) {
  test_read_lat_long();
  test_bearing_north();
  test_bearing_east();
  test_bearing_south();
  test_bearing_west();
  test_variable_timestep();
  test_calculate_mph();
  printf("OK\n");
  return 0;
}

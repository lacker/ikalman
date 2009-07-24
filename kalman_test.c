#include <stdio.h>
#include "kalman.h"

/* Test the example of a train moving along a 1-d track */
void test_train() {
  KalmanFilter f = alloc_filter(2, 1);

  /* The train state is a 2d vector containing position and velocity.
     Velocity is measured in position units per timestep units. */
  set_matrix(f.state_transition,
	     1.0, 1.0,
	     0.0, 1.0);

  /* We only observe position */
  set_matrix(f.observation_model, 1.0, 0.0);

  /* The covariance matrices are blind guesses */
  set_identity_matrix(f.process_noise_covariance);
  set_identity_matrix(f.observation_noise_covariance);
  
  /* Our knowledge of the start position is incorrect and unconfident */
  double deviation = 1000.0;
  set_matrix(f.state_estimate, 10 * deviation);
  set_identity_matrix(f.estimate_covariance);
  scale_matrix(f.estimate_covariance, deviation * deviation);
  
  /* Test with time steps of the position gradually increasing */
  for (int i = 0; i < 10; ++i) {
    set_matrix(f.observation, (double) i);
    update(f);
  }

  /* Our prediction should be close to (10, 1) */
  printf("estimated position: %f\n", f.state_estimate.data[0][0]);
  printf("estimated velocity: %f\n", f.state_estimate.data[1][0]);
  
  free_filter(f);
}

int main(int argc, char *argv[]) {
  test_train();
  printf("OK\n");
  return 0;
}

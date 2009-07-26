/* Applying Kalman filters to GPS data. */

#include "gps.h"

KalmanFilter alloc_filter_velocity2d() {
  /* The state model has four dimensions:
     x, y, x', y'
     Each time step we can only observe position, not velocity, so the
     observation vector has only two dimensions.
  */
  KalmanFilter f = alloc_filter(4, 2);

  /* The position units are in thousandths of latitude and longitude.
     The velocity units are in thousandths of position units per timestep.
     So a velocity of 1 will change the position by 1 after a million
     timesteps.

     Thus a typical position is hundreds of thousands of units.
     A typical velocity is maybe ten.
     
     Assuming the axes are rectilinear does not work well at the
     poles, but it has the bonus that we don't need to convert between
     lat/long and more rectangular coordinates. The slight inaccuracy
     of our physics model is not too important.
   */
  double v2p = 0.001;
  set_matrix(f.state_transition,
	     1.0, 0.0, v2p, 0.0,
	     0.0, 1.0, 0.0, v2p,
	     0.0, 0.0, 1.0, 0.0,
	     0.0, 0.0, 0.0, 1.0);

  /* We observe (x, y) in each time step */
  set_matrix(f.observation_model,
	     1.0, 0.0, 0.0, 0.0,
	     0.0, 1.0, 0.0, 0.0);

  /* Noise in the world. */
  double pos = 0.000001;
  set_matrix(f.process_noise_covariance,
	     pos, 0.0, 0.0, 0.0,
	     0.0, pos, 0.0, 0.0,
	     0.0, 0.0, 1.0, 0.0,
	     0.0, 0.0, 0.0, 1.0);

  /* Noise in our observation */
  set_matrix(f.observation_noise_covariance,
	     pos, 0.0,
	     0.0, pos);

  /* The start position is totally unknown, so give a high variance */
  set_matrix(f.state_estimate, 0.0, 0.0, 0.0, 0.0);
  set_identity_matrix(f.estimate_covariance);
  double trillion = 1000.0 * 1000.0 * 1000.0 * 1000.0;
  scale_matrix(f.estimate_covariance, trillion);

  return f;
}


bool read_lat_long(FILE* file, double* lat, double* lon) {
  while (true) {
    /* If we find a lat long pair, we're done */
    if (2 == fscanf(file, "%lf,%lf", lat, lon)) {
      return true;
    }

    /* Advance to the next line */
    int ch;
    while ((ch = getc(file)) != '\n') {
      if (EOF == ch) {
	return false;
      }
    }
  }
}

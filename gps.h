#ifndef __GPS_H__
#define __GPS_H__

#include <stdio.h>
#include "kalman.h"

/* Create a GPS filter that only tracks two dimensions of position and
   velocity.
   The inherent assumption is that changes in velocity are randomly
   distributed around 0.
   Free with free_filter after using. */
KalmanFilter alloc_filter_velocity2d();

/* Read a lat,long pair from a file.
   Format is lat,long<ignored>
   Return whether there was a lat,long to be read */
bool read_lat_long(FILE* file, double* lat, double* lon);

#endif

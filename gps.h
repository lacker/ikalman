#ifndef __GPS_H__
#define __GPS_H__

#include "kalman.h"

/* Create a GPS filter that only tracks two dimensions of position and
   velocity.
   The inherent assumption is that changes in velocity are randomly
   distributed around 0.
   Free with free_filter after using. */
KalmanFilter alloc_filter_velocity2d();

#endif

/* To use these functions:

   1. Start with a KalmanFilter created by alloc_filter_velocity2d.
   2. At fixed intervals, call update_velocity2d with the lat/long.
   3. At any time, to get an estimate for the current position,
   bearing, or speed, use the functions:
     get_lat_long
     get_bearing
     get_mph
 */

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

/* Update the velocity2d model with one timestep of gps data. */
void update_velocity2d(KalmanFilter f, double lat, double lon);

/* Read a lat,long pair from a file.
   Format is lat,long<ignored>
   Return whether there was a lat,long to be read */
bool read_lat_long(FILE* file, double* lat, double* lon);

/* Extract a lat long from a velocity2d Kalman filter. */
void get_lat_long(KalmanFilter f, double* lat, double* lon);

/* Extract velocity with lat-long-per-timestep units from a velocity2d
   Kalman filter.
   timestep is the time in seconds between each reading. */
void get_velocity(KalmanFilter f, double* delta_lat, double* delta_lon);

/* Extract a bearing from a velocity2d Kalman filter.
   0 = north, 90 = east, 180 = south, 270 = west */
double get_bearing(KalmanFilter f);

/* Extract speed in miles per hour from a velocity2d Kalman filter.
   seconds_per_reading time in seconds between each reading. */
double get_mph(KalmanFilter f, double seconds_per_reading);

#endif

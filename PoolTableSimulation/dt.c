
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 * NAME: NOAH HUFNAGEL
 */

#include <stdio.h>
#include "dimensions.h"
#include "debug.h"

/*CHANGE: ONEJOB COMMENT ADDED
 * Calculates the minimum dt given a passed in minimum dt and a Velocity(V)
 */
double min_dt(double dt, double V)
{
	double candidate;

    if(DEBUG)printf("min_dt: existing dt = %.5lf, V=%.3lf, ", dt, V);
    	if( V == 0.0)
	{
	    if(DEBUG)printf("zero V, returning %.5lf\n", dt);
	}
	else
	{
	    if(V<0.0) V= -V;
	    candidate = RADIUS / V / 2.0;
	    if(candidate < dt)dt = candidate;

	    if(DEBUG)printf("candidate= %.5lf returning %.5lf\n", candidate, dt);
	}
	return(dt);
}
/*CHANGE: ONEJOB COMMENT ADDED
 * Calculates the final dt given a minimum dt, and VX and VY
 * passes work off to min_dt
 */
double get_dt(double dt, double VX, double VY)
{
	dt = min_dt(dt, VX);
	dt = min_dt(dt, VY);
	return dt;
}

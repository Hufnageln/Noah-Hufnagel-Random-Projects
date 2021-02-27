
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 * Name: NOAH HUFNNAGEL
 */


/* action, criteria, numeric, and comparison functions */

#include <stdio.h>

#include "lib8ball.h"
#include "structs.h"	
#include "debug.h"
#include "mem.h"
#include "table.h"

#include "dt.h"

/* numeric functions *******************************************/
/*CHANGE: ONEJOB COMMENT
 *Calculates the frame time of a ball
 * passes work off to get_dt
 */
double frame_time(void *data)
{
	struct Ball *bp = data;
if(TEXT && DEBUG)printf("frame_time: getting dt for the %d ball.\n", bp->ball);
	/* min is 10 frames a second */
	return(get_dt(0.1, bp->VX, bp->VY));
}

/* criteria functions *******************************************/
/*CHANGE: ONEJOB COMMENT
 * determines if a ball is moving returns true if it is
 */
int are_moving(void *data)
{
	struct Ball *bp = data;
	if(DEBUG)printf("are_moving: the %d ball.\n", bp->ball); 
	return( bp->VX != 0.0 || bp->VY != 0.0);
}
/*CHANGE: ONEJOB COMMENT
 *always returns true
 */
int always_true(void *data)
{
	return( 1==1);
}

/* comparison functions *****************************************/
/*CHANGE: ONEJOB COMMENT
 *returns true if lower's number is lower than higher's
 */
int numeric_order( void *lower, void *higher)
{
	struct Ball *loball = lower, *hiball = higher;
	return( loball->ball  <= hiball->ball);
}

/* action functions *****************************************/
/*CHANGE: ONEJOB COMMENT
 * moves a ball
 * passes work off to basic_move, bounce, and apply_friction
 */
void action_motion(void *data)
{
	struct Ball *bp = data;
	/* three parts to this; move, reflect, slow down */
	basic_move(bp);
	bounce(bp);
	apply_friction(bp);
}
/*CHANGE: ONEJOB COMMENT
 *disposes a ball
 *passes work off to free_ball
 */	
void dispose_ball(void *data)
{
	struct Ball *bp = data;
	free_ball(bp);
}
/*CHANGE: ONEJOB COMMENT
 *prints a single ball
 */
void print_ball(void *data)
{
	struct Ball *bp = data;

	printf("Ball #%2d is at (%6.3lf, %6.3lf) moving (%9.4lf, %9.4lf)\n", 
	    bp->ball, bp->current.X, bp->current.Y, bp->VX, bp->VY);
}

/*CHANGE: ONEJOB COMMENT
 *draws a single ball
 */
void draw_ball(void *data)
{
	struct Ball *bp = data;
	eb_ball(bp->ball, bp->current.X, bp->current.Y);
}


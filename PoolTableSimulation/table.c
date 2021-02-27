
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 *NAME: NOAH HUFNAGEL
 */

#include <stdio.h>
#include <math.h>

#include "debug.h"
#include "dimensions.h"
#include "structs.h"

/* roadmap for reflection:
 * We have some #defines that are restricted to this file to characterize
 * things.  We have 2 utilities to turn either X or Y into an int zone
 * number.  We have 2 utilities to give back a string for a given zone.
 * With all of that we can do reflection.  We can also characterize a
 * pocket when a ball leaves the trable (mem.c dispose ball needs this so
 * that it can print.
 */

/* rail zone is zero */
#define RAIL 0
/* chaaracterize the upper and lower rail's pockets */
#define LEFT 1
#define SIDE 2
#define RIGHT 3
/* characterize the left and right rail's pockets */
#define LOWER 1
#define UPPER 2

/* ignore X, is Y high or low enough to line up with an upper or lower
 * corner pocket opening, or is it along the left or right rail?
 *CHANGE: ONEJOB COMMENT: gives the Y zone 
 */
int Yzone(double Y)
{
	/* equals is the pocket */

	/* near one of the lower pockets */
	if( Y <= CORNER_WIDTH) return LOWER;

	/* between the upper and lower pockets is a rail */
	if( Y < WIDTH - CORNER_WIDTH) return RAIL; 

	/* must be high enough to be near an upper pocket */
	return UPPER;
}

/* ignore Y; is above a corner pocket, a side pocket, or one of the rails
 * between?
 *CHANGE: ONE JOB COMMENT: gives the X zone 
 */
int Xzone(double X)
{
	/* equals is a pocket */

	/* near either the left rail of a left pocket */
	if( X <= CORNER_WIDTH ) return LEFT; 

	/* bettween left pockets and side pockets */
	if( X < SIDE_START_X) return RAIL; 

	/* X value lines up with the side pockets */	
	if( X <= SIDE_END_X ) return SIDE; 

	/* between side pockets and right pockets */
	if( X < LENGTH - CORNER_WIDTH) return RAIL; 
	
	 return RIGHT;/* near either the right rail or a right corner pocket */
}
/*CHANGE: ONEJOB comment 
 * returns the Xname (rail, left, side, right)
 */
char * Xname(int Xzone)
{
	char *names[] = { "rail", "left", "side", "right"};
	return names[Xzone];
}
/*CHANGE: ONEJOB COMMENT 
 * returns the Yname (rail, lower, upper)
 */
char * Yname(int Yzone)
{
	char *names[] = { "rail", "lower", "upper"};
	return names[Yzone];
}

/* a lot of moving parts to bounce */
/* we can't double bounce because of the corner pockets are toi wide and
 * dt is small enough that we take small steps even with the fastest ball
 *
 * ALso - the corner pockets are wider than the ball diameter, saving us
 * from various kinds of grief.
 */

/* so here are the things bounce calls come before bounce */

/* we have 4 similar routines for reflection, followed by 2 routines
 * checking in x or y.
 */

/* othere code hinted at being able to run backwards.  THis code is not
 * written to accomodate that capability!
 */
/*CHANGE:ONEJOB COMMENT 
 *Reflects the ball if it hits a rail on the right side of the table
 */
static void reflectRight(struct Ball *bp)
{
	double line = LENGTH - RADIUS;
	double newX = line + (line - bp->current.X);

	/* prior debugs told us where we are and what ball we are talking
	 * about.
	 */
	if(DEBUG)printf("reflectRight: New X is %.4lf\n", newX);
	/* adjust that value */
	bp->current.X = newX;
	/* flip sign of that V and half both */
	bp->VY *= 0.5; 
	bp->VX *= -0.5;
}

/*CHANGE:ONEJOB COMMENT 
 *Reflects the ball if it hits a rail on the top side of the table
 */
static void reflectAbove(struct Ball *bp)
{
	double line = WIDTH - RADIUS;
	double newY = line + (line - bp->current.Y);

	/* prior debugs told us where we are and what ball we are talking
	 * about.
	 */
	if(DEBUG)printf("reflectAbove: New Y is %.4lf\n", newY);
	/* adjust that value */
	bp->current.Y = newY;
	/* flip sign of that V and half both */
	bp->VY *= -0.5; 
	bp->VX *= 0.5;
}

/*CHANGE:ONEJOB COMMENT 
 *Reflects the ball if it hits a rail on the left side of the table
 */
static void reflectLeft(struct Ball *bp)
{
	double newX = RADIUS + (RADIUS - bp->current.X);

	/* prior debugs told us where we are and what ball we are talking
	 * about.
	 */
	if(DEBUG)printf("reflectLeft: New X is %.4lf\n", newX);
	/* adjust that value */
	bp->current.X = newX;
	/* flip sign of that V and half both */
	bp->VY *= 0.5; 
	bp->VX *= -0.5;
}

/*CHANGE:ONEJOB COMMENT 
 *Reflects the ball if it hits a rail on the bottom side of the table
 */
static void reflectBelow(struct Ball *bp)
{
	double newY = RADIUS + (RADIUS - bp->current.Y);

	/* prior debugs told us where we are and what ball we are talking
	 * about.
	 */
	if(DEBUG)printf("reflectBelow: New Y is %.4lf\n", newY);
	/* adjust that value */
	bp->current.Y = newY;
	/* flip sign of that V and half both */
	bp->VY *= -0.5; 
	bp->VX *= 0.5;
}
/*CHANGE: ONEJOB COMMENT
 *Checks if the ball should be reflected on the left or right
 *Passes work off to reflectLeft, reflectRight
 */
static void Xcheck(struct Ball *bp, int Xz)
{
	/*  use a pointer so I don't replicate the struct */
	struct Position *p = &bp->current; 
	
	if( p->X-RADIUS < 0.0)
	{
if(DEBUG )printf("Xcheck: %d ball is into the %s rail in X at %.4lf\n", 
bp->ball, Xname(Xz), p->X);

	    reflectLeft(bp);

	}
	if( p->X+RADIUS >= LENGTH)
	{
if(DEBUG )printf("Xcheck: %d ball is into the %s rail in X at %.4lf\n", 
bp->ball, Xname(Xz), p->X);

	    reflectRight(bp);

	}
}
/*CHANGE: ONEJOB COMMENT
 *Checks if the ball should be reflected on the top or botton
 *passes work off to reflectAbove, reflectBelow
 */
static void Ycheck(struct Ball *bp, int Yz)
{
	/*  use a pointer so I don't replicate the struct */
	struct Position *p = &bp->current; 
	
	if( p->Y-RADIUS < 0.0)
	{
if(DEBUG )printf("Ycheck: %d ball is into the %s rail in Y at %.4lf\n", 
bp->ball, Yname(Yz), p->Y);
	    
	    reflectBelow(bp);

	}
	if( p->Y+RADIUS >= WIDTH)
	{
if(DEBUG )printf("Ycheck: %d ball is into the %s rail in Y at %.4lf\n", 
bp->ball, Yname(Yz), p->Y);

	    reflectAbove(bp);

	}
}

/* does the zone the ball is in indicate that I should make a partiucular
 * check? If it's not across from any rail, it can't bounce.
 * I could optimize and say if I see rails in both dimensions, I'm too far
 * away from them since the corner pocket sizes are bigger than the ball.
 * But I will let the XYchecks find out rather than bake that into the
 * code.
 */
/*CHANGE: ONEJOB COMMENT
 *Bounces the ball if needded
 *passes work off ot Xzone, Yzone, Ycheck, Xcheck
 */
void bounce(struct Ball *bp)
{
	int Xz, Yz;
	/*  use a pointer so I don't replicate the struct */
	struct Position *p = &bp->current; 

	Xz = Xzone(p->X);
	Yz = Yzone(p->Y);

	if(DEBUG)printf("bounce: %d ball zones are %s %s at (%.3lf, %.3lf)\n", bp->ball, Yname(Yz), Xname(Xz), p->X, p->Y);

	if(Xz == RAIL)
	{
	    /* possible bounce in Y */
	    Ycheck(bp, Yz);
	}
	if(Yz == RAIL)
	{
	    /* possible bounce in X */
	    Xcheck(bp, Xz);
	}

}


/******************* end of reflection specific code *********/

/*CHANGE:ONEJOB COMMENT
 *checks if the ball is off the table, returns 0 if false,, 1 if true.
 */
int off_table(void *data)
{
	int rval = 0;
	struct Ball *bp = data;
	struct Position *p = &bp->current;

	if( p->X < 0.0 || p->X >= LENGTH)
	{
if(DEBUG )printf("off_table: Ball %d is off the table in X at %.4lf\n", bp->ball, p->X);
	    rval = 1;
	}
	if( p->Y < 0.0 || p->Y >= WIDTH)
	{
if(DEBUG )printf("off_table: Ball %d is off the table in Y at %.4lf\n", bp->ball, p->Y);
	    rval = 1;
	}
	return rval;
}

/* point A to point B, let others validate the endpoint */
/*CHANGE: ONEJOB COMMENT
 * move the ball (update x and y) dont care about bouncing or anything else.
 */
void basic_move(struct Ball *bp)
{
	/* stash the current position as old and then update current */
	bp->prev = bp->current;
	bp->current.X = bp->current.X + bp->VX * bp->table->dt;
	bp->current.Y = bp->current.Y + bp->VY * bp->table->dt;
if(DEBUG)printf("move_ball: #%d moves from (%0.1lf, %0.1lf) to (%0.1lf, %0.1lf)\n", bp->ball, bp->prev.X, bp->prev.Y, bp->current.X, bp->current.Y);
}

/*CHANGE: ONEJOB COMMENT
 * calculates the friction percent of the ball
 */
double friction_percent(double VX, double VY, double dv)
{
	double vlength,  percent, v2;
	vlength = sqrt( VX*VX + VY*VY); /* always non-negative */
	v2 = vlength - dv; /* we slow as time moves forward */
	if( v2<= 0.0)
	{
	    percent = 0.0;
	    if(DEBUG)
	    {
		if(vlength > 0.0)
		{
	printf("friction_percent: vector length is %0.5lf, STOPS.\n", vlength);
		}
		else
		{
	printf("friction_percent: vector length is %0.5lf, already stopped.\n", vlength);
		}
	    }
	}
	else
	{
	    /* we will apply to both VX and VY */
	    percent = v2 / vlength; 
	    if(DEBUG)printf("friction_percent: vector length is %0.5lf, becomes %0.4lf (%0.3lf%%)\n", vlength, v2, 100.0 * percent);
	}
	return percent;
}
/*CHANGE: ONEJOB COMMENT
 *applies friction to the ball
 *passes work off to friction_percent
 */
void apply_friction(struct Ball *bp )
{
	/* dv = C * g * dt */
	double dv = MU_ROLLING * GIPS * bp->table->dt;
	double fper;
    if(DEBUG )printf("apply_friction: ball #%d dt is %0.5lf giving dv of %0.5lf\n", bp->ball, bp->table->dt, dv);
	fper = friction_percent(bp->VX, bp->VY, dv);
	bp->VX *= fper;
	bp->VY *= fper;
}





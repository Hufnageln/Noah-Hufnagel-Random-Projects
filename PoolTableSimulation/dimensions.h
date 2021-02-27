
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 */


/* table dimensions */
#define LENGTH 100.0
#define WIDTH (LENGTH / 2.0)
/* ball dimensions */
#define RADIUS 1.125
/* pocket dimensions */
#define CORNER_WIDTH 3.1819805	/* corner pocket in X or Y */
/* side pocket is 4.5 inches total width, 2.25 is half of that */
#define SIDE_WIDTH 4.5
/* do the math here: */
#define SIDE_START_X (WIDTH - SIDE_WIDTH / 2.0)
#define SIDE_END_X (WIDTH + SIDE_WIDTH / 2.0)

/* rolling friction mu is 0.005 to 0.015 
 * g in inches per sec2 is 386.08858267716 */

#define GIPS 386.08858267716
#define MU_ROLLING 0.01


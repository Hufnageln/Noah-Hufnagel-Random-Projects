
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 */

/* structs.h */


struct Sim
{
	double elapsed, dt;
	void *ball_list;
	/*CHANGE: added file name*/
	FILE *file;
};

/* contains position and ball structs */

struct Position
{
	double X, Y;
};

struct Ball
{
	int ball;
	double VX, VY;
	/* I no longer make much use of prev position since I nerfed the
	 * idea of beign able to run the sim backwards.*/
	struct Position current, prev;
	struct Sim *table;
};


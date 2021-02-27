
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 *Name: Noah Hufnagel 
*/


/* input (reading) functions (output functions are elsewhere )*/
#include <stdio.h>

#include "linkedlist.h"
#include "functions.h"
#include "debug.h"
#include "mem.h"
#include "structs.h"

/* return NULL or a filled in ball struct */
/*CHANGE: ONEJOB COMMENT
 *Reads one ball and returns it, NULL when scanf fails.
 */
 /*CHANGE: added Sim parameter*/
struct Ball *read_one(struct Sim *table)
{
	struct Ball cue, *bp = NULL;
	int items;
	/*CHANGE: if changed to while, so that if allocation fails it will skip that ball and go to the next
 	* if allocation succeeds the first time then this is essentially an if test 
 	*/
	/*CHANGE: changed scanf to fscanf*/
	while (5 == ( items = fscanf(table->file, "%d %lf %lf %lf %lf", &cue.ball, &cue.current.X, &cue.current.Y, &cue.VX, &cue.VY)))
	{
	    if(bp = allocate_ball())
	    {
	    	*bp = cue;
		/*CHANGE: break, so when allocation succeeds we exit the loop*/
		break;
	    }
	}
	/*CHANGE: else removed and incorporated into the if, since the prior if was changed to a while*/
	if(TEXT && (items !=5))printf("read_one: scanf returned %d\n", items);
	return bp;

}
/*CHANGE: ONEJOB COMMENT ADDED
 *Reads all the balls and adds them to the simulation. passes work off to read_one 
 */
void read_all(struct Sim *table)
{
	struct Ball *newbie = NULL;

	while( newbie = read_one(table))
	{
	    newbie->table = table;
	    if( !insert(&table->ball_list, newbie, numeric_order, TEXT) )
	    {
	    	/*CHANGE: Added code to free the ball if insert fails*/ 
		free_ball(newbie);
	    }
	}

}


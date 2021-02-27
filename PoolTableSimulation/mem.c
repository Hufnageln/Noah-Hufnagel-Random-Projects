
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 * Name: Noah Hufnagel
 */


/* mem.c - allocates and deallocates dynamic memory */

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "debug.h"
#include "table.h"	/* we need the zone and naming fucntions */
#include "altmem.h"	/*CHANGE: ALTMEM*/
/*CHANGE: ONEJOB COMMEN
 *frees a ball
 *passes work off to off_table, Yname, Yzone, Xname, Xzone
 */
void free_ball(struct Ball *bp)
{
	static int freed = 0;
	if(bp == NULL)
	{
	    if(TEXT )printf("ERROR: free_ball: NULL passed in.\n" );
	}
	else
	{

	    if( off_table(bp))
	    {
		if(TEXT)printf("The %d ball drops into the %s %s pocket.\n", 
		    bp->ball, Yname(Yzone(bp->current.Y)), 
		    Xname(Xzone(bp->current.X))); 
	    }

	    if(DEBUG)printf("free_ball: freeing the %d ball.\n", bp->ball);
	    /*CHANGE: free to alternative free*/
	    alternative_free(bp);
	    /*CHANGE: set bp to NULL*/
	    bp=NULL;
	    freed++;
	    if(TEXT)printf("DIAGNOSTIC: %d balls freed.\n", freed);
	}
}
/*CHANGE: ONEJOB COMMENT
 *Allocates memory for a ball
 */
struct Ball *allocate_ball()
{
	static int allocated = 0;
	/*CHANGE: malloc to alternative malloc*/
	struct Ball *bp = alternative_malloc(sizeof(struct Ball));

	if(bp == NULL)
	{
	    if(TEXT )printf("ERROR: allocate_ball: failed to allocate.\n" );
	}
	else
	{
	    allocated++;
    if(TEXT)printf("DIAGNOSTIC: %d balls allocated.\n", allocated);
	}
	return(bp);
}


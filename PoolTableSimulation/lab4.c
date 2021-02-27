
/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 *Name: NOAH HUFNAGEL
 */


#include <stdio.h>
#include <stdlib.h>

#include "lib8ball.h"
#include "linkedlist.h"   
#include "structs.h"
#include "table.h"
#include "dt.h"
#include "debug.h"
#include "io.h"
#include "functions.h"

/*CHANGE: ONEJOB COMMENT
 *Prints the final elapsed time of the simulation
 */ 
void final_print( struct Sim *table)
{
    printf("Simulation eands at sim elapsed time of %7.4lf seconds.\n", table->elapsed);
}

/*CHANGE: ONEJOB COMMENT 
 *draws the balls after they have all stopped
 */
void final_draw(struct Sim *table, double delay)
{
	eb_clear();
	iterate(table->ball_list, draw_ball);
	eb_refresh();
	millisleep((unsigned int) (delay * 1000.0));
}

/*CHANGE: *ONEJOB COMMENT
 *Outputs the balls. Draws in graphics, prints in text. passes work off to draw_ball and print_ball
 */
void output(struct Sim *table)
{
	if(GRAPHICS)
	{
	    eb_clear();
	    iterate(table->ball_list, draw_ball);
	    eb_refresh();
	    millisleep( (unsigned int) (table->dt * 1000));
	}
	else 
	{
	    /* CHANGE: removed todo for header */
	    printf("\nAt time %7.4lf:\n", table->elapsed);
	    iterate(table->ball_list, print_ball);
	    printf("\n");
	}
}
/*CHANGE: ONEJOB COMMENT
 *Runs the table while any ball is moving
 * passes work off to are_moving, output, draw_ball, print_ball, final_draw, final_print, dispose_ball, off_table
 */ 
void run_the_table(struct Sim *table)
{
	/* GOT A PROBLEM HERE!
	 * how do we iterate to find fastest ball to set dt? 
	 * ANswer: least function, a numeric function in the list that
	 * takes a math function.  GET RID OF SORTING other than on insert,
	 * put the balls in the file in randon order so that output shows
	 * them sorted upon insertion. 
	 * */

	
	table->dt = least(table->ball_list, frame_time);

	/* as long as we have balls on the table and some of them are
	 * moving...
	 */
	while( table->ball_list != NULL && some(table->ball_list, are_moving))
	{
	    output(table );
	    /* now onto the next tick */
	    table->elapsed += table->dt;

	    iterate(table->ball_list, action_motion);

	    /* some of them may have dropped into a pocket */
	    deleteSome(&table->ball_list, off_table, dispose_ball, TEXT);
	}
	if(table->ball_list != NULL)output(table);
	if(GRAPHICS)final_draw(table, 2.0);
	if(TEXT)  final_print(table);

}

/*CHANGE: ONEJOB COMMENT 
 *deletes all the remaining balls when the simulation stops
 *passes work off to always_true, dispose_ball
 */
void clear_remaining(struct Sim *table )
{
	deleteSome(&table->ball_list, always_true, dispose_ball, TEXT);
}
/*CHANGE: added openFile function
 *opens a file and returns the file pointer if it succeeds, NULL otherwise
 */
FILE *openFile(struct Sim *table, char** argv){	
	/*try to open*/
	if (!(table->file = fopen(argv[1], "r"))) 
	{
	    printf("ERROR: unable to open file %s for reading\n", argv[1]);
	}else{
	    printf("DIAGNOSTIC: Successfully opened %s for input.\n", argv[1]);
	}
	return table->file;
}

/* let's do some math....
 * speeds: slow is 1-2 mph (18-35 ips)
 * med is 2-4 mph (36-70 ish ips)
 * fast is 4-7 mph (70 - 125)
 * Typical pro break has the cue ball at 20 MPH, 26 MPH tops.
 * The conversion is 17.6 ips per MPH.
 * 26 MPH is 457.6 ips.
 * 20 MPH is 352 ips.
 * Our ball is 1.125 inches in radius.  
 * We have to see the ball hit the rail but still be on the table.  So 
 * it can't travel more than 1 radius per update.  This means dt is
 * computed from max V.  We will not let dt go above 0.1 seconds in any
 * case.  We won't change dt as the ball slows down to keep things
 * simple.
 * So we will use 22.5 ips in our test data to give 0.025s as frame time
 * and then we note that we see 38 odd frames per second instead of 40 -
 * put that in the writeup; what did you expect from dt alone and why are
 * we seeing fewer?  Revisit this when we do the performance lecture.
 * Later on have a HW where they try to compute the compute time for a
 * frame using the now() call.  Note that instrumentation itself sucks up
 * some time - Heisenberg lives!
 *
 */
/*CHANGE: ONEJOB COMMENT 
 *reads the balls, runs the table, then clears the balls once the simulation is done. takes 
 *command line args in
 *passes work off to read_all, run_the_table,openFile  and clear_remaining
 */
/*CHANGE: added command line args as parameters*/
void read_run_clear(int argc, char **argv)
{
	/* tenth of a sec for base dt - 10 frames per second */
	struct Sim slate = {0.0, 0.1, NULL, NULL}, *table = &slate;
	/*CHANGE: open the file and set filename*/
	if(argc<2) printf("ERROR: not enought args to open a file for input\n");
	/*CHANGE: args must match for code to run*/
	else{
	    /*CHANGE: put the main body in an if test that will only run if file opening succeeds*/ 
	    if((openFile(table, argv)!= NULL)){ 
	        /* read them all */
	        read_all(table);
	        /* run till they stop or drop */
	        run_the_table(table);
	        /* clear the table (free any remaining balls) */
	        clear_remaining(table);
	        /*CHANGE: close the file*/
	    	if (fclose(table->file)==0) printf("DIAGNOSTIC: Closed input file %s\n", argv[1]) ;
	    	else printf("ERROR: unable to close input file %s\n", argv[1]);
	    }
	}
}

/*CHANGE: ONEJOB COMMENT
 *calculates runtime and initializes graphics.
 *passes work off to read_run_clear
 *CHANGE: added command line args
 */ 
int main(int argc, char **argv)
{
	double start, runtime;

	start = now();
	if( TEXT || eb_initialize(0))
	{
	    /*CHANGE: changed call to match new params*/
	    read_run_clear(argc, argv);
	    if(GRAPHICS) eb_teardown();
	}
	else
	{
	    printf("Failed to init.\n");
	}
	runtime = now() - start;
	printf("Total run time is %.9lf seconds.\n", runtime);


	return(EXIT_SUCCESS);
}


/* AU20 Lab 3 Code Copyright 2020 Neil Kirby. Do not remove this comment.
 * Do not publish this code without written permission.
 * If you change this code you must add a comment here with your name and
 * you must comment any place you make changes.
 */

/* table.h - below here is machine generated */


char * Xname(int zone);
int Xzone(double X);
char * Yname(int zone);
int Yzone(double Y);
void apply_friction(struct Ball *bp );
void basic_move(struct Ball *bp);
void bounce(struct Ball *bp);
double friction_percent(double VX, double VY, double dv);
int inside_rails(struct Position p);
int off_table(void *data);

/*Prototype 6
 *Tests command line args
 *Name: Noah Hufnagel
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TEXT 1
#define DEBUG 1
int main(int argc, char **argv){
	printf("%d\n", argc);
	while( *argv != NULL) printf("%s\n", *argv++);
	return 1;
}

#include <stdio.h>

#include "lab6.h"

int main()
{
	long G;
	long range = 0;
	char *str = "1 2 3 4 WHO are we fighting FOR?";

	for (range = 0; range <3; range++)
	{
	    G = count(str, range);
    printf("countmain: %ld words found using range %d on \"%s\"\n", G, range, str);
    	}

	return 0;
}
